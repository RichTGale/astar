#!/bin/bash

DIRECTORY="./build"

rm -rf ${DIRECTORY}
mkdir ${DIRECTORY}

cmake -H. -B ./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

make --directory=./build
