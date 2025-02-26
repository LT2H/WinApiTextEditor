#pragma once
#include <windows.h>

#include <unordered_map>
#include <string>
namespace Core
{
constexpr UINT WM_CREATE_CONTROLS = WM_APP + 1;

enum class Command : int32_t
{
    nothing = 1,
    openFile,
    saveFile,
    saveFileAs,
    help,
    exit,
    newWindow,
    undo,
    redo,
    selectAll,
    showFindDialog,
    showReplaceDialog,
};

void enableDebugConsole();

} // namespace Core