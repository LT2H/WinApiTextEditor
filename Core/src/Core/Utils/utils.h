#pragma once
#include <windows.h>
#include <unordered_map>
#include <string>
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

inline std::unordered_map<Command, std::string> shortcutKeys{
    { Command::nothing, "A" }, { Command::openFile, "N" }, { Command::saveFile, "C" }
};

void enableDebugConsole();

} // namespace Core