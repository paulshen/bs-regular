module Styles = {
  open Css;
  let root = style([%style {|
    font-family: Inter;
  |}]);
  let button = style([%style {|
    margin-right: 8px;
  |}]);
};

[@react.component]
let make = () => {
  <div className=Styles.root>
    <div> {React.string("Hello")} </div>
    <div>
      <Button className=Styles.button> {React.string("primary")} </Button>
      <Button type_=Button.Secondary className=Styles.button>
        {React.string("secondary")}
      </Button>
    </div>
  </div>;
};