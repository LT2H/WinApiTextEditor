#include "Window.h"
#include "Core/Utils/utils.h"
#include "Core/Windows/Controls/Menu.h"
#include <string>
#include <iostream>
#include <unordered_map>
namespace Core
{
std::unordered_map<Command, Control> Window::m_controls{};
std::vector<std::unique_ptr<Menu>> Window::m_menus{};
std::unordered_map<Command, std::function<void()>> Window::m_registered_funcs{};

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

void Window::addMenu(std::unique_ptr<Menu> mainMenu)
{
    m_menus.push_back(std::move(mainMenu));
}

void Window::createControls()
{
    /*  for (auto& control : m_controls)
      {
          control.second.create();
      }*/
}

void Window::registerFunc(Command command, std::function<void()> func)
{
    m_registered_funcs[command] = func;
}

int Window::registerHotkeys()
{ // inline std::unordered_map<Command, std::string> shortcutKeys{
    //     { Command::nothing, "A" },
    //     { Command::openFile, "O" },
    //     { Command::saveFileAs, "S" }
    // };

    m_hotkeys = { { MOD_CONTROL, Command::openFile, 'O' },
                  { MOD_CONTROL | MOD_SHIFT, Command::saveFileAs, 'S' },
                  { MOD_CONTROL, Command::help, 'H' } };

    for (auto& hotkey : m_hotkeys)
    {
        int vkScanResult{ VkKeyScan(hotkey.key) };
        if (vkScanResult == -1)
        {
            std::cerr << "Invalid key: " << hotkey.key << '\n';
            continue; // Skip invalid hotkeys
        }

        UINT vkCode{ static_cast<UINT>(vkScanResult & 0xFF) }; // Extract key code
        if (!RegisterHotKey(
                m_hwnd, static_cast<int>(hotkey.command), hotkey.modifiers, vkCode))
        {
            std::cerr << "Failed to register hotkey\n";
            return 1;
        }
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
            // createControls();
            break;

        case WM_COMMAND:
        {
            Command command{ LOWORD(wp) };
            auto it{ m_registered_funcs.find(command) };
            if (it != m_registered_funcs.end())
            {
                it->second();
            }

            if (command == Command::exit)
            {
                PostQuitMessage(0);
            }

            // switch (command)
            //{
            // case Command::openFile:
            //{
            //     // openFile(hwnd);
            //     std::cout << "Opening...\n";
            //     break;
            // }

            // case Command::saveFile:
            //     // saveFile(hwnd);
            //     break;

            // default:
            //     break;
            // }

            break;
        }

        case WM_HOTKEY:
        {
            Command hotkey{ LOWORD(wp) };
            auto it{ m_registered_funcs.find(hotkey) };
            if (it != m_registered_funcs.end())
            {
                it->second();
            }

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