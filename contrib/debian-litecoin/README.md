
Debian
====================
This directory contains files used to package lamacoind/lamacoin-qt
for Debian-based Linux systems. If you compile lamacoind/lamacoin-qt yourself, there are some useful files here.

## lamacoin: URI support ##


lamacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lamacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lamacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

lamacoin-qt.protocol (KDE)

