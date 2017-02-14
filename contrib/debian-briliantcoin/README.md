
Debian
====================
This directory contains files used to package briliantcoind/briliantcoin-qt
for Debian-based Linux systems. If you compile briliantcoind/briliantcoin-qt yourself, there are some useful files here.

## briliantcoin: URI support ##


briliantcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Briliantcoin.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your briliantcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

briliantcoin-qt.protocol (KDE)

