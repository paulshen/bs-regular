module Styles = {
  open Css;
  let container = style([display(`flex), justifyContent(`center)]);
  let root = style([padding2(~v=`px(64), ~h=`px(32))]);
  let button = style([marginRight(`px(8))]);
  let section = style([marginBottom(`px(32)), maxWidth(`px(640))]);
  let gridRow = style([marginBottom(`px(16))]);
  let gridCell = style([backgroundColor(`hex(Colors.primary475))]);

  let cardPink = style([backgroundColor(`hex(Colors.pink))]);
  let badge = style([marginRight(`px(8))]);
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
  <Layer.Provider>
    <div className=Styles.container>
      <div className=Styles.root>
        <div className=Styles.section>
          <Text.Header> {React.string("Buttons")} </Text.Header>
          <Button className=Styles.button> {React.string("primary")} </Button>
          <Button type_=Button.Secondary className=Styles.button>
            {React.string("secondary")}
          </Button>
        </div>
        <div className=Styles.section>
          <Divider />
          <Text.SmallHeader> {React.string("Header")} </Text.SmallHeader>
          <Text.Body>
            {React.string(
               "Such a riot of sea and wind strews the whole extent of beach with whatever has been lost or thrown overboard, or torn out of sunken ships. Many a man has made a good week's work in a single day by what he has found while walking along the Beach when the surf was down.",
             )}
          </Text.Body>
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Grid")} </Text.Header>
          <Grid.Row className=Styles.gridRow>
            <Grid.Cell span=6>
              <div className=Styles.gridCell> {React.string("6")} </div>
            </Grid.Cell>
            <Grid.Cell span=6>
              <div className=Styles.gridCell> {React.string("6")} </div>
            </Grid.Cell>
          </Grid.Row>
          <Grid.Row className=Styles.gridRow>
            {React.array(
               repeatElement(3, i =>
                 <Grid.Cell span=4 key={string_of_int(i)}>
                   <div className=Styles.gridCell> {React.string("4")} </div>
                 </Grid.Cell>
               ),
             )}
          </Grid.Row>
          <Grid.Row className=Styles.gridRow>
            {React.array(
               repeatElement(4, i =>
                 <Grid.Cell span=3 key={string_of_int(i)}>
                   <div className=Styles.gridCell> {React.string("3")} </div>
                 </Grid.Cell>
               ),
             )}
          </Grid.Row>
          <Grid.Row className=Styles.gridRow>
            {React.array(
               repeatElement(6, i =>
                 <Grid.Cell span=2 key={string_of_int(i)}>
                   <div className=Styles.gridCell> {React.string("2")} </div>
                 </Grid.Cell>
               ),
             )}
          </Grid.Row>
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Inputs")} </Text.Header>
          <FormExample />
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("ContextLayer")} </Text.Header>
          <ContextLayerExample />
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Tooltip")} </Text.Header>
          <Tooltip text="tooltip">
            {(~contextRef, ~onMouseEnter, ~onMouseLeave) =>
               <Button ref=contextRef onMouseEnter onMouseLeave>
                 {React.string("Hover me")}
               </Button>}
          </Tooltip>
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Select")} </Text.Header>
          <SelectExample />
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Modal")} </Text.Header>
          <ModalExample />
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Card")} </Text.Header>
          <Grid.Row>
            <Grid.Cell span=6>
              <Card className=Styles.cardPink>
                <Text.SmallBodyBold>
                  {React.string("ReasonReact")}
                </Text.SmallBodyBold>
                <Text.SmallBody>
                  {React.string(
                     "ReasonReact uses functions and React Hooks to compose the component of your application. Let's look at how a component is written and then break down some of the things happening.",
                   )}
                </Text.SmallBody>
              </Card>
            </Grid.Cell>
            <Grid.Cell span=6>
              <Card>
                <Text.SmallBodyBold>
                  {React.string("What & Why")}
                </Text.SmallBodyBold>
                <Text.SmallBody>
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
                </Text.SmallBody>
              </Card>
            </Grid.Cell>
          </Grid.Row>
        </div>
        <div className=Styles.section>
          <Text.Header> {React.string("Badge")} </Text.Header>
          <div>
            <Badge className=Styles.badge> {React.string("8")} </Badge>
            <Badge className=Styles.badge> {React.string("24")} </Badge>
            <Badge className=Styles.badge> {React.string("Unread")} </Badge>
          </div>
        </div>
      </div>
      <Modals />
      <Layer.Container />
    </div>
  </Layer.Provider>;
};
