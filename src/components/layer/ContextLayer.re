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

exception RefHasNoElement;

let getAnchor =
    (
      contextRect: Webapi.Dom.DomRect.t,
      _layerRect: Webapi.Dom.DomRect.t,
      position: position,
    ) => {
  let scrollX = Webapi.Dom.Window.scrollX(Webapi.Dom.window);
  let scrollY = Webapi.Dom.Window.scrollY(Webapi.Dom.window);
  Webapi.Dom.DomRect.(
    switch (position) {
    | Top =>
      BottomLeft(scrollY +. top(contextRect), scrollX +. left(contextRect))
    | Bottom =>
      TopLeft(scrollY +. bottom(contextRect), scrollX +. left(contextRect))
    | Left =>
      TopRight(scrollY +. top(contextRect), scrollX +. left(contextRect))
    | Right =>
      TopLeft(scrollY +. top(contextRect), scrollX +. right(contextRect))
    }
  );
};

[@react.component]
let make =
    (
      ~contextRef: React.ref(Js.Nullable.t(Dom.element)),
      ~position=Top,
      ~children: (~position: position) => React.element,
      ~onKeyPress=?,
    ) => {
  let (anchor, setAnchor) = React.useState(() => None);
  let divRef = React.useRef(Js.Nullable.null);
  React.useLayoutEffect0(() => {
    let contextElement =
      switch (Js.Nullable.toOption(contextRef.current)) {
      | Some(element) => element
      | None => raise(RefHasNoElement)
      };
    let contextRect =
      Webapi.Dom.Element.getBoundingClientRect(contextElement);

    let layerDiv = Belt.Option.getExn(Js.Nullable.toOption(divRef.current));
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
        ReactDOM.Style.make(
          ~top=Js.Float.toString(y) ++ "px",
          ~left=Js.Float.toString(x) ++ "px",
          (),
        ),
    );
  let innerStyle =
    Belt.Option.map(
      anchor,
      fun
      | BottomLeft(_, _) => ReactDOM.Style.make(~bottom="0", ~left="0", ())
      | TopLeft(_, _) => ReactDOM.Style.make(~top="0", ~left="0", ())
      | TopRight(_, _) => ReactDOM.Style.make(~top="0", ~right="0", ()),
    );
  <Layer ?onKeyPress>
    <div
      ref={ReactDOM.Ref.domRef(divRef)}
      className=Styles.layer
      style=?outerStyle>
      <div className=Styles.layer style=?innerStyle>
        {children(~position)}
      </div>
    </div>
  </Layer>;
};
