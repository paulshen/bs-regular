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

[@react.component]
let root = (~children) => {
  <div className=Styles.root> children </div>;
};

[@react.component]
let make = (~renderModal, ~onCloseRequest=?, ()) => {
  let modalKeyRef = React.useRef(None);
  let renderModalRef = React.useRef(renderModal);
  let onCloseRequestRef = React.useRef(onCloseRequest);
  React.useLayoutEffect0(() => {
    let modalKey = Modals.openModal(~renderModal, ~onCloseRequest);
    modalKeyRef->React.Ref.setCurrent(Some(modalKey));
    Some(() => Modals.closeModal(modalKey));
  });
  React.useLayoutEffect2(
    () => {
      if (React.Ref.current(renderModalRef) !== renderModal
          || React.Ref.current(onCloseRequestRef) !== onCloseRequest) {
        Modals.updateModal(
          Belt.Option.getExn(React.Ref.current(modalKeyRef)),
          ~renderModal,
          ~onCloseRequest,
        );
        renderModalRef->React.Ref.setCurrent(renderModal);
        onCloseRequestRef->React.Ref.setCurrent(onCloseRequest);
      };
      None;
    },
    (renderModal, onCloseRequest),
  );
  React.null;
};