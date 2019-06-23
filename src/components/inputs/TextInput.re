module Styles = {
  open Css;
  let input =
    style([
      border(`px(1), `solid, `hex(Colors.primary450)),
      boxSizing(`borderBox),
      color(`hex(Colors.primary200)),
      fontSize(`px(16)),
      lineHeight(`px(24)),
      padding4(~top=`px(8), ~bottom=`px(8), ~left=`px(16), ~right=`px(8)),
      transition(~duration=100, "border-color"),
      width(`percent(100.)),
      focus([borderColor(`hex(Colors.primary300)), outlineStyle(`none)]),
      placeholder([
        color(`hex(Colors.primary400)),
        fontWeight(`num(300)),
      ]),
    ]);
};

[@react.component]
let make = (~className=?, ~placeholder=?) => {
  <input
    type_="text"
    className={Cn.make([Styles.input, Cn.unpack(className)])}
    ?placeholder
  />;
};