#pragma once
#include <windows.h>
#include <string>

namespace Core
{
class Window
{
  public:
    explicit Window(HINSTANCE hInst, LPCWSTR cursorId, int color,
                    std::wstring className, std::wstring windowName, int x, int y,
                    int width, int height, HWND hwndParent);

    HWND getHandle() { return m_hwnd; }

  private:
    WNDCLASS m_wc{};
    HWND m_hwnd{};

    static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};
} // namespace Core