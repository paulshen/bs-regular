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
  <Select getOptions selectedOption=None onChange={_ => ()} />;
};