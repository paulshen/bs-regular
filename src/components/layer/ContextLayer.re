module Styles = {
  open Css;
  let layer = style([position(`absolute)]);
};

type position =
  | Top
  | Bottom
  | Left
  | Right;

type anchor =
  | BottomLeft(float, float)
  | TopLeft(float, float)
  | TopRight(float, float);

let getAnchor =
    (
      contextRect: Webapi__Dom__DomRect.t,
      _layerRect: Webapi__Dom__DomRect.t,
      position: position,
    ) => {
  Webapi__Dom__DomRect.(
    switch (position) {
    | Top => BottomLeft(top(contextRect), left(contextRect))
    | Bottom => TopLeft(bottom(contextRect), left(contextRect))
    | Left => TopRight(top(contextRect), left(contextRect))
    | Right => TopLeft(top(contextRect), right(contextRect))
    }
  );
};

[@react.component]
let make =
    (
      ~context: React.Ref.t(Js.Nullable.t(Dom.element))=?,
      ~position=Top,
      ~children,
    ) => {
  let (anchor, setAnchor) = React.useState(() => None);
  let divRef = React.useRef(Js.Nullable.null);
  React.useLayoutEffect0(() => {
    let contextElement =
      Belt.Option.getExn(Js.Nullable.toOption(React.Ref.current(context)));
    let contextRect =
      Webapi.Dom.Element.getBoundingClientRect(contextElement);

    let layerDiv =
      Belt.Option.getExn(Js.Nullable.toOption(React.Ref.current(divRef)));
    let layerRect = Webapi.Dom.Element.getBoundingClientRect(layerDiv);

    setAnchor(_ => Some(getAnchor(contextRect, layerRect, position)));
    None;
  });
  let outerStyle =
    Belt.Option.map(
      anchor,
      fun
      | BottomLeft(y, x)
      | TopLeft(y, x)
      | TopRight(y, x) =>
        ReactDOMRe.Style.make(
          ~top=Js.Float.toString(y) ++ "px",
          ~left=Js.Float.toString(x) ++ "px",
          (),
        ),
    );
  let innerStyle =
    Belt.Option.map(
      anchor,
      fun
      | BottomLeft(_, _) => ReactDOMRe.Style.make(~bottom="0", ~left="0", ())
      | TopLeft(_, _) => ReactDOMRe.Style.make(~top="0", ~left="0", ())
      | TopRight(_, _) => ReactDOMRe.Style.make(~top="0", ~right="0", ()),
    );
  <Layer>
    <div
      ref={ReactDOMRe.Ref.domRef(divRef)}
      className=Styles.layer
      style=?outerStyle>
      <div className=Styles.layer style=?innerStyle> children </div>
    </div>
  </Layer>;
};