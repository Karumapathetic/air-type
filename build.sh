#!/bin/bash

# Function to check if cmake is installed
check_cmake() {
    if ! command -v cmake &> /dev/null; then
        echo "CMake is not installed. Installing CMake..."
        if [ -x "$(command -v apt-get)" ]; then
            sudo apt-get update
            sudo apt-get install -y cmake
        elif [ -x "$(command -v dnf)" ]; then
            sudo dnf install -y cmake
        elif [ -x "$(command -v pacman)" ]; then
            sudo pacman -Syu cmake
        else
            echo "Package manager not supported. Please install CMake manually."
        fi
    else
        echo "CMake is already installed."
    fi
}

check_cmake

if [ "$1" == "clean" ]; then
    rm -f r-type_client r-type_server
    rm -rf build build
    echo "Successfully cleaned !"
    exit 0
elif [ "$1" == "help" ]; then
    echo "Usage: $0 [clean]"
    exit 1
elif [ "$1" == "doc" ]; then
    doxygen Doc/Doxyfile
    xdg-open ./Doc/html/index.html
    exit 0
else
    git submodule update --init
    mkdir -p build
    cmake -S . -B build
    cmake --build build
    if [ $? -ne 0 ]; then
        echo "Failed to build the Project"
        exit 1
    fi
    exit 0
fi

exit 0
