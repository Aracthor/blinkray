#!/bin/sh

scene_file=$1
if [ -z $scene_file ]
then
    scene_file="scene_test.ipp"
fi

echo "Compiling..."
if clang++ -std=c++20 -fconstexpr-steps=0x4000000 -Wall -Werror -I srcs/ -DSCENE_FILE=\"../scenes/$scene_file\" srcs/main.cpp -o blink
then
    echo "Running..."
    ./blink > tmp.bmp && mv tmp.bmp output.bmp || rm tmp.bmp
fi
