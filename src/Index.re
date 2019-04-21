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
      hints: {true},
      dayHint: {"DD"},
      monthHint: {"MM"},
      yearHint: {"YYYY"},
      className: {""},
      onChange: {handle}
    }
  />, 
  "index1"
);
