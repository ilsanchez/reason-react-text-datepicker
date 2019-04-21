let handle = (event: option(Js.Date.t)) => {
  switch event {
    | Some(evt') =>  Js.log("cambio: " ++ evt' -> Js.Date.toDateString)
    | None => Js.log("Invalid Date")
  }
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
      onChange: {handle}
    }
  />, 
  "index1"
);
