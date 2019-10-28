[@bs.val] external alert: string => unit = "alert";

type item = {value: string};

let items = [|
  {value: "apple"},
  {value: "pear"},
  {value: "orange"},
  {value: "grape"},
  {value: "banana"},
|];

[@react.component]
let make = () => {
  module StateAndHelpers = Downshift.StateAndHelpers;

  let itemToString = (item: Js.Nullable.t(item)) =>
    switch (Js.Nullable.toOption(item)) {
    | Some({value}) => value
    | None => ""
    };
  let render = (stateAndHelpers: StateAndHelpers.t) => {
    open StateAndHelpers;

    let labelProps = getLabelProps(stateAndHelpers);
    let inputProps = getInputProps(stateAndHelpers, ());
    let label =
      spreadDownshiftProps(
        <label> {React.string("Enter a fruit")} </label>,
        labelProps,
      );

    let input = spreadDownshiftProps(<input />, inputProps);

    let menuProps = getMenuProps(stateAndHelpers, ());
    let menu =
      if (getIsOpen(stateAndHelpers)) {
        let filteredItems =
          switch (getInputValue(stateAndHelpers)->Js.Nullable.toOption) {
          | None
          | Some("") => items
          | Some(inputValue) =>
              items->Belt.Array.keep(item =>
                Js.String.includes(inputValue, item.value)
              )
          };
        let itemElems =
          filteredItems -> Belt.Array.mapWithIndex((index, {value} as item) => {
              let itemProps =
                getItemProps(
                  stateAndHelpers,
                  ~mainParams=
                    itemMainParams(~item, ~key=value, ~index, ()),
                );
              let backgroundColor =
                switch (
                  getHighglightedIndex(stateAndHelpers)->Js.Nullable.toOption
                ) {
                | Some(highlightedIndex) =>
                  highlightedIndex == index ? "lightgray" : ""
                | None => ""
                };
              let fontWeight =
                switch (
                  getSelectedItem(stateAndHelpers)->Js.Nullable.toOption
                ) {
                | Some(selectedItem) =>
                  selectedItem == item ? "bold" : "normal"
                | None => ""
                };
              let style =
                ReactDOMRe.Style.make(~backgroundColor, ~fontWeight, ());
              spreadDownshiftProps(
                <li style> {React.string(item.value)} </li>,
                itemProps,
              );
          });
        spreadDownshiftProps(<ul> {React.array(itemElems)} </ul>, menuProps);
      } else {
        spreadDownshiftProps(
          <ul style={ReactDOMRe.Style.make(~display="none", ())} />,
          menuProps,
        );
      };

    <div> label input menu </div>;
  };

  let onChange = (selectedItem: Js.Nullable.t(item), _) =>
    switch (Js.Nullable.toOption(selectedItem)) {
    | Some({value}) => alert("You selected " ++ value)
    | None => alert("Selection cleared")
    };

  <Downshift onChange itemToString> render </Downshift>;
};
