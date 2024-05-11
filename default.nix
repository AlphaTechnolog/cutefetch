# WIP: failing
{
  stdenvNoCC,
  version,
  src,
  zig,
  ...
}:
stdenvNoCC.mkDerivation {
  pname = "cutefetch";

  inherit
    version
    src
    ;

  buildInputs = [zig];

  buildPhase = ''
    mkdir $out
    export XDG_CACHE_HOME=$(mktemp -d)
    zig build -Doptimize=ReleaseSafe --prefix $out
    rm -rf $XDG_CACHE_HOME
  '';

  installPhase = ''
    mkdir $out/bin
    install -Dvm755 ./zig-out/bin/cutefetch $out/bin/
  '';
}
