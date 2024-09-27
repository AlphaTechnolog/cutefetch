{
  inputs,
  system,
}:

let
  pkgs = inputs.nixpkgs.legacyPackages.${system};
  cutefetch = pkgs.callPackage ./cutefetch.nix {};
in {
  packages.default = cutefetch;
  overlays.default = (_: final: final.callPackage ./cutefetch.nix {});

  devShells.default = pkgs.mkShell {
    buildInputs = [cutefetch];
    shellHook = ''
      echo 'Cutefetch should be available to use by typing: `cutefetch`'
    '';
  };
}
