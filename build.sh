#!/bin/bash

mkdir build && pushd build
# Edit the command below, as well as '../kobo.cmake' depending on the location of your Qt cross-compilation setup
cmake -DCMAKE_TOOLCHAIN_FILE=../kobo.cmake -DCMAKE_PREFIX_PATH=/home/nicolas/qt-bin/qt-linux-5.15.2-kobo/lib/cmake ..
make -j$(($(nproc)*2))
popd
