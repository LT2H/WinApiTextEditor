#include "utils.h"
#include <cstdio>
#include <iostream>

void Core::enableDebugConsole()
{
    FILE* fp{};

    if (AllocConsole())
    {
        freopen_s(&fp, "CONIN$", "r", stdin);
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);

        // Optional debug message
        std::cout << "Debug console enabled\n";
    }
    else
    {
        std::cerr << "Failed to allocate console\n";
    }
}