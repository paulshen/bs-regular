module Styles = {
  open Css;
  let layer =
    style([
      backgroundColor(`hex(Colors.primary200)),
      borderRadius(`px(2)),
      color(`hex(Colors.primary500)),
      fontSize(`px(14)),
      padding2(~v=`px(6), ~h=`px(12)),
    ]);
};

[@react.component]
let layer = (~text, ~contextRef, ~position=?, ()) => {
  <ContextLayer ?position contextRef>
    {(~position as _) =>
       <div className=Styles.layer> {React.string(text)} </div>}
  </ContextLayer>;
};

[@react.component]
let make = (~text, ~position=?, ~children) => {
  let contextRef = React.useRef(Js.Nullable.null);
  let (showTooltip, setShowTooltip) = React.useState(() => false);
  let onMouseEnter = React.useCallback0(_ => setShowTooltip(_ => true));
  let onMouseLeave = React.useCallback0(_ => setShowTooltip(_ => false));
  <>
    {children(
       ~contextRef=ReactDOM.Ref.domRef(contextRef),
       ~onMouseEnter,
       ~onMouseLeave,
     )}
    {showTooltip
       ? layer(layerProps(~contextRef, ~text, ~position?, ())) : React.null}
  </>;
};

let container = (~text, ~position=?, ~children, ~className=?, ()) => {
  make(
    makeProps(
      ~text,
      ~position?,
      ~children=
        (~contextRef, ~onMouseEnter, ~onMouseLeave) =>
          <div ref=contextRef onMouseEnter onMouseLeave ?className>
            children
          </div>,
      (),
    ),
  );
};
