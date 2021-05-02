module Styles = {
  open Css;
  let divider =
    style([
      backgroundColor(`hex(Colors.primary450)),
      height(`px(1)),
      marginBottom(`px(4)),
    ]);
};

[@react.component]
let make = () => {
  <div className=Styles.divider />;
};
