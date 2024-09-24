# Function to check if CMake is installed
function Check-CMake {
    $cmake = Get-Command cmake -ErrorAction SilentlyContinue
    if (-not $cmake) {
        Write-Host "CMake is not installed. Installing CMake..."
        
        if (Get-Command "choco" -ErrorAction SilentlyContinue) {
            choco install cmake -y
        } elseif (Get-Command "winget" -ErrorAction SilentlyContinue) {
            winget install Kitware.CMake
        } else {
            Write-Host "Package manager not supported. Please install CMake manually."
            exit 1
        }
    } else {
        Write-Host "CMake is already installed."
    }
}

# Check if CMake is installed
Check-CMake

# Check if argument is client or server
if ($args[0] -eq "client") {
    New-Item -ItemType Directory -Force -Path "client/build" | Out-Null
    cmake -DTARGET_TYPE=client -S . -B client/build
    cmake --build client/build
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to build the Client"
        exit 1
    }
    Move-Item -Path .\Debug\rtype_client.exe -Destination ./
    exit 0
} elseif ($args[0] -eq "server") {
    New-Item -ItemType Directory -Force -Path "server/build" | Out-Null
    cmake -DTARGET_TYPE=server -S . -B server/build
    cmake --build server/build
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to build the Server"
        exit 1
    }
    Move-Item -Path .\Debug\rtype_server.exe -Destination ./
    exit 0
} elseif ($args[0] -eq "clean") {
    Remove-Item -Force -Recurse rtype_client.exe, rtype_server.exe, server/build, client/build, Debug -ErrorAction SilentlyContinue
    Write-Host "Successfully cleaned!"
    exit 0
} else {
    Write-Host "Usage: $($MyInvocation.MyCommand.Name) {client|server|clean}"
    exit 1
}

exit 0
