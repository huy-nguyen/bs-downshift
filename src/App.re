[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  switch (url.path) {
  | ["basic-autocomplete"] => <BasicAutocomplete />
  | ["complete-autocomplete"] => <CompleteAutocomplete />
  | _ => <CompleteAutocomplete />
  };
};
