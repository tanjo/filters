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

## Run

```
./filters --type blue --file /Users/hoge/img.jpg
```

## Result

```

```

# おまけ

```bash
cmake -GXcode .
```

で Xcode のプロジェクトが作成されて便利

# Result

## Original

<img src="result/798808978.jpg" width="240px">

## grayscale, blue, green, red

<img src="result/798808978.jpg-grayscale.png" width="240px"><img src="result/798808978.jpg-blue.png" width="240px"><img src="result/798808978.jpg-green.png" width="240px"><img src="result/798808978.jpg-red.png" width="240px">

## meanshift

<img src="result/798808978.jpg-meanshift.png" width="240px">

## dot, simple

<img src="result/798808978.jpg-dot.png" width="240px"><img src="result/798808978.jpg-simple.png" width="240px">

## emboss, gaussianblur, sharp

<img src="result/798808978.jpg-emboss.png" width="240px"><img src="result/798808978.jpg-gaussianblur.png" width="240px"><img src="result/798808978.jpg-sharp.png" width="240px">

## negative

<img src="result/798808978.jpg-negative.png" width="240px">
