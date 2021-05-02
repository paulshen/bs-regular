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
          let keyFilterStr = keyFilter.current ++ String.lowercase_ascii(key);
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
         ReactDOMRe.Style.make(
           ~width=
             string_of_int(Webapi.Dom.Element.clientWidth(inputElement))
             ++ "px",
           (),
         );
       <div
         className=Styles.optionsLayer
         onMouseDown
         style
         ref={ReactDOMRe.Ref.domRef(layerRef)}>
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
