module Styles = {
  open Css;
  let root = style([%style {|
    font-family: Inter;
  |}]);
};

[@react.component]
let make = () => {
  <div className=Styles.root> {React.string("Hello")} </div>;
};