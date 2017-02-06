
Debian
====================
This directory contains files used to package libracoind/libracoin-qt
for Debian-based Linux systems. If you compile libracoind/libracoin-qt yourself, there are some useful files here.

## libracoin: URI support ##


libracoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Libracoin.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your libracoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

libracoin-qt.protocol (KDE)

