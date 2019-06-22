module Styles = {
  open Css;
  let body =
    style([
      color(`hex(Colors.primary100)),
      fontSize(`px(16)),
      lineHeight(px(22)),
    ]);
  let header =
    style([
      color(`hex(Colors.primary200)),
      fontSize(`px(24)),
      fontWeight(`num(500)),
      lineHeight(`px(36)),
      marginBottom(`px(12)),
    ]);
  let smallHeader =
    style([
      color(`hex(Colors.primary400)),
      fontSize(`px(9)),
      lineHeight(`px(11)),
      marginBottom(`px(8)),
      textTransform(`uppercase),
    ]);
};

[@react.component]
let body = (~children, ~className=?) =>
  <div className={Cn.make([Styles.body, Cn.unpack(className)])}>
    children
  </div>;

[@react.component]
let header = (~children, ~className=?) =>
  <div className={Cn.make([Styles.header, Cn.unpack(className)])}>
    children
  </div>;

[@react.component]
let smallHeader = (~children, ~className=?) =>
  <div className={Cn.make([Styles.smallHeader, Cn.unpack(className)])}>
    children
  </div>;