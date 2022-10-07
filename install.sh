#!/bin/bash

cmake -H. -B ./debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

make --directory=./
