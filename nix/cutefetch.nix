{
  pkgs ? import <nixpkgs> {},
  lib ? pkgs.lib,
  stdenv ? pkgs.stdenv,
}:

stdenv.mkDerivation {
  pname = "cutefetch";
  version = "git";

  src = ../.;

  buildInputs = with pkgs; [
    gnumake
    gcc
  ];

  installPhase = ''
    make PREFIX=/ DESTDIR=$out install
  '';

  meta = with lib; {
    description = "Simple fetch tool written in c";
    homepage = "https://github.com/AlphaTechnolog/cutefetch";
    license = licenses.mit;
  };
}
