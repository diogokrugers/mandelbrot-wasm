#!/bin/bash

mkdir -p build
cd build

emcmake cmake ..
emmake make

cd ..

if ls build/*.wasm 1> /dev/null 2>&1; then
    mv build/*.wasm build/*.js web/
    echo "Arquivos mandelbrot.wasm e mandelbrot.js movidos para web/"
else
    echo "Arquivos mandelbrot.wasm e mandelbrot.js não encontrados em build/"
    exit 1
fi
