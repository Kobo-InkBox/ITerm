#!/bin/sh

if [ "${1}" != "install" ]; then
	make
	printf "==== NOTICE: You can safely ignore the above error, it will be fixed shortly ====\n"
	# You are not making my life easy, dear libtool...
	arm-kobo-linux-gnueabihf-gcc -shared  -fPIC -DPIC  src/.libs/encoding.o src/.libs/keyboard.o src/.libs/mouse.o src/.libs/parser.o src/.libs/pen.o src/.libs/screen.o src/.libs/state.o src/.libs/unicode.o src/.libs/vterm.o      -Wl,-soname -Wl,libvterm.so.0 -o .libs/libvterm.so.0.0.3
else
	pushd .libs/
	ln -sf libvterm.so.0.0.3 libvterm.so
	popd
	mkdir -p ../../build/root/lib
	cp .libs/* ../../build/root/lib
fi
