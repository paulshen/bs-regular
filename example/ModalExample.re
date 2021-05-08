[@react.component]
let make = () => {
  let (showModal, setShowModal) = React.useState(() => false);
  let (count, setCount) = React.useState(() => 1);
  let renderModal =
    React.useCallback1(
      () =>
        <Modal.Root>
          <Text.Body> {React.string("Modal")} </Text.Body>
          <div>
            <Button onClick={_ => setCount(count => count + 1)}>
              {React.string(string_of_int(count))}
            </Button>
          </div>
          <Button onClick={_ => setShowModal(_ => false)}>
            {React.string("Hide")}
          </Button>
        </Modal.Root>,
      [|count|],
    );
  let onCloseRequest = React.useCallback0(() => setShowModal(_ => false));
  <>
    <Button onClick={_ => setShowModal(_ => true)}>
      {React.string("Show modal")}
    </Button>
    {showModal ? <Modal renderModal onCloseRequest /> : React.null}
  </>;
};
