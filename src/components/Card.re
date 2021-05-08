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
let make = (~children, ~className=?) => {
  <div className={Cn.fromList([Styles.card, Cn.take(className)])}>
    children
  </div>;
};
