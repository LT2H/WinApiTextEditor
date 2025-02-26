#pragma once
#include "utils.h"

#include <windows.h>

namespace Core
{
struct Hotkey
{
    UINT modifiers;
    Command command;
    char key;
};

} // namespace Core