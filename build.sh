#!/bin/bash

#Clean project
if [ "$1" == "clean" ]; then
    rm -f rtype_client rtype_server
    rm -rf server/build client/build
    echo "Success !"
    exit 0
fi

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
            exit 1
        fi
    else
        echo "CMake is already installed."
    fi
}

check_cmake

#Check if arg is client or server
if [ "$1" == "client" ]; then
    cd client
    mkdir -p build
    cmake -S . -B build
    if ! cmake --build build -j; then
        echo "Failed to build the Client"
        exit 1
    fi
    mv build/rtype_client ..
    cd ..
    exit 0
elif [ "$1" == "server" ]; then
    cd server
    mkdir -p build
    cmake -S . -B build
    if ! cmake --build build -j; then
        echo "Failed to build the Client"
        exit 1
    fi
    mv build/rtype_server ..
    cd ..
    exit 0
else
    echo "Usage: $0 {client|server}"
    exit 1
fi

exit 0
