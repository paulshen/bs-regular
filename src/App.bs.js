// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var React = require("react");
var Text$ReactHooksTemplate = require("./components/Text.bs.js");
var Button$ReactHooksTemplate = require("./components/Button.bs.js");
var Divider$ReactHooksTemplate = require("./components/Divider.bs.js");

var root = Css.style(/* :: */[
      Css.fontFamily("Inter"),
      /* :: */[
        Css.padding(Css.px(32)),
        /* [] */0
      ]
    ]);

var button = Css.style(/* :: */[
      Css.marginRight(Css.px(8)),
      /* [] */0
    ]);

var section = Css.style(/* :: */[
      Css.marginBottom(Css.px(32)),
      /* :: */[
        Css.maxWidth(Css.px(640)),
        /* [] */0
      ]
    ]);

var Styles = /* module */[
  /* root */root,
  /* button */button,
  /* section */section
];

function App(Props) {
  return React.createElement("div", {
              className: root
            }, React.createElement("div", {
                  className: section
                }, React.createElement(Text$ReactHooksTemplate.header, {
                      children: "Buttons"
                    }), React.createElement(Button$ReactHooksTemplate.make, {
                      children: "primary",
                      className: button
                    }), React.createElement(Button$ReactHooksTemplate.make, {
                      type_: /* Secondary */1,
                      children: "secondary",
                      className: button
                    })), React.createElement("div", {
                  className: section
                }, React.createElement(Divider$ReactHooksTemplate.make, { }), React.createElement(Text$ReactHooksTemplate.smallHeader, {
                      children: "Header"
                    }), React.createElement(Text$ReactHooksTemplate.body, {
                      children: "Such a riot of sea and wind strews the whole extent of beach with whatever has been lost or thrown overboard, or torn out of sunken ships. Many a man has made a good week's work in a single day by what he has found while walking along the Beach when the surf was down."
                    })));
}

var make = App;

exports.Styles = Styles;
exports.make = make;
/* root Not a pure module */
