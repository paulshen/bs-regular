module Styles = {
  open Css;
  let optionsLayer =
    style([
      border(`px(1), `solid, `hex(Colors.primary450)),
      maxHeight(`px(200)),
      overflow(`auto),
    ]);
  let option =
    style([
      backgroundColor(`hex(Colors.primary500)),
      borderBottom(`px(1), `solid, `hex(Colors.primary450)),
      padding2(~v=`px(8), ~h=`px(16)),
      lastChild([borderBottomStyle(`none)]),
    ]);
  let optionSelected = style([backgroundColor(`hex(Colors.primary490))]);
  let optionFocused = style([textDecoration(`underline)]);
};
type selectOption = SelectOptionType.selectOption;
// type selectOption = {label: string};

[@react.component]
let make =
    (
      ~option: selectOption,
      ~onClick,
      ~isSelected,
      ~isFocused,
      ~scrollToElement: Dom.htmlElement => unit,
    ) => {
  let domRef = React.useRef(Js.Nullable.null);

  React.useEffect1(
    () => {
      if (isFocused) {
        let element =
          Belt.Option.getExn(Js.Nullable.toOption(domRef.current));
        Webapi.Dom.(element |> Element.unsafeAsHtmlElement |> scrollToElement);
      };
      None;
    },
    [|isFocused|],
  );

  <div
    onClick
    tabIndex=0
    className={Cn.fromList([
      Styles.option,
      Cn.on(Styles.optionSelected, isSelected),
      Cn.on(Styles.optionFocused, isFocused),
    ])}
    ref={ReactDOMRe.Ref.domRef(domRef)}>
    {React.string(option.label)}
  </div>;
};
