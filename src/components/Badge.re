module Styles = {
  open Css;
  let badge =
    style([
      border(`px(1), `solid, `hex(Colors.primary450)),
      borderRadius(`px(2)),
      color(`hex(Colors.primary300)),
      display(`inlineBlock),
      padding2(~v=`px(2), ~h=`px(6)),
    ]);
};

[@react.component]
let make = (~children, ~className=?) => {
  <Text.smallBody className={Cn.make([Styles.badge, Cn.unpack(className)])}>
    children
  </Text.smallBody>;
};