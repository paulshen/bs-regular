module Styles = {
  open Css;
  let row = style([display(`flex), justifyContent(`flexEnd)]);
};

let states = [|
  "AK",
  "AL",
  "AR",
  "AZ",
  "CA",
  "CO",
  "CT",
  "DE",
  "FL",
  "GA",
  "HI",
  "IA",
  "ID",
  "IL",
  "IN",
  "KS",
  "KY",
  "LA",
  "MA",
  "MD",
  "ME",
  "MI",
  "MN",
  "MO",
  "MS",
  "MT",
  "NC",
  "ND",
  "NE",
  "NH",
  "NJ",
  "NM",
  "NV",
  "NY",
  "OH",
  "OK",
  "OR",
  "PA",
  "RI",
  "SC",
  "SD",
  "TN",
  "TX",
  "UT",
  "VA",
  "VT",
  "WA",
  "WI",
  "WV",
  "WY",
|];
let stateOptions =
  Js.Array.map((state): Select.selectOption => {label: state}, states);
let getStateOptions = value => {
  let lowercaseValue = Js.String.toLowerCase(value);
  Js.Array.filter(
    (option: Select.selectOption) =>
      Js.String.startsWith(
        lowercaseValue,
        Js.String.toLowerCase(option.label),
      ),
    stateOptions,
  )
  |> Js.Array.slice(~start=0, ~end_=8);
};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => None);
  let onStateChange = React.useCallback0(option => setState(_ => option));
  <div>
    <div className=Spacing.marginBottom16>
      <TextInput label="Street Address" placeholder="1 Folsom Street" />
    </div>
    <Grid.row className=Spacing.marginBottom16>
      <Grid.cell span=6>
        <TextInput label="City" placeholder="San Francisco" />
      </Grid.cell>
      <Grid.cell span=6>
        <Select
          getOptions=getStateOptions
          label="State"
          selectedOption=state
          onChange=onStateChange
          placeholder="CA"
          forceOption=true
        />
      </Grid.cell>
    </Grid.row>
    <div className=Styles.row>
      <Button type_=Button.Secondary> {React.string("Save")} </Button>
    </div>
  </div>;
};