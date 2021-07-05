Css.global("body", [Css.fontFamily(`custom("Inter"))]);


switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<App />, root)
| None => Js.log("Coudn't find #root element to mount the React app.")
};
