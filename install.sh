#!/bin/bash

cmake -H. -B./ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

make --directory=./
