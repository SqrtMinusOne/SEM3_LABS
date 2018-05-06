#!/bin/bash
cd ./build
cmake .. -Dtests=ON -Dmain=ON -Dshift=ON

if [ ! -f "$Makefile" ]; then
    echo "===============CMake OK==============="
    make
fi
if [ ! -f "$lab5test" ]; then
    echo "===============Launching tests==============="
    ./lab5test
fi