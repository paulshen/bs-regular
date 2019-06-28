module Styles = {
  open Css;
  let root = style([%style {|
    padding: 32px;
  |}]);
  let button = style([%style {|
    margin-right: 8px;
  |}]);
  let section =
    style([%style {|
    margin-bottom: 32px;
    max-width: 640px;
  |}]);
  let gridRow = style([%style {|
    margin-bottom: 16px;
  |}]);
  let gridCell = style([backgroundColor(`hex(Colors.primary475))]);
  let contextLayer = style([backgroundColor(`hex(Colors.primary475))]);
};

let repeatElement = (num: int, render) => {
  let rv = [||];
  for (i in 0 to num - 1) {
    Js.Array.push(render(i), rv) |> ignore;
  };
  rv;
};

module ContextLayerExample = {
  [@react.component]
  let make = () => {
    let (showLayer, setShowLayer) = React.useState(() => false);
    let divRef = React.useRef(Js.Nullable.null);
    React.useEffect0(() => {
      setShowLayer(_ => true);
      None;
    });
    <>
      <div ref={ReactDOMRe.Ref.domRef(divRef)}>
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
};

module SelectExample = {
  let options: array(Select.option) = [|{label: "FB"}, {label: "GOOGL"}|];

  [@react.component]
  let make = () => {
    let getOptions = value => {
      let lowercaseValue = Js.String.toLowerCase(value);
      Js.Array.filter(
        (option: Select.option) =>
          Js.String.startsWith(
            lowercaseValue,
            Js.String.toLowerCase(option.label),
          ),
        options,
      );
    };
    <Select getOptions />;
  };
};

module ModalExample = {
  [@react.component]
  let make = () => {
    let (showModal, setShowModal) = React.useState(() => false);
    let (count, setCount) = React.useState(() => 1);
    let renderModal =
      React.useCallback1(
        () =>
          <Modal.root>
            <Text.body> {React.string("Modal")} </Text.body>
            <div>
              <Button onClick={_ => setCount(count => count + 1)}>
                {React.string(string_of_int(count))}
              </Button>
            </div>
            <Button onClick={_ => setShowModal(_ => false)}>
              {React.string("Hide")}
            </Button>
          </Modal.root>,
        [|count|],
      );
    <>
      <Button onClick={_ => setShowModal(_ => true)}>
        {React.string("Show modal")}
      </Button>
      {showModal ? <Modal renderModal /> : React.null}
    </>;
  };
};

[@react.component]
let make = () => {
  <Layer.provider>
    <div className=Styles.root>
      <div className=Styles.section>
        <Text.header> {React.string("Buttons")} </Text.header>
        <Button className=Styles.button> {React.string("primary")} </Button>
        <Button type_=Button.Secondary className=Styles.button>
          {React.string("secondary")}
        </Button>
      </div>
      <div className=Styles.section>
        <Divider />
        <Text.smallHeader> {React.string("Header")} </Text.smallHeader>
        <Text.body>
          {React.string(
             "Such a riot of sea and wind strews the whole extent of beach with whatever has been lost or thrown overboard, or torn out of sunken ships. Many a man has made a good week's work in a single day by what he has found while walking along the Beach when the surf was down.",
           )}
        </Text.body>
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("Grid")} </Text.header>
        <Grid.row className=Styles.gridRow>
          <Grid.cell span=6>
            <div className=Styles.gridCell> {React.string("6")} </div>
          </Grid.cell>
          <Grid.cell span=6>
            <div className=Styles.gridCell> {React.string("6")} </div>
          </Grid.cell>
        </Grid.row>
        <Grid.row className=Styles.gridRow>
          {React.array(
             repeatElement(3, i =>
               <Grid.cell span=4 key={string_of_int(i)}>
                 <div className=Styles.gridCell> {React.string("4")} </div>
               </Grid.cell>
             ),
           )}
        </Grid.row>
        <Grid.row className=Styles.gridRow>
          {React.array(
             repeatElement(4, i =>
               <Grid.cell span=3 key={string_of_int(i)}>
                 <div className=Styles.gridCell> {React.string("3")} </div>
               </Grid.cell>
             ),
           )}
        </Grid.row>
        <Grid.row className=Styles.gridRow>
          {React.array(
             repeatElement(6, i =>
               <Grid.cell span=2 key={string_of_int(i)}>
                 <div className=Styles.gridCell> {React.string("2")} </div>
               </Grid.cell>
             ),
           )}
        </Grid.row>
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("Inputs")} </Text.header>
        <Grid.row className=Spacing.marginBottom16>
          <Grid.cell span=6>
            <TextInput label="First name" placeholder="Harry" />
          </Grid.cell>
          <Grid.cell span=6>
            <TextInput label="Last name" placeholder="Potter" />
          </Grid.cell>
        </Grid.row>
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("ContextLayer")} </Text.header>
        <ContextLayerExample />
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("Tooltip")} </Text.header>
        <Tooltip text="tooltip">
          {(~contextRef, ~onMouseEnter, ~onMouseLeave) =>
             <Button ref=contextRef onMouseEnter onMouseLeave>
               {React.string("Hover me")}
             </Button>}
        </Tooltip>
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("Select")} </Text.header>
        <SelectExample />
      </div>
      <div className=Styles.section>
        <Text.header> {React.string("Modal")} </Text.header>
        <ModalExample />
      </div>
    </div>
    <Modals />
    <Layer.container />
  </Layer.provider>;
};