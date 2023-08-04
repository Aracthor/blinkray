echo "Compiling..."
if clang++ -std=c++20 -fconstexpr-steps=0x4000000 -Wall -Werror -I . main.cpp -o blink
then
    echo "Running..."
    ./blink > output.bmp
fi
