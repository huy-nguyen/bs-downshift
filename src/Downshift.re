module StateAndHelpers = {
  type t;

  type propGetterOutput;

  /* input params to `StateAndHelpers`'s prop getters */
  [@bs.deriving abstract]
  type rootMainParams = {
    [@bs.optional]
    refKey: string,
  };
  [@bs.deriving abstract]
  type errorBehavior = {supressRefError: bool};

  [@bs.deriving abstract]
  type inputMainParams = {
    [@bs.optional]
    disabled: bool,
  };
  [@bs.deriving abstract]
  type menuMainParams = {
    [@bs.optional]
    refKey: string,
    [@bs.optional] [@bs.as "aria-label"]
    ariaLabel: string,
  };
  [@bs.deriving abstract]
  type itemMainParams('a) = {
    item: 'a,
    [@bs.optional]
    index: int,
    [@bs.optional]
    disabed: bool,
    /* TODO: find a way to avoid specifying React's built-in props explicitly*/
    [@bs.optional]
    key: string,
  };
  [@bs.deriving abstract]
  type toggleButtonMainParams = {
    [@bs.optional]
    disabed: bool,
    [@bs.optional] [@bs.as "aria-label"]
    ariaLabel: string,
  };

  /* prop getters */
  [@bs.send]
  external getRootProps:
    (
      t,
      ~mainParams: rootMainParams=?,
      ~errorBehavior: errorBehavior=?,
      unit
    ) =>
    propGetterOutput =
    "getRootProps";

  [@bs.send]
  external getInputProps:
    (t, ~mainParams: inputMainParams=?, unit) => propGetterOutput =
    "getInputProps";

  [@bs.send] external getLabelProps: t => propGetterOutput = "getLabelProps";

  [@bs.send]
  external getMenuProps:
    (
      t,
      ~mainParams: menuMainParams=?,
      ~errorBehavior: errorBehavior=?,
      unit
    ) =>
    propGetterOutput =
    "getMenuProps";

  [@bs.send]
  external getItemProps:
    (t, ~mainParams: itemMainParams('item)) => propGetterOutput =
    "getItemProps";

  [@bs.send]
  external getToggleButtonProps:
    (t, ~mainParams: toggleButtonMainParams=?, unit) => propGetterOutput =
    "getToggleButtonProps";

  /* state */
  [@bs.get]
  external getHighlightedIndex: t => Js.Nullable.t('item) =
    "highlightedIndex";
  [@bs.get] external getInputValue: t => Js.Nullable.t(string) = "inputValue";
  [@bs.get] external getIsOpen: t => bool = "isOpen";
  [@bs.get]
  external getSelectedItem: t => Js.Nullable.t('item) = "selectedItem";

  /* actions */
  [@bs.send] external clearSelection: t => unit = "clearSelection";
  [@bs.send] external clearItems: t => unit = "clearItems";
  [@bs.send] external closeMenu: t => unit = "closeMenu";

  /* Not part of the JS API. Provided as helper because JSX in Reason doesn't support prop spreading */
  let spreadDownshiftProps = (element: React.element, props: propGetterOutput) =>
    ReasonReact.cloneElement(element, ~props=Obj.magic(props), [||]);
};

type renderer('item) = StateAndHelpers.t => React.element;

type changeHandler('item) =
  (Js.Nullable.t('item), StateAndHelpers.t) => unit;

[@bs.module "downshift"] [@react.component]
external make:
  /* Basic props: */
  (
    ~children: renderer('item),
    ~itemToString: Js.Nullable.t('item) => string=?,
    ~onChange: changeHandler('item)=?,
    /* Control props */
    ~isOpen: bool=?,
    /* Advanced props: */
    ~initialSelectedItem: Js.Nullable.t('item)=?
  ) =>
  React.element =
  "default";
