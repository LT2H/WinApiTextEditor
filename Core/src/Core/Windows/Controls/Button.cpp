#include "Button.h"

#include <windows.h>

#include <string>

namespace Core
{
Button::Button(std::wstring className, std::wstring windowName, DWORD style, int x,
               int y, int width, int height, HWND hwndParent, int id)
{
    CreateWindow(className.data(),
                 windowName.data(),
                 style,
                 x,
                 y,
                 width,
                 height,
                 hwndParent,
                 reinterpret_cast<HMENU>(id),
                 nullptr,
                 nullptr);
}

} // namespace Core