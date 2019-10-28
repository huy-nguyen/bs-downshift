
[@bs.module "starwars-names"] external all: array(string) = "all";
[@bs.module "starwars-names"] external random1: unit => string = "random";
[@bs.module "starwars-names"] external randomN: int => array(string) = "random";
