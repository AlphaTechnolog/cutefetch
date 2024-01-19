{
  stdenv,
  pkgs,
  lib,
  ...
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
    make DESTDIR=$out/bin install
  '';

  meta = with lib; {
    description = "Simple fetch tool written in c";
    homepage = "https://github.com/AlphaTechnolog/cutefetch";
    license = licenses.mit;
  };
}
