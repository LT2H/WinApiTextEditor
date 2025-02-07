#pragma once
#include <windows.h>

#include <string>
namespace Core
{
class Control
{
  private:
    int m_id{};

  public:
    explicit Control(std::wstring className, std::wstring windowName, DWORD style,
                     int x, int y, int width, int height, HWND hwndParent, int id);
};
} // namespace Core