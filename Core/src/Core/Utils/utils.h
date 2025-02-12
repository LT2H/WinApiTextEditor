#pragma once
#include <windows.h>

namespace Core
{
constexpr UINT WM_CREATE_CONTROLS = WM_APP + 1;

enum class Command
{
    openFile = 1,
    saveFile,
};

} // namespace Core