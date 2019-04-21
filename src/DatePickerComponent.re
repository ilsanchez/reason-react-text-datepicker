
type textDatePickerProps = {
  value: option(string),
  hints: bool,
  dayHint: string,
  monthHint: string,
  yearHint: string,
  className: string,
  onChange: (option(Js.Date.t)) => unit
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

let isAValidPartialDate = (day_: int, month_: int, year_: int): bool => {
  let fixedMonth = month_ - 1;
  fixedMonth >= 0 && fixedMonth < 12 && day_ > 0 && day_ <= getDaysInMonth(fixedMonth, year_);
}

let isValidDate = (value: string): bool => {
  let dateWrapper = Js.Date.fromString(value);
  dateWrapper
  -> Js.Date.valueOf
  -> Js.Float.isNaN
};     

let getInitialDate = (value: option(string)): option(Js.Date.t) => {
  switch value {
  | None => None
  | Some(value) => isValidDate(value)
    ? Some(Js.Date.fromString(value))
    : Some(Js.Date.make())
  };
};

let validationRegExp = [%bs.re "/^[0-9]+$/g"];
let parseInputValue = (value: string): float => {
    let passed = Js.Re.test_(validationRegExp, value);
    let emptyString = Js.String.length(value) === 0;
    switch (passed, emptyString) {
      | (true, false) => float_of_string(value)
      | _ => 0.0
    }
};

[@react.component]
let make = (~props: textDatePickerProps) => {
  let dateValue = getInitialDate(props.value);

  let (day, setDay) = React.useState(() => 
    switch dateValue {
      | Some(d') => d' -> Js.Date.getDay -> truncate -> string_of_int
      | None => ""
    }
  );
  let (month, setMonth) = React.useState(() => 
    switch dateValue {
      | Some(d') => truncate(Js.Date.getMonth(d') +. 1.0) -> string_of_int
      | None => ""
    }
  );
  let (year, setYear) = React.useState(() => 
    switch dateValue {
      | Some(d') => d' -> Js.Date.getFullYear -> truncate -> string_of_int
      | None => "" 
    }
  );

  React.useEffect(() => {
    let floatDay = parseInputValue(day);
    let floatMonth = parseInputValue(month);
    let floatYear = parseInputValue(year);
    let valid = isAValidPartialDate(
      floatDay -> truncate, 
      floatMonth -> truncate, 
      floatYear -> truncate
    );
    Js.log("Parsed Values --> " ++
      floatDay -> Js.Float.toString ++ "/" ++ 
      floatMonth -> Js.Float.toString ++ "/" ++ 
      floatYear -> Js.Float.toString ++ "\n" ++
      "Original Values --> " ++
      day ++ "/" ++
      month ++ "/" ++
      year);
    switch valid {
      | true => {
          let date = Js.Date.makeWithYMD(~year = floatYear, ~month = floatMonth, ~date = floatDay, ());
          props.onChange(Some(date));
        }
      | false => props.onChange(None);      
    }
    Some(() => Js.log("Effect Called"));
  });

  let onInputChange = (event) => {
    let target = ReactEvent.Form.target(event);
    
    let value: string = target##value;
    let name: string = target##name;
    Js.log("On Change -> " ++ name ++ ": " ++ value);
    switch name {
      | "day-input" => setDay(_ => value)
      | "month-input" => setMonth(_ => value)
      | "year-input" => setYear(_ => value)
      | _ => ()
    }
  };

  <span className="rtdp">
      <span className="rtdp-inner">
        <TextInput
          props={
            name: "day-input",
            className:"rtdp-day",
            value:{day},
            hintText:{props.hints ? props.dayHint : ""},
            onInputChange:onInputChange,
            maxLength:{2}
          }
        />
        <span className="rtdp-separator">{ReasonReact.string("/")}</span>
        <TextInput
          props = {
            name:"month-input",
            className:"rtdp-month",
            value:{month},
            hintText:{props.hints ? props.monthHint : ""},
            onInputChange:onInputChange,
            maxLength:{2}
          }
        />
        <span className="rtdp-separator">{ReasonReact.string("/")}</span>
        <TextInput
          props = {
            name:"year-input",
            className:"rtdp-year",
            value:{year},
            hintText:{props.hints ? props.yearHint : ""},
            onInputChange:onInputChange,
            maxLength:{4}
          }
        />
      </span>
    </span>
}
