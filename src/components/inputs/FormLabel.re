module Styles = {
  open Css;
  let label =
    style([
      color(`hex(Colors.primary200)),
      display(`inlineBlock),
      fontSize(`px(14)),
      fontWeight(`num(500)),
      marginBottom(`px(4)),
    ]);
};

[@react.component]
let make = (~children, ~htmlFor=?) => {
  <label className=Styles.label ?htmlFor> children </label>;
};
