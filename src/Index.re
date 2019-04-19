let handle = (event) => {
  Js.log("cambio")
}

ReactDOMRe.renderToElementWithId(
  <DatePickerComponent 
    props = {
      value: None,
      hints: {false},
      dayHint: {""},
      monthHint: {""},
      yearHint: {""},
      className: {""},
      maxLength: {2},
      onChange: {handle}
    }
  />, 
  "index1"
);
