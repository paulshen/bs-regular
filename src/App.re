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
};

[@react.component]
let make = () => {
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
  </div>;
};