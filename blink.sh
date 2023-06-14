echo "Compiling..."
if g++ -std=c++17 -Wall -Werror main.cpp -o blink
then
    echo "Running..."
    ./blink > output.bmp
fi
