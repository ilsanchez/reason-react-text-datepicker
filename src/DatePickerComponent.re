
type textDatePickerProps = {
  value: option(string),
  hints: bool,
  dayHint: string,
  monthHint: string,
  yearHint: string,
  className: string,
  maxLength: int,
  onChange: (unit) => Js.Date.t
};

let getDaysInMonth = (month: int, year: int): int => {
  switch month {
  | 1 => year mod 4 == 0 || year mod 400 == 0 
    ? 29
    : 28
  | 3 | 5 | 8 | 10 => 30
  | _ => 31
  };
}

let isAValidPartialDate = (day: int, month: int, year: int): bool => {
  let fixedMonth = month - 1;
  fixedMonth >= 0 && fixedMonth < 12 && day > 0 && day <= getDaysInMonth(fixedMonth, year);
}

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

[@react.component]
let make = (~props: textDatePickerProps) => {
  let dateValue = getInitialDate(props.value);

  let (day, setDay) = React.useState(() => dateValue -> Js.Date.getDay -> truncate);
  let (month, setMonth) = React.useState(() => truncate(Js.Date.getMonth(dateValue) +. 1.0));
  let (year, setYear) = React.useState(() => dateValue -> Js.Date.getFullYear -> truncate);

  React.useEffect(() => {
    let floatDay = float_of_int(day);
    let floatMonth = float_of_int(month);
    let floatYear = float_of_int(year);
    let valid = isAValidPartialDate(day, month, year);
    switch valid {
      | true => props.onChange(Js.Date.makeWithYMD(~year = floatYear, ~month = floatMonth, ~date = floatDay))
      | false => props.onChange("")
    }
  });

  let onInputChange = (event) => {
    let target = ReactEvent.Form.target(event);
    
    let value: string = target##value;
    let name: string = target##name;

    let _ = switch name {
      | "day-input" => setDay(_ => int_of_string(value))
      | "month-input" => setMonth(_ => int_of_string(value) + 1)
      | "year-input" => setYear(_ => int_of_string(value))
    }

    Js.log(value ++ name);
  };

  <span className="rtdp">
      <span className="rtdp-inner">
        <TextInput
          props={
            name: "day-input",
            className:"rtdp-day",
            value:{string_of_int(day)},
            hintText:{props.hints ? props.dayHint : ""},
            onInputChange:onInputChange,
            maxLength:{2}
          }
        />
        // <Separator />
        <TextInput
          props = {
            name:"month-input",
            className:"rtdp-month",
            value:{string_of_int(month)},
            hintText:{props.hints ? props.monthHint : ""},
            onInputChange:onInputChange,
            maxLength:{2}
          }
        />
        // <Separator />
        <TextInput
          props = {
            name:"year-input",
            className:"rtdp-year",
            value:{string_of_int(year)},
            hintText:{props.hints ? props.yearHint : ""},
            onInputChange:onInputChange,
            maxLength:{4}
          }
        />
      </span>
    </span>
}
