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

[@react.component]
let make = (~children) => {
  let layerContainer =
    Belt.Option.getExn(React.useContext(context).container);
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
    None;
  });
  <div ref={ReactDOMRe.Ref.domRef(domRef)} />;
};