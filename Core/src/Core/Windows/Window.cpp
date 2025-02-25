#include "Core/Utils/utils.h"
#include "Core/Windows/Controls/Menu.h"
#include "Window.h"
#include <Core/Windows/Controls/FindDialog.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <span>
#include <commdlg.h>

namespace Core
{
Window* Window::m_instance{ nullptr };
UINT Window::m_findMsg{};
HWND Window::m_hwnd{};
std::unordered_map<std::wstring, Control> Window::m_controls{};
FindDialog* Window::m_findDialog{};
ReplaceDialog* Window::m_replaceDialog{};
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

Window& Window::initialize(HINSTANCE hInst, LPCWSTR cursorId, int color,
                           std::wstring className, std::wstring windowName, int x,
                           int y, int width, int height, HWND hwndParent)
{
    if (!m_instance)
    {
        m_instance = new Window(hInst,
                                cursorId,
                                color,
                                className,
                                windowName,
                                x,
                                y,
                                width,
                                height,
                                hwndParent);
    }
    else
    {
        throw std::runtime_error(
            "Window already created. Call getInstance() instead.");
    }

    return *m_instance;
}

Window& Window::getInstance()
{
    if (!m_instance)
    {
        throw std::runtime_error("WinApp not created yet. Call create() first.");
    }
    return *m_instance;
}

void Window::registerControl(const Control& control)
{
    m_controls[control.getClassName()] = control;
}

void Window::registerFindDialog(FindDialog* dialog) { m_findDialog = dialog; }

void Window::registerReplaceDialog(ReplaceDialog* dialog)
{
    m_replaceDialog = dialog;
}

void Window::addMenu(std::unique_ptr<Menu> mainMenu)
{
    m_menus.push_back(std::move(mainMenu));
}

void Window::registerFunc(Command command, std::function<void()> func)
{
    m_registered_funcs[command] = func;
}

int Window::registerHotkeys(std::span<Hotkey> hotkeys) const
{
    for (auto& hotkey : hotkeys)
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

int Window::promptSaveBeforeClose()
{
    int result{ MessageBox(m_hwnd,
                           L"Do you want to save changes?",
                           L"Save Changes",
                           MB_YESNOCANCEL | MB_ICONWARNING) };

    return result;
}

LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        m_findMsg = RegisterWindowMessage(FINDMSGSTRING); // Register find message
        // m_replaceMsg = RegisterWindowMessage(FINDMSGSTRING); // Register replace
        // message Post a custom message to register controls after WM_CREATE
        // PostMessage(hwnd, WM_CREATE_CONTROLS, 0, 0);
    }
    break;

        // case WM_CREATE_CONTROLS:
        //     break;

    case WM_COMMAND:
    {
        Command command{ LOWORD(wp) };
        auto it{ m_registered_funcs.find(command) };
        if (it != m_registered_funcs.end())
        {
            it->second();
        }

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

    case WM_SIZE:
    {
        RECT rc{};
        GetClientRect(m_hwnd, &rc);
        for (const auto& control : m_controls)
        {
            MoveWindow(control.second.getHwnd(), 0, 0, rc.right, rc.bottom, TRUE);
        }
    }
    break;

    case WM_CLOSE:
    {
        int choice{ promptSaveBeforeClose() };
        switch (choice)
        {
        case IDYES:
        {
            auto it{ m_registered_funcs.find(Core::Command::saveFile) };
            if (it != m_registered_funcs.end())
            {
                it->second();
            }
        }
        break;
        case IDNO:
            break;
        case IDCANCEL:
            return 0;
        default:
            break;
        }
        PostQuitMessage(0);
    }
    break;

    default:
        if (msg == m_findMsg)
        {
            LPFINDREPLACE lpfr{ reinterpret_cast<LPFINDREPLACE>(lp) };
            auto it{ m_controls.find(L"Edit") };
            if (it == m_controls.end())
                return 0;

            BOOL searchDown{ (lpfr->Flags & FR_DOWN) ? TRUE
                                                     : FALSE }; // Search direction
            BOOL matchCase{ (lpfr->Flags & FR_MATCHCASE) ? TRUE
                                                         : FALSE }; // Match case
            BOOL matchWholeWord{ (lpfr->Flags & FR_WHOLEWORD)
                                     ? TRUE
                                     : FALSE };                     // Whole word

            if (lpfr->Flags & FR_FINDNEXT)
            {

                m_findDialog->searchFile(it->second.getHwnd(),
                                         lpfr->lpstrFindWhat,
                                         searchDown,
                                         matchCase,
                                         matchWholeWord);
            }

            if (lpfr->Flags & FR_REPLACE)
            {
                m_replaceDialog->findAndReplaceText(it->second.getHwnd(),
                                                    lpfr->lpstrFindWhat,
                                                    lpfr->lpstrReplaceWith,
                                                    matchCase,
                                                    matchWholeWord);
            }

            if (lpfr->Flags & FR_REPLACEALL)
            {
                m_replaceDialog->findAndReplaceAllText(it->second.getHwnd(),
                                                       lpfr->lpstrFindWhat,
                                                       lpfr->lpstrReplaceWith,
                                                       matchCase,
                                                       matchWholeWord);
            }

            return 0;
        }

        return DefWindowProc(hwnd, msg, wp, lp);
    }
}

} // namespace Core