  open Css;

  let rtdpSpan = style([
    display(inlineBlock),
    position(relative),
    padding(px(2)),
    margin(px(1)),
    backgroundColor(hex("ffffff")),
    border(px(1), solid, hex("666")),
    borderRadius(px(3))
  ]);

  let rtdpSpanInner = style([
    border(px(0), none, hex("000")),
    padding(px(1)),
    margin(px(1)),
    whiteSpace(nowrap),
    backgroundColor(hex("ffffff"))
  ]);

  let rtdpInput = style([
    border(px(0), none, hex("000")),
    padding(px(1)),
    margin(px(1)),
    whiteSpace(nowrap),
    backgroundColor(hex("ffffff")),
    width(px(31))
  ]);

 let plusSizeInput = style([width(px(47))]);

 let rtdpYearInput = merge([rtdpInput, plusSizeInput]);

 let rtdpSeparator = style([
   color(hex("999999"))
 ]);
