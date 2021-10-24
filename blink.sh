SRCS=(
    main.cpp
)

echo "Compiling..."
if g++ -std=c++17 -Wall -Werror "${SRCS[@]}" -o blink
then
    echo "Running..."
    ./blink
fi
