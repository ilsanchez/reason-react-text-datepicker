type textInputProps = {
  className: string,
  hintText: string,
  value: string,
  maxLength: int,
  name: string,
  onInputChange: (ReactEvent.Form.t) => unit
};

[@react.component]
let make = (~props: textInputProps) => {
  <input
    type_="text"
    className={"rtdp-input" ++ props.className}
    placeholder={props.hintText}
    value={props.value}
    onChange={props.onInputChange}
    name={props.name}
    maxLength={props.maxLength}
  />
};