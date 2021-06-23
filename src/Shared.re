type item = {
  name: string,
  id: string,
};
let allItems =
  StarwarsNames.all->Belt.Array.map(name =>
    {name, id: Js.String.toLowerCase(name)}
  );
let getItems = phrase => {
  switch (phrase) {
  | "" => allItems
  | otherPhrase =>
    MatchSorter.matchSortByFunctionKeys(
      ~collection=allItems,
      ~searchPhrase=otherPhrase,
      ~keys=MatchSorter.functionKeys(~keys=[|item => item.name|]),
    )
  };
};

let itemToSring = (item: Js.Nullable.t(item)) =>
  switch (item->Js.Nullable.toOption) {
  | Some({name}) => name
  | None => ""
  };
module Styles = {
  open Css;

  let label =
    style([
      fontWeight(`bold),
      display(`block),
      marginBottom(`pxFloat(10.)),
    ]);
  let baseInput =
    style([
      width(`percent(100.)),
      fontSize(`rem(1.)),
      wordWrap(`breakWord),
      lineHeight(`rem(1.)),
      outlineWidth(`zero),
      whiteSpace(`normal),
      minHeight(`rem(2.)),
      backgroundColor(`hex("fff")),
      display(`inlineBlock),
      padding4(
        ~top=`rem(1.0),
        ~right=`rem(2.0),
        ~bottom=`rem(1.0),
        ~left=`rem(1.0),
      ),
      color(`rgba((0, 0, 0, `num(0.87)))),
      boxShadow(`none),
      border(`px(1), `solid, `rgba((34, 36, 38, `num(0.15)))),
      borderRadius(`rem(0.30)),
    ]);

  let openedInput =
    merge([
      baseInput,
      style([
        borderBottomLeftRadius(`zero),
        borderBottomRightRadius(`zero),
      ]),
    ]);

  let controllerButton =
    style([
      backgroundColor(`transparent),
      borderWidth(`zero),
      position(`absolute),
      right(`zero),
      top(`zero),
      cursor(`pointer),
      width(`pxFloat(47.)),
      display(`flex),
      flexDirection(`column),
      height(`percent(100.)),
      justifyContent(`center),
      alignItems(`center),
    ]);

  let baseMenu =
    style([
      padding(`zero),
      marginTop(`zero),
      position(`absolute),
      backgroundColor(white),
      width(`percent(100.)),
      maxHeight(`rem(20.)),
      overflowY(`auto),
      overflowX(`hidden),
      outlineWidth(`zero),
      borderColor(`hex("96c8da")),
      borderTopWidth(`zero),
      borderRightWidth(`px(1)),
      borderBottomWidth(`px(1)),
      borderLeftWidth(`px(1)),
      borderStyle(`solid),
    ]);
  let hiddenMenu = merge([baseMenu, style([display(`none)])]);
  let itemBase =
    style([
      position(`relative),
      cursor(`pointer),
      display(`block),
      borderWidth(`zero),
      height(`auto),
      textAlign(`left),
      borderTopWidth(`zero),
      lineHeight(`rem(1.)),
      color(`rgba((0, 0, 0, `num(0.87)))),
      fontSize(`rem(1.)),
      textTransform(`none),
      fontWeight(`normal),
      boxShadow(`none),
      padding2(~v=`rem(0.8), ~h=`rem(1.1)),
      whiteSpace(`normal),
      wordWrap(`normal),
    ]);

  let getItemClassName = (~isActive, ~isSelected) => {
    let activeStyle =
      isActive
        ? style([
            color(`rgba((0, 0, 0, `num(0.95)))),
            background(`rgba((0, 0, 0, `num(0.03)))),
          ])
        : style([]);
    let selectedStyle =
      isSelected ? style([color(`rgba((0, 0, 0, `num(0.95))))]) : style([]);
    merge([itemBase, activeStyle, selectedStyle]);
  };
};

module ArrowIcon = {
  [@react.component]
  let make = (~isOpen) =>
    <svg
      viewBox="0 0 20 20"
      preserveAspectRatio="none"
      width="16"
      fill="transparent"
      stroke="#979797"
      strokeWidth="1.1px"
      transform={isOpen ? "rotate(180)" : ""}>
      <path d="M1,6 L10,15 L19,6" />
    </svg>;
};

module XIcon = {
  [@react.component]
  let make = () =>
    <svg
      viewBox="0 0 20 20"
      preserveAspectRatio="none"
      width="12"
      fill="transparent"
      stroke="#979797"
      strokeWidth="1.1px">
      <path d="M1,1 L19,19" />
      <path d="M19,1 L1,19" />
    </svg>;
};
