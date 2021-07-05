module Styles = {
  open Css;
  let contextLayer = style([backgroundColor(`hex(Colors.primary475))]);
};

[@react.component]
let make = () => {
  let (showLayer, setShowLayer) = React.useState(() => false);
  let divRef = React.useRef(Js.Nullable.null);
  React.useEffect0(() => {
    setShowLayer(_ => true);
    None;
  });
  <>
    <div ref={ReactDOM.Ref.domRef(divRef)}>
      {React.string("Context")}
    </div>
    {showLayer
       ? <>
           <ContextLayer position=ContextLayer.Top contextRef=divRef>
             {(~position as _) =>
                <div className=Styles.contextLayer>
                  {React.string("ContextLayer")}
                </div>}
           </ContextLayer>
           <ContextLayer position=ContextLayer.Bottom contextRef=divRef>
             {(~position as _) =>
                <div className=Styles.contextLayer>
                  {React.string("ContextLayer")}
                </div>}
           </ContextLayer>
           <ContextLayer position=ContextLayer.Left contextRef=divRef>
             {(~position as _) =>
                <div className=Styles.contextLayer>
                  {React.string("ContextLayer")}
                </div>}
           </ContextLayer>
           <ContextLayer position=ContextLayer.Right contextRef=divRef>
             {(~position as _) =>
                <div className=Styles.contextLayer>
                  {React.string("ContextLayer")}
                </div>}
           </ContextLayer>
         </>
       : React.null}
  </>;
};
