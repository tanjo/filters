# filters

# はじめに

```bash
git submodule update --init --recursive
pushd opencv
  mkdir release
  pushd release
    cmake ..
    make -j8
    make install
  popd
popd
pushd glfags
  mkdir release
  pushd release
    cmake ..
    make -j8
    make install
  popd
popd
cmake ..
make
./filters
```

# おまけ

```bash
cmake -GXcode .
```

で Xcode のプロジェクトが作成されて便利
