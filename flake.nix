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
      zig-0_11_0 = inputs.zig.packages.${system}."0.11.0";

      pkgs = import nixpkgs {
        inherit system;
        overlays = [
          (_: prev: {
            zig = zig-0_11_0;
          })
        ];
      };
    in {
      # packages.default = pkgs.callPackage ./default.nix {
      #   src = ./.;
      #   version = "git";
      #   zig = zig-0_11_0;
      # };

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
