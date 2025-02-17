#pragma once
#include <windows.h>

namespace Core
{
constexpr UINT WM_CREATE_CONTROLS = WM_APP + 1;

enum class Command
{
    nothing  = 1,
    openFile = 2,
    saveFile = 3,
    help     = 4,
};

void enableDebugConsole();

} // namespace Core