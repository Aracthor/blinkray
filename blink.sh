echo "Compiling..."
if g++ -std=c++17 -fconstexpr-ops-limit=0x4000000 -Wall -Werror main.cpp -o blink
then
    echo "Running..."
    ./blink > output.bmp
fi
