
Debian
====================
This directory contains files used to package lavrovcoind/lavrovcoin-qt
for Debian-based Linux systems. If you compile lavrovcoind/lavrovcoin-qt yourself, there are some useful files here.

## lavrovcoin: URI support ##


lavrovcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Lavrovcoin.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lavrovcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

lavrovcoin-qt.protocol (KDE)

