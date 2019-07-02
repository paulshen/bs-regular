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
  let optionFocused = style([textDecoration(`underline)]);
};

type selectOption = {label: string};

module SelectOption = {
  [@react.component]
  let make = (~option, ~onClick, ~isSelected, ~isFocused) => {
    <div
      onClick
      tabIndex=0
      className={Cn.make([
        Styles.option,
        Cn.ifTrue(Styles.optionSelected, isSelected),
        Cn.ifTrue(Styles.optionFocused, isFocused),
      ])}>
      {React.string(option.label)}
    </div>;
  };
};

module SelectOptions = {
  [@react.component]
  let make = (~options, ~selectedOption, ~onSelect, ~onMouseDown, ~contextRef) => {
    let (focusedIndex, setFocusedIndex) = React.useState(() => (-1));
    let onKeyPress = (e: Webapi.Dom.KeyboardEvent.t) => {
      let numOptions = Js.Array.length(options);
      switch (Webapi.Dom.KeyboardEvent.key(e)) {
      | "Esc"
      | "Escape" => onSelect(None)
      | "ArrowUp" =>
        setFocusedIndex(i => (i - 1 + numOptions) mod numOptions);
        Webapi.Dom.KeyboardEvent.preventDefault(e);
      | "ArrowDown" =>
        setFocusedIndex(i => (i + 1) mod numOptions);
        Webapi.Dom.KeyboardEvent.preventDefault(e);
      | "Enter" => onSelect(Belt.Array.get(options, focusedIndex))
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
                  let isFocused = focusedIndex == i;
                  <SelectOption
                    option
                    isSelected
                    isFocused
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
    (
      ~getOptions,
      ~selectedOption,
      ~onChange=?,
      ~label=?,
      ~placeholder=?,
      ~forceOption=false,
      (),
    ) => {
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

  let hasSelectedOption = Belt.Option.isNone(selectedOption);
  let onInputChange =
    React.useCallback3(
      e => {
        let value: string = ReactEvent.Form.currentTarget(e)##value;
        setTextValue(_ => value);
        setShowOptions(_ => true);
        if (!forceOption && hasSelectedOption) {
          switch (onChange) {
          | Some(onChange) => onChange(None)
          | None => ()
          };
        };
      },
      (forceOption, hasSelectedOption, onChange),
    );
  let blurTimeout = React.useRef(None);
  let onBlur =
    React.useCallback1(
      _ =>
        React.Ref.setCurrent(
          blurTimeout,
          Some(
            Js.Global.setTimeout(
              () => {
                switch (selectedOption) {
                | Some(selectedOption) =>
                  setTextValue(_ => selectedOption.label)
                | None => ()
                };
                setShowOptions(_ => false);
              },
              100,
            ),
          ),
        ),
      [|selectedOption|],
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
    switch (onChange) {
    | Some(onChange) =>
      switch (option) {
      | Some(option) => onChange(Some(option))
      | None =>
        if (!forceOption) {
          onChange(None);
        }
      }
    | None => ()
    };
  };

  let options = getOptions(textValue);
  React.useEffect3(
    () => {
      if (forceOption && Belt.Option.isNone(selectedOption)) {
        switch (Belt.Array.get(options, 0)) {
        | Some(firstOption) =>
          switch (onChange) {
          | Some(onChange) => onChange(Some(firstOption))
          | None => ()
          }
        | None => ()
        };
      };
      None;
    },
    (forceOption, hasSelectedOption, onChange),
  );

  <div onFocus={React.useCallback0(onFocus)} onBlur>
    <TextInput
      value=textValue
      onChange=onInputChange
      ?label
      ?placeholder
      ref=inputRef
    />
    {showOptions
       ? {
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