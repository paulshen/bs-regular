module Styles = {
  open Css;
  let span1Percent = 100. /. 12.;
  let row = style([display(`flex), flexWrap(`wrap)]);
  let cell = style([boxSizing(`borderBox)]);
};

type gridContext = {
  span: int,
  gutter: int,
};
let context = React.createContext({span: 12, gutter: 8});
module ContextProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(context);
};

module Row = {
  [@react.component]
  let make = (~className=?, ~span=?, ~children) => {
    let {gutter} = React.useContext(context);
    let style =
      switch (gutter) {
      | 0 => None
      | gutter =>
        Some(
          ReactDOM.Style.make(
            ~marginLeft=string_of_int(- gutter) ++ "px",
            ~marginRight=string_of_int(- gutter) ++ "px",
            (),
          ),
        )
      };
    let body =
      <div className={Cn.fromList([Styles.row, Cn.take(className)])} ?style>
        children
      </div>;
    switch (span) {
    | Some(span) =>
      <ContextProvider value={span, gutter}> body </ContextProvider>
    | None => body
    };
  };
};
module Cell = {
  [@react.component]
  let make = (~span, ~className=?, ~children) => {
    let {span: contextSpan, gutter} = React.useContext(context);
    let style =
      ReactDOM.Style.make(
        ~width=
          Js.Float.toString(
            float_of_int(span) /. float_of_int(contextSpan) *. 100.,
          )
          ++ "%",
        (),
      );
    let style =
      if (gutter != 0) {
        ReactDOM.Style.combine(
          style,
          ReactDOM.Style.make(
            ~paddingLeft=string_of_int(gutter) ++ "px",
            ~paddingRight=string_of_int(gutter) ++ "px",
            (),
          ),
        );
      } else {
        style;
      };
    <ContextProvider value={span, gutter}>
      <div className={Cn.fromList([Styles.cell, Cn.take(className)])} style>
        children
      </div>
    </ContextProvider>;
  };
};
