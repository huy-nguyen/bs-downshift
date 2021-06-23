[@bs.module "match-sorter"]
external matchSort:
  (~collection: array(string), ~searchPhrase: string) => array(string) =
  "matchSorter";

[@bs.deriving abstract]
type stringKeys = {keys: array(string)};

[@bs.module "match-sorter"]
external matchSortByStringKeys:
  (~collection: array('element), ~searchPhrase: string, ~keys: stringKeys) =>
  array('element) =
  "matchSorter";

[@bs.deriving abstract]
type functionKeys('a) = {keys: array('a => string)};

[@bs.module "match-sorter"]
external matchSortByFunctionKeys:
  (
    ~collection: array('element),
    ~searchPhrase: string,
    ~keys: functionKeys('element)
  ) =>
  array('element) =
  "matchSorter";
