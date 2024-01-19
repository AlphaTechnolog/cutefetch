{
  inputs,
  system,
}: let
  pkgs = inputs.nixpkgs.legacyPackages.${system};
  cutefetch = pkgs.callPackage ./cutefetch.nix {};
in {
  packages.default = cutefetch;
  devShells.default = pkgs.mkShell {
    buildInputs = [cutefetch];
  };
}
