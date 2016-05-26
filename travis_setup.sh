#!/bin/sh

echo -e "\033[0;46mOpenCV\033[0;39m"
pushd opencv
  mkdir release
  pushd release
    cmake ..
    make -j8
    make install
  popd
popd
echo -e "\033[0;46mgflags\033[0;39m"
pushd gflags
  mkdir release
  pushd release
    cmake ..
    make -j8
    make install
  popd
popd
