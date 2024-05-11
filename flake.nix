{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    zig.url = "github:mitchellh/zig-overlay";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [
          (_: prev: {
            zig = inputs.zig.packages.${system}."0.11.0";
          })
        ];
      };
    in {
      devShells.default = let
        inherit
          (pkgs)
          mkShell
          zig
          ;
      in
        mkShell {
          buildInputs = [zig];
        };
    });
}
