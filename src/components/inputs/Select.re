module Styles = {
  open Css;
  let layer = style([border(`px(1), `solid, `hex(Colors.primary450))]);
  let option =
    style([
      borderBottom(`px(1), `solid, `hex(Colors.primary450)),
      padding2(~v=`px(8), ~h=`px(16)),
    ]);
};

type option = {label: string};

module SelectOption = {
  [@react.component]
  let make = (~option, ~onClick) => {
    <div onClick tabIndex=0 className=Styles.option>
      {React.string(option.label)}
    </div>;
  };
};

module SelectOptions = {
  [@react.component]
  let make = (~options, ~onSelect, ~onMouseDown, ~contextRef) => {
    <ContextLayer position=ContextLayer.Bottom contextRef>
      {(~position as _) =>
         <div className=Styles.layer onMouseDown>
           {React.array(
              Js.Array.mapi(
                (option, i) =>
                  <SelectOption
                    option
                    onClick={_ => onSelect(option)}
                    key={string_of_int(i)}
                  />,
                options,
              ),
            )}
         </div>}
    </ContextLayer>;
  };
};

[@react.component]
let make = (~getOptions) => {
  let inputRef = React.useRef(Js.Nullable.null);
  let ((value, selectedOption), setValue) =
    React.useState(() => ("", None));
  let (focused, setFocused) = React.useState(() => false);
  let onChange =
    React.useCallback0(e => {
      let value: string = ReactEvent.Form.currentTarget(e)##value;
      setValue(_ => (value, None));
    });
  let blurTimeout = React.useRef(None);
  let onBlur =
    React.useCallback0(_ =>
      React.Ref.setCurrent(
        blurTimeout,
        Some(Js.Global.setTimeout(() => setFocused(_ => false), 100)),
      )
    );
  let onFocus = _ => {
    switch (React.Ref.current(blurTimeout)) {
    | Some(timeout) =>
      Js.Global.clearTimeout(timeout);
      React.Ref.setCurrent(blurTimeout, None);
    | None => ()
    };
    setFocused(_ => true);
  };
  let onMouseDown = React.useCallback0(onFocus);
  let onSelect =
    React.useCallback(option => setValue(_ => (option.label, Some(option))));
  <div onFocus={React.useCallback0(onFocus)} onBlur>
    <TextInput value onChange ref=inputRef />
    {selectedOption == None && String.length(value) > 0 && focused
       ? {
         let options = getOptions(value);
         Array.length(options) > 0
           ? <SelectOptions
               options
               onSelect
               onMouseDown
               contextRef=inputRef
             />
           : React.null;
       }
       : React.null}
  </div>;
};