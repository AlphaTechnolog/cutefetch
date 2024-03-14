# cutefetch

cutefetch is adopting zig now!!

![banner](./assets/banner.png)

> This branch is the WIP implementation, you can try it out if you want :)

## Installation

```sh
git clone https://github.com/alphatechnolog/cutefetch -b zig --depth=1
cd cutefetch
zig build -Doptimize=ReleaseSafe
```

then use the binary at `zig-out/bin/zig`

```sh
install -Dvm755 zig-out/bin/* /usr/bin/
```

so now you can call the command `cutefetch` from your shell.