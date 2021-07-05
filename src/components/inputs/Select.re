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

type selectOption = {label: string};

module SelectOption = {
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
          Webapi.Dom.(
            element |> Element.unsafeAsHtmlElement |> scrollToElement
          );
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
      ref={ReactDOM.Ref.domRef(domRef)}>
      {React.string(option.label)}
    </div>;
  };
};

module SelectOptions = {
  [@react.component]
  let make =
      (
        ~options: array(selectOption),
        ~selectedOption,
        ~onSelect,
        ~onMouseDown,
        ~contextRef: React.ref(Js.Nullable.t(Dom.element)),
      ) => {
    let (focusedIndex, setFocusedIndex) =
      React.useState(() =>
        switch (selectedOption) {
        | Some(selectedOption) =>
          switch (Js.Array.indexOf(selectedOption, options)) {
          | (-1) => 0
          | index => index
          }
        | None => 0
        }
      );

    let keyFilter = React.useRef("");
    let keyFilterTimeoutRef = React.useRef(None);

    let clearKeyFilterTimeout = () => {
      switch (keyFilterTimeoutRef.current) {
      | Some(keyFilterTimeout) =>
        Js.Global.clearTimeout(keyFilterTimeout);
        keyFilterTimeoutRef.current = None;
      | None => ()
      };
    };
    let onKeyPress = (e: Webapi.Dom.KeyboardEvent.t) => {
      clearKeyFilterTimeout();

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
      | key =>
        if (String.length(key) == 1) {
          open Char;
          let lowercaseKey = code(lowercase_ascii(key.[0]));
          if (lowercaseKey >= code('a') && lowercaseKey <= code('z')) {
            let keyFilterStr =
              keyFilter.current ++ String.lowercase_ascii(key);
            switch (
              Js.Array.findIndex(
                (option: selectOption) =>
                  Js.String.startsWith(
                    keyFilterStr,
                    Js.String.toLowerCase(option.label),
                  ),
                options,
              )
            ) {
            | (-1) => ()
            | firstMatchingOptionIndex =>
              setFocusedIndex(_ => firstMatchingOptionIndex)
            };
            keyFilter.current = keyFilterStr;
          };
          keyFilterTimeoutRef.current =
            Some(
              Js.Global.setTimeout(
                () => {
                  keyFilter.current = "";
                  keyFilterTimeoutRef.current = None;
                },
                300,
              ),
            );
        }
      };
    };

    let onSelectRef = React.useRef(onSelect);
    React.useEffect1(
      () => {
        onSelectRef.current = onSelect;
        None;
      },
      [|onSelect|],
    );
    let contextRefRef = React.useRef(contextRef);
    React.useEffect1(
      () => {
        contextRefRef.current = contextRef;
        None;
      },
      [|contextRef|],
    );

    let layerRef = React.useRef(Js.Nullable.null);
    React.useEffect0(() => {
      open Webapi.Dom;
      let onClick = e => {
        let target = MouseEvent.target(e);
        let layerDiv =
          Belt.Option.getExn(Js.Nullable.toOption(layerRef.current));
        let contextElement =
          Belt.Option.getExn(Js.Nullable.toOption(contextRef.current));
        let targetElement = EventTarget.unsafeAsElement(target);
        if (!Element.contains(targetElement, layerDiv)
            && !Element.contains(targetElement, contextElement)) {
          let onSelect = onSelectRef.current;
          onSelect(None);
        };
      };
      Document.addClickEventListener(onClick, document);
      Some(
        () => {
          Document.removeClickEventListener(onClick, document);
          clearKeyFilterTimeout();
        },
      );
    });

    let scrollToElement =
      React.useCallback0(optionElement => {
        let layerDiv =
          Belt.Option.getExn(Js.Nullable.toOption(layerRef.current));
        open Webapi.Dom;
        open Webapi.Dom.HtmlElement;
        let layerDiv = layerDiv |> Element.unsafeAsHtmlElement;
        let layerTop = int_of_float(layerDiv |> scrollTop);
        let layerHeight = layerDiv |> offsetHeight;
        let layerBottom = layerTop + layerHeight;

        let optionTop = optionElement |> offsetTop;
        let optionBottom = optionTop + offsetHeight(optionElement);

        if (optionTop < layerTop) {
          setScrollTop(layerDiv, float_of_int(optionTop));
        } else if (optionBottom > layerBottom) {
          setScrollTop(layerDiv, float_of_int(optionBottom - layerHeight));
        };
      });

    <ContextLayer position=ContextLayer.Bottom contextRef onKeyPress>
      {(~position as _) => {
         let inputElement =
           Belt.Option.getExn(Js.Nullable.toOption(contextRef.current));
         let style =
           ReactDOM.Style.make(
             ~width=
               string_of_int(Webapi.Dom.Element.clientWidth(inputElement))
               ++ "px",
             (),
           );
         <div
           className=Styles.optionsLayer
           onMouseDown
           style
           ref={ReactDOM.Ref.domRef(layerRef)}>
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
                    scrollToElement
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
// type selectOption = SelectOptionType.selectOption;

[@react.component]
let make =
    (
      ~getOptions,
      ~selectedOption: option(selectOption),
      ~onChange=?,
      ~label=?,
      ~placeholder=?,
      ~withTextInput=true,
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
      (e: ReactEvent.Form.t) => {
        let value: string = e |> ReactEvent.Form.target(e)##value;
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
        blurTimeout.current =
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
      [|selectedOption|],
    );
  let onFocus = _ => {
    switch (blurTimeout.current) {
    | Some(timeout) =>
      Js.Global.clearTimeout(timeout);
      blurTimeout.current = None;
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
    {withTextInput
       ? <TextInput
           value=textValue
           onChange=onInputChange
           ?label
           ?placeholder
           ref=inputRef
         />
       : <TextInput.Static
           ?label
           tabIndex=0
           onClick={_ => setShowOptions(_ => true)}
           ref=inputRef>
           {switch (selectedOption) {
            | Some(selectedOption) => React.string(selectedOption.label)
            | None => React.null
            }}
         </TextInput.Static>}
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
