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

#Check if arg is client or server
if [ "$1" == "client" ]; then
    mkdir -p client/build
    cmake -DTARGET_TYPE=client -S . -B client/build
    cmake --build client/build
    if [ $? -ne 0 ]; then
        echo "Failed to build the Client"
        exit 1
    fi
    exit 0
elif [ "$1" == "server" ]; then
    mkdir -p server/build
    cmake -DTARGET_TYPE=server -S . -B server/build
    cmake --build server/build
    if [ $? -ne 0 ]; then
        echo "Failed to build the Client"
        exit 1
    fi
    exit 0
elif [ "$1" == "server" ]; then
    rm -f rtype_client rtype_server
    rm -rf server/build client/build
    echo "Successfully cleaned !"
    exit 0
else
    echo "Usage: $0 {client|server}"
    exit 1
fi

exit 0
