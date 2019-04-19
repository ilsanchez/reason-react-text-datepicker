
type textDatePickerProps = {
  value: option(string),
  hints: bool,
  dayHint: string,
  monthHint: string,
  yearHint: string,
  className: string,
  maxLength: int,
  onChange: (string) => string
};

let isValidDate = (value: string): bool => {
  let dateWrapper = Js.Date.fromString(value);
  dateWrapper
  -> Js.Date.valueOf
  -> Js.Float.isNaN
};     

let getInitialDate = (value: option(string)):Js.Date.t => {
  switch value {
  | None => Js.Date.make()
  | Some(value) => isValidDate(value)
    ? Js.Date.fromString(value)
    : Js.Date.make()
  };
};

type state= {
  day: string,
  month: string,
  year: string
};

type action = 
  | SetDay(string)
  | SetMonth(string)
  | SetYear(string);

[@react.component]
let make = (props: textDatePickerProps) => {
  let dateValue = getInitialDate(props.value);

  let (state, dispatch) = React.useReducer((state, action) => 
    switch action {
    | SetDay(value) => {...state, day: value}
    | SetMonth(value) => {...state, month: value}
    | SetYear(value) => {...state, year: value}
    }, {
      day: dateValue -> Js.Date.getDay -> Js.Float.toString,
      month: Js.Float.toString(Js.Date.getMonth(dateValue) +. 1.0),
      year: dateValue -> Js.Date.getFullYear -> Js.Float.toString
      }
  );

  let onInputChange = (event: ReactEvent.Form.t): unit => {
    dispatch(SetDay(""))
  };

  <span className="rtdp">
      <span className="rtdp-inner">
        <TextInput
          props={
            name: "day-input",
            className:"rtdp-day",
            value:{state.day},
            hintText:{props.hints ? props.dayHint : ""},
            onInputChange:{onInputChange},
            maxLength:{2}
          }
        />
        // <Separator />
        <TextInput
          props = {
            name:"month-input",
            className:"rtdp-month",
            value:{state.month},
            hintText:{props.hints ? props.monthHint : null},
            onInputChange:{onInputChange},
            maxLength:{2}
          }
        />
        // <Separator />
        <TextInput
          name="year-input"
          className="rtdp-year"
          value={state.year}
          hintText={props.hints ? props.yearHint : null}
          onInputChange={onInputChange}
          maxLength={4}
        />
      </span>
    </span>

}
