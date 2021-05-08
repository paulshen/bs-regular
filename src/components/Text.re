module Styles = {
  open Css;
  let smallBody =
    style([
      color(`hex(Colors.primary100)),
      fontSize(`px(13)),
      lineHeight(px(18)),
    ]);
  let smallBodyBold = style([fontWeight(`num(700))]);
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

module SmallBody = {
  [@react.component]
  let make = (~children, ~className=?) =>
    <div className={Cn.fromList([Styles.smallBody, Cn.take(className)])}>
      children
    </div>;
};

module SmallBodyBold = {
  [@react.component]
  let make = (~children, ~className=?) =>
    <div
      className={Cn.fromList([
        Styles.smallBody,
        Styles.smallBodyBold,
        Cn.take(className),
      ])}>
      children
    </div>;
};
module Body = {
  [@react.component]
  let make = (~children, ~className=?) =>
    <div className={Cn.fromList([Styles.body, Cn.take(className)])}>
      children
    </div>;
};
module Header = {
  [@react.component]
  let make = (~children, ~className=?) =>
    <div className={Cn.fromList([Styles.header, Cn.take(className)])}>
      children
    </div>;
};
module SmallHeader = {
  [@react.component]
  let make = (~children, ~className=?) =>
    <div className={Cn.fromList([Styles.smallHeader, Cn.take(className)])}>
      children
    </div>;
};
