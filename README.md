# Cutefetch

Cutefetch is a little fetch utility completely made in the C programming language
which aims to be simple and to show a little cute bunny in your terminal as well as
relevant information about your current running system.

![banner](./assets/banner.png)

## Features

- Header
- Bunny banner
- Os name
- Kernel version
- Current used ram
- Hostname
- Disk: Used disk space / Total disk space (Shows mountpoints)
- Color palette

## Requirements

- gcc / clang
- gnumake
- git
- sudo
- uname (you should have it already installed)
- your hostname at /etc/hostname (you may already have that file there)
- A nerd font (to correctly render the glyphs at the color palette)

## Installation

### For arch-based systems

In an arch system you can build it by using your preferred aur helper such as yay per example

```sh
yay -S cutefetch
```

### Gentoo systems

When running gentoo, you could use the [Alxhr0's](https://github.com/Alxhr0) lunatic repository which includes an
ebuild for cutefetch, check it out [here](https://gitlab.com/Alxhr0/andromeda).

Include the repository by following the next commands:

```sh
emerge -av app-eselect/eselect-repository
eselect repository add andromeda git https://gitlab.com/Alxhr0/andromeda.git
emerge --sync andromeda
```

And now you can install it by unmasking it and accepting the license:

```sh
echo 'app-misc/cutefetch **' >> /etc/portage/package.accept_keywords/cutefetch
echo 'app-misc/cutefetch all-rights-reserved' >> /etc/portage/package.license/cutefetch
emerge -av app-misc/cutefetch
```

### Others package managers

We're searching for contributors for packaging cutefetch on others distros, if you like cutefetch
but it's not available in your distro, you could try packaging it for it, or adding a suggestion in the issues tab ;)

Else, you can try manually building it, it's easy :)

## Manual building

Run a little list of shell script commands.

```sh
mkdir -pv ~/repo && cd ~/repo
git clone https://github.com/AlphaTechnolog/cutefetch.git && cd cutefetch
sudo make install
```

Then just run in your terminal `cutefetch`, and you'll see the cute bunny appearing
in your terminal screen :)

## Compilation tricks

You may want to build it using clang, you can do it by overriding the
`CC` variable:

```sh
sudo make CC=clang DESTDIR=/usr/bin all install
```

You can also set a destdir on where you wanna install cutefetch.

```sh
sudo make DESTDIR=/usr/bin install
sudo make DESTDIR=/usr/local/bin install
sudo make DESTIDR=/usr/local/bin uninstall
# ...
```

## Dev notes

- Cleaning the file tree

```sh
make clean
```

> if you already have ran `sudo make install` without having the program compiled you may have to run

```sh
sudo make clean
```

- Fresh compilation

```sh
make clean all
```

## Thanks to

- [Alxhr0](https://github.com/Alxhr0): Who've built & tested cutefetch on others distros and packaged it for gentoo.

## Enjoy

Thanks for reading me! Enjoy with cutefetch, also if you liked this little project
please give me a star on this repo, that will support me and my work at GitHub :)
