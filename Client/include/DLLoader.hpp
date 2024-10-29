/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DLLoader
*/

#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

/**
 * @brief A class for dynamically loading and unloading shared libraries.
 *
 * This class provides a platform-independent way to load and unload shared libraries.
 * It uses the appropriate system calls (LoadLibrary on Windows, dlopen on Unix-like systems)
 * to load the library and retrieve function pointers.
 *
 * @tparam T The type of the shared library functions.
 */
template <typename T>
class DLLoader {
public:
    void* handle;

    /**
     * @brief Constructor for the DLLoader class.
     *
     * This constructor loads a shared library at the specified path.
     * It uses platform-specific functions (LoadLibrary on Windows, dlopen on Unix-like systems)
     * to load the library and store the handle for future use.
     *
     * @param libPath The path to the shared library to be loaded.
     *
     * @throws std::runtime_error If the library cannot be loaded.
     */
    DLLoader(const std::string& libPath) {
#ifdef _WIN32
        handle = LoadLibrary(libPath.c_str());
        if (!handle) {
            std::cerr << "Error loading library: " << libPath << " Error: " << GetLastError() << std::endl;
            exit(1);
        }
#else
        handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
        if (!handle) {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
#endif
    }

    /**
     * @brief Destructor for the DLLoader class.
     *
     * This destructor unloads the shared library that was loaded using the constructor.
     * It uses platform-specific functions (FreeLibrary on Windows, dlclose on Unix-like systems)
     * to unload the library and release any associated resources.
     *
     * @note The destructor calls the DLunloader() method internally to perform the unloading.
     */
    ~DLLoader() {
        DLunloader();
    }

    /**
     * @brief Retrieves a function pointer from the loaded shared library.
     *
     * This function retrieves a function pointer of the specified type from the loaded shared library.
     * It uses platform-specific functions (GetProcAddress on Windows, dlsym on Unix-like systems)
     * to retrieve the function pointer based on the given function name.
     *
     * @param funcName The name of the function to retrieve.
     *
     * @return A function pointer of the specified type. If the function is not found, the function
     *         terminates the program with an error message.
     *
     * @note The retrieved function pointer should be cast to the appropriate function pointer type
     *       before use.
     */
    template <typename FuncPtr>
    FuncPtr getFunction(const std::string& funcName) {
        void* sym;
#ifdef _WIN32
        sym = GetProcAddress(static_cast<HMODULE>(handle), funcName.c_str());
#else
        sym = dlsym(handle, funcName.c_str());
#endif

        if (!sym) {
#ifdef _WIN32
            std::cerr << "Error getting symbol: " << funcName << " Error: " << GetLastError() << std::endl;
#else
            std::cerr << dlerror() << std::endl;
#endif
            exit(1);
        }

        return reinterpret_cast<FuncPtr>(sym);
    }

    /**
     * @brief Unloads the shared library that was loaded using the constructor.
     *
     * This function unloads the shared library that was loaded using the constructor.
     * It uses platform-specific functions (FreeLibrary on Windows, dlclose on Unix-like systems)
     * to unload the library and release any associated resources.
     *
     * @note The destructor calls this method internally to perform the unloading.
     *
     * @return void
     */
    void DLunloader() {
#ifdef _WIN32
        if (handle) {
            FreeLibrary(static_cast<HMODULE>(handle));
        }
#else
        if (handle) {
            dlclose(handle);
        }
#endif
    }
};
