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
if ($args[0] -eq "--help") {
    Write-Host "Usage: $($MyInvocation.MyCommand.Name) [clean]"
    exit 1
} elseif ($args[0] -eq "clean") {
    Remove-Item -Force -Recurse r-type_client.exe, r-type_server.exe, build, Debug -ErrorAction SilentlyContinue
    Write-Host "Successfully cleaned!"
    exit 0
} else {
    git submodule update --init
    New-Item -ItemType Directory -Force -Path "build" | Out-Null
    cmake -S . -B build
    cmake --build build
    Move-Item -Path "Debug\r-type_client.exe" -Destination "./"
    Move-Item -Path "Debug/r-type_server.exe" -Destination "./"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to build the Project"
        exit 1
    }
    exit 0
}

exit 0
