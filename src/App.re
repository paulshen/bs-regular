module Styles = {
  open Css;
  let root =
    style([%style {|
    font-family: Inter;
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
            <TextInput placeholder="First name" />
          </Grid.cell>
          <Grid.cell span=6> <TextInput placeholder="Last name" /> </Grid.cell>
        </Grid.row>
      </div>
    </div>
    <Layer.container />
  </Layer.provider>;
};