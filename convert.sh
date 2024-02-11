#!/bin/sh

if [ $# -ne 2 ]; then
    echo >&2 "Use: $0 src dest"
    exit 2
fi

src=$1
dest=$2
name=$(basename $dest | cut -d . -f 1) # file name without path and without extension.

file_data=$(cat $src | xxd -i)
echo "constexpr unsigned char $name[] = {\n$file_data\n};" > $dest
