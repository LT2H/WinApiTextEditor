#pragma once
#include <windows.h>
#include "utils.h"

namespace Core
{
struct Hotkey
{
    UINT modifiers;
    Command command;
    char key;
};

} // namespace Core