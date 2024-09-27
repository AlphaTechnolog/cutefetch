{
  description = "Little fetch utility completely made in the C programming language";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = inputs:
    inputs.flake-utils.lib.eachDefaultSystem (system: let
      getOutputs = import ./nix/outputs.nix;
    in (
        getOutputs {
          inherit inputs system;
        }
      )
    );
}
