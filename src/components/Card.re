module Styles = {
  open Css;
  let card =
    style([
      border(`px(1), `solid, `hex(Colors.primary450)),
      borderRadius(`px(4)),
      padding(`px(16)),
    ]);
};

[@react.component]
let make = (~children) => {
  <div className=Styles.card> children </div>;
};