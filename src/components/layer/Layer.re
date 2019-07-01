module Styles = {
  open Css;
  let container =
    style([
      position(`absolute),
      top(`zero),
      left(`zero),
      width(`percent(100.)),
    ]);
};

type layerContext = {
  container: option(Dom.element),
  setContainer: Dom.element => unit,
};
let context: React.Context.t(layerContext) =
  React.createContext({container: None, setContainer: _ => ()});
module ContextProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(context);
};

type layer = {onKeyPress: option(Webapi.Dom.KeyboardEvent.t => unit)};
let layers: ref(array(React.Ref.t(layer))) = ref([||]);

[@react.component]
let make = (~children, ~onKeyPress=?, ()) => {
  let layerContainer =
    Belt.Option.getExn(React.useContext(context).container);
  let layer = React.useRef({onKeyPress: onKeyPress});
  layer->React.Ref.setCurrent({onKeyPress: onKeyPress});
  React.useLayoutEffect0(() => {
    layers := Js.Array.concat([|layer|], layers^);
    Some(() => layers := Js.Array.filter(l => l !== layer, layers^));
  });
  ReactDOMRe.createPortal(children, layerContainer);
};

[@react.component]
let provider = (~children) => {
  let (container, setContainer) = React.useState(() => None);
  let setContainerCallback =
    React.useCallback0(element => setContainer(_ => Some(element)));
  <ContextProvider value={container, setContainer: setContainerCallback}>
    children
  </ContextProvider>;
};

[@react.component]
let container = () => {
  let domRef = React.useRef(Js.Nullable.null);
  let setContainer = React.useContext(context).setContainer;
  React.useLayoutEffect0(() => {
    let element =
      Belt.Option.getExn(Js.Nullable.toOption(React.Ref.current(domRef)));
    setContainer(element);
    open Webapi.Dom;
    let onKeyPress = (e: KeyboardEvent.t) =>
      if (Js.Array.length(layers^) > 0) {
        let {onKeyPress} =
          React.Ref.current(layers^[Js.Array.length(layers^) - 1]);
        switch (onKeyPress) {
        | Some(onKeyPress) => onKeyPress(e)
        | None => ()
        };
      };
    window |> Window.addKeyDownEventListener(onKeyPress);
    Some(() => Window.removeKeyDownEventListener(onKeyPress) |> ignore);
  });
  <div ref={ReactDOMRe.Ref.domRef(domRef)} className=Styles.container />;
};