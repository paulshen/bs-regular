module Styles = {
  open Css;
  let layer = style([border(`px(1), `solid, `hex(Colors.primary450))]);
  let option =
    style([
      backgroundColor(`hex(Colors.primary500)),
      borderBottom(`px(1), `solid, `hex(Colors.primary450)),
      padding2(~v=`px(8), ~h=`px(16)),
      lastChild([borderBottomStyle(`none)]),
    ]);
  let optionSelected = style([backgroundColor(`hex(Colors.primary490))]);
};

type option = {label: string};

module SelectOption = {
  [@react.component]
  let make = (~option, ~onClick, ~isSelected) => {
    <div
      onClick
      tabIndex=0
      className={Cn.make([
        Styles.option,
        Cn.ifTrue(Styles.optionSelected, isSelected),
      ])}>
      {React.string(option.label)}
    </div>;
  };
};

module SelectOptions = {
  [@react.component]
  let make = (~options, ~selectedOption, ~onSelect, ~onMouseDown, ~contextRef) => {
    let onKeyPress = (e: Webapi.Dom.KeyboardEvent.t) => {
      switch (Webapi.Dom.KeyboardEvent.key(e)) {
      | "Esc"
      | "Escape" => onSelect(None)
      | _ => ()
      };
    };

    <ContextLayer position=ContextLayer.Bottom contextRef onKeyPress>
      {(~position as _) => {
         let inputElement =
           Belt.Option.getExn(
             Js.Nullable.toOption(React.Ref.current(contextRef)),
           );
         let style =
           ReactDOMRe.Style.make(
             ~width=
               string_of_int(Webapi.Dom.Element.clientWidth(inputElement))
               ++ "px",
             (),
           );
         <div className=Styles.layer onMouseDown style>
           {React.array(
              Js.Array.mapi(
                (option, i) => {
                  let isSelected =
                    switch (selectedOption) {
                    | Some(selectedOption) => selectedOption === option
                    | None => false
                    };
                  <SelectOption
                    option
                    isSelected
                    onClick={_ => onSelect(Some(option))}
                    key={string_of_int(i)}
                  />;
                },
                options,
              ),
            )}
         </div>;
       }}
    </ContextLayer>;
  };
};

[@react.component]
let make =
    (~getOptions, ~selectedOption, ~onChange=?, ~label=?, ~placeholder=?, ()) => {
  let inputRef = React.useRef(Js.Nullable.null);
  let (textValue, setTextValue) = React.useState(() => "");
  let (showOptions, setShowOptions) = React.useState(() => false);

  React.useEffect1(
    () => {
      switch (selectedOption) {
      | Some(selectedOption) => setTextValue(_ => selectedOption.label)
      | None => setTextValue(_ => "")
      };
      None;
    },
    [|selectedOption|],
  );

  let onInputChange =
    React.useCallback0(e => {
      let value: string = ReactEvent.Form.currentTarget(e)##value;
      setTextValue(_ => value);
      setShowOptions(_ => true);
    });
  let blurTimeout = React.useRef(None);
  let onBlur =
    React.useCallback0(_ =>
      React.Ref.setCurrent(
        blurTimeout,
        Some(Js.Global.setTimeout(() => setShowOptions(_ => false), 100)),
      )
    );
  let onFocus = _ => {
    switch (React.Ref.current(blurTimeout)) {
    | Some(timeout) =>
      Js.Global.clearTimeout(timeout);
      React.Ref.setCurrent(blurTimeout, None);
    | None => ()
    };
    setShowOptions(_ => true);
  };
  let onMouseDown = React.useCallback0(onFocus);
  let onSelect = option => {
    setShowOptions(_ => false);
    switch (option) {
    | Some(option) =>
      switch (onChange) {
      | Some(onChange) => onChange(option)
      | None => ()
      }
    | None => ()
    };
  };
  <div onFocus={React.useCallback0(onFocus)} onBlur>
    <TextInput
      value=textValue
      onChange=onInputChange
      ?label
      ?placeholder
      ref=inputRef
    />
    {String.length(textValue) > 0 && showOptions
       ? {
         let options = getOptions(textValue);
         Array.length(options) > 0
           ? <SelectOptions
               options
               selectedOption
               onSelect
               onMouseDown
               contextRef=inputRef
             />
           : React.null;
       }
       : React.null}
  </div>;
};