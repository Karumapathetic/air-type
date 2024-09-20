#!/bin/bash

#Clean project
if [ "$1" == "clean" ]; then
    rm -f rtype_client rtype_server
    rm -rf server/build client/build
    echo "Successfully cleaned !"
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
        fi
    else
        echo "CMake is already installed."
    fi
}

check_cmake

#Check if arg is client or server
if [ "$1" == "client" ]; then
    mkdir -p build
    cmake -DTARGET_TYPE=client -S . -B build
    cmake --build build
    if [ $? -ne 0 ]; then
        echo "Failed to build the Client"
        exit 1
    fi
    mv build/client/rtype_client .
    exit 0
elif [ "$1" == "server" ]; then
    mkdir -p build
    cmake -DTARGET_TYPE=server -S . -B build
    cmake --build build
    if [ $? -ne 0 ]; then
        echo "Failed to build the Client"
        exit 1
    fi
    mv build/server/rtype_server .
    exit 0
else
    echo "Usage: $0 {client|server}"
    exit 1
fi

exit 0
