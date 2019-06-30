module Styles = {
  open Css;
  let container = style([display(`flex), justifyContent(`center)]);
  let root = style([%style {|
    padding: 64px 32px;
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

  let cardPink = style([backgroundColor(`hex(Colors.pink))]);
};

let repeatElement = (num: int, render) => {
  let rv = [||];
  for (i in 0 to num - 1) {
    Js.Array.push(render(i), rv) |> ignore;
  };
  rv;
};

[@react.component]
let make = () => {
  <Layer.provider>
    <div className=Styles.container>
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
        <div className=Styles.section>
          <Text.header> {React.string("Card")} </Text.header>
          <Grid.row>
            <Grid.cell span=6>
              <Card className=Styles.cardPink>
                <Text.smallBodyBold>
                  {React.string("ReasonReact")}
                </Text.smallBodyBold>
                <Text.smallBody>
                  {React.string(
                     "ReasonReact uses functions and React Hooks to compose the component of your application. Let's look at how a component is written and then break down some of the things happening.",
                   )}
                </Text.smallBody>
              </Card>
            </Grid.cell>
            <Grid.cell span=6>
              <Card>
                <Text.smallBodyBold>
                  {React.string("What & Why")}
                </Text.smallBodyBold>
                <Text.smallBody>
                  {React.string(
                     "By leveraging the latter's great type system, expressive language features and smooth interoperability with JS, ReasonReact packs ReactJS' features into an API that is:",
                   )}
                  <ul>
                    <li> {React.string("Safe and statically typed")} </li>
                    <li> {React.string("Simple and lean")} </li>
                    <li>
                      {React.string(
                         "Familiar and easy to insert into an existing ReactJS codebase",
                       )}
                    </li>
                    <li>
                      {React.string(
                         "Well thought-out (made by the creator of ReactJS himself!)",
                       )}
                    </li>
                  </ul>
                </Text.smallBody>
              </Card>
            </Grid.cell>
          </Grid.row>
        </div>
      </div>
      <Modals />
      <Layer.container />
    </div>
  </Layer.provider>;
};