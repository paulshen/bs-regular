module Styles = {
  open Css;
  let bgc = `hex("404040");
  let button =
    style(
      [%style
        {|
    border-radius: 2px;
    border-style: none;
    color: #ffffff;
    font-size: 14px;
    padding: 10px 16px;
  |}
      ],
    );
  let primary = style([%style {|
    background-color: bgc;
    |}]);
  let secondary = style([%style {|
    background-color: #2A77DF;
    |}]);
};

type buttonType =
  | Primary
  | Secondary;

[@react.component]
let make = (~type_=Primary, ~children, ~className=?) => {
  <button
    className={Cn.make([
      Styles.button,
      switch (type_) {
      | Primary => Styles.primary
      | Secondary => Styles.secondary
      },
      Cn.unpack(className),
    ])}>
    children
  </button>;
};