#pragma once
#include <windows.h>

#include <string>
namespace Core
{
class Button
{
  public:
    explicit Button(std::wstring className, std::wstring windowName, DWORD style,
                    int x, int y, int width, int height, HWND hwndParent, int id);
};
} // namespace Core