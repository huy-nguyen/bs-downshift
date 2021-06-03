[@bs.val] external alert: string => unit = "alert";

[@react.component]
let make = () => {
  // open Downshift;

  let render = (stateAndHelpers: Downshift.StateAndHelpers.t) => {
    open Downshift.StateAndHelpers;
    module SharedStyles = Shared.Styles;
    let labelProps = getLabelProps(stateAndHelpers);
    let inputProps = getInputProps(stateAndHelpers, ());
    let toggleProps = getToggleButtonProps(stateAndHelpers, ());
    let menuProps = getMenuProps(stateAndHelpers, ());

    let label =
      spreadDownshiftProps(
        <label className=SharedStyles.label>
          {React.string("Find a Star Wars character")}
        </label>,
        labelProps,
      );
    let isOpen = getIsOpen(stateAndHelpers);
    let inputClassName =
      isOpen ? SharedStyles.openedInput : SharedStyles.baseInput;
    let input =
      spreadDownshiftProps(
        <input placeholder="Enter a name" className=inputClassName />,
        inputProps,
      );
    let toggle =
      switch (getSelectedItem(stateAndHelpers)->Js.Nullable.toOption) {
      | Some(_) =>
        <button
          className=SharedStyles.controllerButton
          onClick={_ => clearSelection(stateAndHelpers)}
          ariaLabel="clear selection">
          <Shared.XIcon />
        </button>
      | None =>
        spreadDownshiftProps(
          <button className=SharedStyles.controllerButton>
            <Shared.ArrowIcon isOpen />
          </button>,
          toggleProps,
        )
      };
    let itemElems =
      switch (getInputValue(stateAndHelpers)->Js.Nullable.toOption) {
      | None => [||]
      | Some(inputValue) =>
        Shared.getItems(inputValue)
        ->Belt.Array.mapWithIndex((index, {name, id} as item) => {
            let itemProps =
              getItemProps(
                stateAndHelpers,
                ~mainParams=itemMainParams(~item, ~index, ()),
              );
            let isActive =
              switch (
                getHighlightedIndex(stateAndHelpers)->Js.Nullable.toOption
              ) {
              | Some(highlightedIndex) => highlightedIndex == index
              | None => false
              };
            let isSelected =
              switch (getSelectedItem(stateAndHelpers)->Js.Nullable.toOption) {
              | Some(selectedItem) => selectedItem == item
              | None => false
              };
            spreadDownshiftProps(
              <li
                key=id
                className={SharedStyles.getItemClassName(
                  ~isActive,
                  ~isSelected,
                )}>
                {React.string(name)}
              </li>,
              itemProps,
            );
          })
      };
    let menuClassName =
      getIsOpen(stateAndHelpers)
        ? SharedStyles.baseMenu : SharedStyles.hiddenMenu;
    let menu =
      spreadDownshiftProps(
        <ul className=menuClassName> {React.array(itemElems)} </ul>,
        menuProps,
      );
    <div style={ReactDOMRe.Style.make(~width="250px", ~margin="auto", ())}>
      label
      <div style={ReactDOMRe.Style.make(~position="relative", ())}>
        input
        toggle
      </div>
      <div style={ReactDOMRe.Style.make(~position="relative", ())}>
        menu
      </div>
    </div>;
  };

  let onChange = (selectedItem: Js.Nullable.t(Shared.item), _) => {
    switch (Js.Nullable.toOption(selectedItem)) {
    | Some({name}) => alert("You selected " ++ name)
    | None => alert("Selection cleared")
    };
  };

  let wrapperStyle =
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexDirection="column",
      ~marginTop="50px",
      (),
    );

  <div style=wrapperStyle>
    <Downshift itemToString=Shared.itemToSring onChange> render </Downshift>
  </div>;
};
