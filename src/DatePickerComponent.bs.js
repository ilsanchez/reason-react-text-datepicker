// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Styles$ReactHooksTemplate = require("./Styles.bs.js");
var TextInput$ReactHooksTemplate = require("./TextInput.bs.js");

function getDaysInMonth(month, year) {
  switch (month) {
    case 1 : 
        var match = year % 4 === 0 || year % 400 === 0;
        if (match) {
          return 29;
        } else {
          return 28;
        }
    case 2 : 
    case 4 : 
    case 6 : 
    case 7 : 
    case 9 : 
        return 31;
    case 3 : 
    case 5 : 
    case 8 : 
    case 10 : 
        return 30;
    default:
      return 31;
  }
}

function isAValidPartialDate(day_, month_, year_) {
  var fixedMonth = month_ - 1 | 0;
  if (year_ > 0 && month_ > 0 && day_ > 0 && fixedMonth >= 0 && fixedMonth < 12) {
    return day_ <= getDaysInMonth(fixedMonth, year_);
  } else {
    return false;
  }
}

function isValidDate(value) {
  var dateWrapper = new Date(value);
  return isNaN(dateWrapper.valueOf());
}

function getInitialDate(value) {
  if (value !== undefined) {
    var value$1 = value;
    var match = isValidDate(value$1);
    if (match) {
      return Caml_option.some(new Date(value$1));
    } else {
      return Caml_option.some(new Date());
    }
  }
  
}

function parseInputValue(value) {
  var validationRegExp = (/^\d+$/g);
  var passed = validationRegExp.test(value);
  var emptyString = value.length === 0;
  if (passed) {
    if (emptyString) {
      return -1.0;
    } else {
      return Caml_format.caml_float_of_string(value);
    }
  } else {
    return -1.0;
  }
}

function DatePickerComponent(Props) {
  var props = Props.props;
  var dateValue = getInitialDate(props[/* value */0]);
  var match = React.useState((function () {
          if (dateValue !== undefined) {
            return String(Caml_option.valFromOption(dateValue).getDay() | 0);
          } else {
            return "";
          }
        }));
  var setDay = match[1];
  var day = match[0];
  var match$1 = React.useState((function () {
          if (dateValue !== undefined) {
            return String(Caml_option.valFromOption(dateValue).getMonth() + 1.0 | 0);
          } else {
            return "";
          }
        }));
  var setMonth = match$1[1];
  var month = match$1[0];
  var match$2 = React.useState((function () {
          if (dateValue !== undefined) {
            return String(Caml_option.valFromOption(dateValue).getFullYear() | 0);
          } else {
            return "";
          }
        }));
  var setYear = match$2[1];
  var year = match$2[0];
  React.useEffect((function () {
          var floatDay = parseInputValue(day);
          var floatMonth = parseInputValue(month);
          var floatYear = parseInputValue(year);
          var valid = isAValidPartialDate(floatDay | 0, floatMonth | 0, floatYear | 0);
          if (year.length === 4) {
            if (valid) {
              var date = new Date(floatYear, floatMonth, floatDay);
              Curry._1(props[/* onChange */6], Caml_option.some(date));
            } else {
              Curry._1(props[/* onChange */6], undefined);
            }
          }
          return (function (param) {
                    console.log(/* () */0);
                    return /* () */0;
                  });
        }));
  var onInputChange = function ($$event) {
    var target = $$event.target;
    var value = target.value;
    var name = target.name;
    switch (name) {
      case "day-input" : 
          return Curry._1(setDay, (function (param) {
                        return value;
                      }));
      case "month-input" : 
          return Curry._1(setMonth, (function (param) {
                        return value;
                      }));
      case "year-input" : 
          return Curry._1(setYear, (function (param) {
                        return value;
                      }));
      default:
        return /* () */0;
    }
  };
  var match$3 = props[/* hints */1];
  var match$4 = props[/* hints */1];
  var match$5 = props[/* hints */1];
  return React.createElement("span", {
              className: Styles$ReactHooksTemplate.rtdpSpan
            }, React.createElement("span", {
                  className: Styles$ReactHooksTemplate.rtdpSpanInner
                }, React.createElement(TextInput$ReactHooksTemplate.make, {
                      props: /* record */[
                        /* className */"rtdp-day",
                        /* hintText */match$3 ? props[/* dayHint */2] : "",
                        /* value */day,
                        /* maxLength */2,
                        /* name */"day-input",
                        /* onInputChange */onInputChange
                      ]
                    }), React.createElement("span", {
                      className: Styles$ReactHooksTemplate.rtdpSeparator
                    }, "/"), React.createElement(TextInput$ReactHooksTemplate.make, {
                      props: /* record */[
                        /* className */"rtdp-month",
                        /* hintText */match$4 ? props[/* monthHint */3] : "",
                        /* value */month,
                        /* maxLength */2,
                        /* name */"month-input",
                        /* onInputChange */onInputChange
                      ]
                    }), React.createElement("span", {
                      className: Styles$ReactHooksTemplate.rtdpSeparator
                    }, "/"), React.createElement(TextInput$ReactHooksTemplate.make, {
                      props: /* record */[
                        /* className */"rtdp-year",
                        /* hintText */match$5 ? props[/* yearHint */4] : "",
                        /* value */year,
                        /* maxLength */4,
                        /* name */"year-input",
                        /* onInputChange */onInputChange
                      ]
                    })));
}

var make = DatePickerComponent;

exports.getDaysInMonth = getDaysInMonth;
exports.isAValidPartialDate = isAValidPartialDate;
exports.isValidDate = isValidDate;
exports.getInitialDate = getInitialDate;
exports.parseInputValue = parseInputValue;
exports.make = make;
/* react Not a pure module */
