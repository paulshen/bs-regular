module Styles = {
  open Css;
  let button =
    style([
      borderRadius(`px(2)),
      borderStyle(`none),
      color(`hex(Colors.primary500)),
      fontSize(`px(16)),
      padding2(~v=`px(10), ~h=`px(16)),
    ]);
  let primary = style([backgroundColor(`hex(Colors.primary200))]);
  let secondary = style([backgroundColor(`hex("2A77DF"))]);
};

type buttonType =
  | Primary
  | Secondary;

[@react.component]
let make =
  React.forwardRef(
    (
      ~type_=Primary,
      ~children,
      ~className=?,
      ~onClick=?,
      ~onMouseEnter=?,
      ~onMouseLeave=?,
      forwardedRef,
    ) =>
    <button
      className={Cn.fromList([
        Styles.button,
        switch (type_) {
        | Primary => Styles.primary
        | Secondary => Styles.secondary
        },
        Cn.take(className),
      ])}
      ?onClick
      ?onMouseEnter
      ?onMouseLeave
      ref=?{
        Belt.Option.map(
          Js.Nullable.toOption(forwardedRef),
          ReactDOM.Ref.domRef,
        )
      }>
      children
    </button>
  );
