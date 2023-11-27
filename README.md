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

In an arch system you can build it by using your preferred aur helper such as yay per example

```sh
yay -S cutefetch
```

**Note**: Aur package is down atm, since the change from `PREFIX` to `DESTDIR` in the `Makefile`.

Or, if you're running gentoo, you could use the Alxhr0's lunatic repository which includes an
ebuild for cutefetch, check it out [here](https://gitlab.com/Alxhr0/lunatic_repository).

Include the repository by following the next commands:

```sh
emerge -av app-eselect/eselect-repository
eselect repository add lunatic_repository git https://gitlab.com/Alxhr0/lunatic_repository.git
emerge --sync lunatic_repository
```

And now you can install it by unmasking it and accepting the license:

```sh
echo 'app-misc/cutefetch **' >> /etc/portage/package.accept_keywords/cutefetch
echo 'app-misc/cutefetch all-rights-reserved' >> /etc/portage/package.license/cutefetch
emerge -av app-misc/cutefetch
```

> Others package managers are WIP atm, if you want, you could contribute by packaging cutefetch to your fav distro

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

## Enjoy

Thanks for reading me! Enjoy with cutefetch, also if you liked this little project
please give me a star on this repo, that will support me and my work at GitHub :)
