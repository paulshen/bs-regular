let options: array(Select.selectOption) = [|
  {label: "FB"},
  {label: "GOOGL"},
|];

[@react.component]
let make = () => {
  let getOptions = value => {
    let lowercaseValue = Js.String.toLowerCase(value);
    Js.Array.filter(
      (option: Select.selectOption) =>
        Js.String.startsWith(
          lowercaseValue,
          Js.String.toLowerCase(option.label),
        ),
      options,
    );
  };
  let (selectedOption, setSelectedOption) = React.useState(() => None);
  <Select
    getOptions
    selectedOption
    onChange={option => setSelectedOption(_ => option)}
  />;
};