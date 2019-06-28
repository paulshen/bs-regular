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
let make = (~renderModal) => {
  let modalKeyRef = React.useRef(None);
  let renderModalRef = React.useRef(renderModal);
  React.useLayoutEffect0(() => {
    let modalKey = Modals.openModal(~renderModal);
    modalKeyRef->React.Ref.setCurrent(Some(modalKey));
    Some(() => Modals.closeModal(modalKey));
  });
  React.useLayoutEffect1(
    () => {
      if (React.Ref.current(renderModalRef) !== renderModal) {
        Modals.updateModal(
          Belt.Option.getExn(React.Ref.current(modalKeyRef)),
          ~renderModal,
        );
        renderModalRef->React.Ref.setCurrent(renderModal);
      };
      None;
    },
    [|renderModal|],
  );
  React.null;
};