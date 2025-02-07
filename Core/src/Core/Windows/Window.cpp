#include "Window.h"
#include <string>
#include <iostream>
namespace Core
{
Window::Window(HINSTANCE hInst, LPCWSTR cursorId, int color, std::wstring className,
               std::wstring windowName, int x, int y, int width, int height,
               HWND hwndParent)
{
    m_wc.hbrBackground = reinterpret_cast<HBRUSH>(color);
    m_wc.hCursor       = LoadCursor(nullptr, cursorId);
    m_wc.hInstance     = hInst;
    m_wc.lpszClassName = className.data();
    m_wc.lpfnWndProc   = windowProc;

    if (!RegisterClass(&m_wc))
    {
        std::cerr << "Failed to register class\n";
    }

    m_hwnd = CreateWindow(m_wc.lpszClassName,
                          reinterpret_cast<wchar_t*>(windowName.data()),
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          x,
                          y,
                          width,
                          height,
                          hwndParent,
                          nullptr,
                          nullptr,
                          nullptr);
}

LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    {
        switch (msg)
        {
        case WM_CREATE:
            // addControls(hwnd);
            break;

        case WM_COMMAND:
            /*  switch (wp)
              {
              case OPEN_FILE_BUTTON:
              {
                  openFile(hwnd);
                  break;
              }

              case SAVE_FILE_BUTTON:
                  saveFile(hwnd);
                  break;

              default:
                  break;
              }*/

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
    }
}

} // namespace Core