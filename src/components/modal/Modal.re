module Styles = {
  open Css;
  let root =
    style([
      backgroundColor(`hex(Colors.primary500)),
      borderRadius(`px(4)),
      width(`px(512)),
      height(`px(256)),
    ]);
};

module Root = {
  [@react.component]
  let make = (~children) => {
    <div className=Styles.root> children </div>;
  };
};

[@react.component]
let make = (~renderModal, ~onCloseRequest=?, ()) => {
  let modalKeyRef = React.useRef(None);
  let renderModalRef = React.useRef(renderModal);
  let onCloseRequestRef = React.useRef(onCloseRequest);
  React.useLayoutEffect0(() => {
    let modalKey = Modals.openModal(~renderModal, ~onCloseRequest);
    modalKeyRef.current = Some(modalKey);
    Some(() => Modals.closeModal(modalKey));
  });
  React.useLayoutEffect2(
    () => {
      if (renderModalRef.current !== renderModal
          || onCloseRequestRef.current !== onCloseRequest) {
        Modals.updateModal(
          Belt.Option.getExn(modalKeyRef.current),
          ~renderModal,
          ~onCloseRequest,
        );
        renderModalRef.current = renderModal;
        onCloseRequestRef.current = onCloseRequest;
      };
      None;
    },
    (renderModal, onCloseRequest),
  );
  React.null;
};
