#include "Window.h"
#include "Core/Utils/utils.h"
#include <string>
#include <iostream>
#include <unordered_map>
namespace Core
{
std::unordered_map<Command, Control> Window::m_controls{};
// std::unordered_map<int, HWND> Window::m_control_handles{};

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

void Window::addControl(const Control& control)
{
    m_controls[control.getCommand()] = control;
}

void Window::createControls()
{
    for (auto& control : m_controls)
    {
        control.second.create();
    }
}

LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    {
        switch (msg)
        {
        case WM_CREATE:
            // createControls();
            // Post a custom message to register controls after WM_CREATE
            PostMessage(hwnd, WM_CREATE_CONTROLS, 0, 0);
            break;

        case WM_CREATE_CONTROLS:
            createControls();
            break;

        case WM_COMMAND:
        {
            Command command{ LOWORD(wp) };
            if (m_controls.contains(command))
            {
                m_controls[command].handleCommand(command);
            }
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
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
    }
}

} // namespace Core