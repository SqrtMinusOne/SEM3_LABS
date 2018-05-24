#!/bin/bash
cd ./build
cmake .. -Dtests=ON -Dmain=ON -Djoker=ON

if [ ! -f "$Makefile" ]; then
    echo "===============CMake OK==============="
    make
fi
if [ ! -f "$lab6test" ]; then
    echo "===============Launching tests==============="
    ./lab6test
fi
