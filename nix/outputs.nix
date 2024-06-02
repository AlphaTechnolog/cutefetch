{
  inputs,
  system,
}: let
  pkgs = inputs.nixpkgs.legacyPackages.${system};
  cutefetch = pkgs.callPackage ./cutefetch.nix {};
in {
  packages.default = cutefetch;
  overlays.default = (_: _: {inherit cutefetch;});

  devShells.default = pkgs.mkShell {
    buildInputs = [cutefetch];
  };
}
