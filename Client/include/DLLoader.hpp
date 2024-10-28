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

template <typename T>
class DLLoader {
public:
    void* handle;

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

    ~DLLoader() {
        DLunloader();
    }

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
