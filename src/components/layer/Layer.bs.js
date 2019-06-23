// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDom = require("react-dom");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

var context = React.createContext(/* record */[
      /* container */undefined,
      /* setContainer */(function (param) {
          return /* () */0;
        })
    ]);

function makeProps(value, children, param) {
  return {
          value: value,
          children: children
        };
}

var make = context.Provider;

var ContextProvider = /* module */[
  /* makeProps */makeProps,
  /* make */make
];

function Layer(Props) {
  var children = Props.children;
  var layerContainer = Belt_Option.getExn(React.useContext(context)[/* container */0]);
  return ReactDom.createPortal(children, layerContainer);
}

function Layer$provider(Props) {
  var children = Props.children;
  var match = React.useState((function () {
          return undefined;
        }));
  var setContainer = match[1];
  var setContainerCallback = React.useCallback((function (element) {
          return Curry._1(setContainer, (function (param) {
                        return Caml_option.some(element);
                      }));
        }), ([]));
  return React.createElement(make, makeProps(/* record */[
                  /* container */match[0],
                  /* setContainer */setContainerCallback
                ], children, /* () */0));
}

function Layer$container(Props) {
  var domRef = React.useRef(null);
  var setContainer = React.useContext(context)[/* setContainer */1];
  React.useLayoutEffect((function () {
          var element = Belt_Option.getExn(Caml_option.nullable_to_opt(domRef.current));
          Curry._1(setContainer, element);
          return undefined;
        }), ([]));
  return React.createElement("div", {
              ref: domRef
            });
}

var make$1 = Layer;

var provider = Layer$provider;

var container = Layer$container;

exports.context = context;
exports.ContextProvider = ContextProvider;
exports.make = make$1;
exports.provider = provider;
exports.container = container;
/* context Not a pure module */
