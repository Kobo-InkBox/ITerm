#!/bin/bash

if ! arm-kobo-linux-gnueabihf-gcc --version &>/dev/null; then
	echo "Found no working 'arm-kobo-linux-gnueabihf-gcc' binary. Maybe you forgot to set up the environment?"
	exit 1
fi

mkdir build && pushd build
# Edit the command below, as well as '../kobo.cmake' depending on the location of your Qt cross-compilation setup
cmake -DCMAKE_TOOLCHAIN_FILE=../kobo.cmake -DCMAKE_PREFIX_PATH=/home/nicolas/qt-bin/qt-linux-5.15.2-kobo/lib/cmake ..
make -j$(($(nproc)*2))
popd
