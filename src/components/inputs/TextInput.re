module Styles = {
  open Css;
  let input =
    style([
      border(`px(1), `solid, `hex(Colors.primary450)),
      borderRadius(`px(2)),
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

let nextUniqueId = ref(1);
let getUniqueId = () => {
  let uniqueId = nextUniqueId^;
  nextUniqueId := uniqueId + 1;
  string_of_int(uniqueId);
};

[@react.component]
let make =
  React.forwardRef(
    (
      ~className=?,
      ~label=?,
      ~placeholder=?,
      ~value=?,
      ~onChange=?,
      ~onFocus=?,
      ~onBlur=?,
      forwardedRef,
    ) => {
    let (inputId, _) = React.useState(() => getUniqueId());
    let input =
      <input
        type_="text"
        className={Cn.make([Styles.input, Cn.unpack(className)])}
        id=inputId
        ?placeholder
        ?value
        ?onChange
        ?onFocus
        ?onBlur
        ref=?{
          Belt.Option.map(
            Js.Nullable.toOption(forwardedRef),
            ReactDOMRe.Ref.domRef,
          )
        }
      />;
    switch (label) {
    | Some(label) =>
      <>
        <FormLabel htmlFor=inputId> {React.string(label)} </FormLabel>
        input
      </>
    | None => input
    };
  });

[@react.component]
let static =
  React.forwardRef(
    (~children, ~className=?, ~label=?, ~tabIndex=?, ~onClick=?, forwardedRef) => {
    let input =
      <div
        className={Cn.make([Styles.input, Cn.unpack(className)])}
        ?onClick
        ?tabIndex
        ref=?{
          Belt.Option.map(
            Js.Nullable.toOption(forwardedRef),
            ReactDOMRe.Ref.domRef,
          )
        }>
        children
      </div>;
    switch (label) {
    | Some(label) =>
      <> <FormLabel> {React.string(label)} </FormLabel> input </>
    | None => input
    };
  });