#pragma once
#include <Core/Windows/Controls/Control.h>
#include <windows.h>
#include <string>
#include <vector>

namespace Core
{
class Window
{
  public:
    explicit Window(HINSTANCE hInst, LPCWSTR cursorId, int color,
                    std::wstring className, std::wstring windowName, int x, int y,
                    int width, int height, HWND hwndParent);

    HWND getHandle() { return m_hwnd; }

    void addControl(const Control& control);

  private:
    WNDCLASS m_wc{};
    HWND m_hwnd{};
    static std::vector<Control> m_controls;

    static void createControls();

    static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};
} // namespace Core