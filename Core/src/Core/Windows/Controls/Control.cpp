#include "Control.h"

#include <windows.h>
#include <richedit.h>

#include <string>
#include <tchar.h>

namespace Core
{
Control::Control(std::wstring className, std::wstring windowName, DWORD style, int x,
                 int y, int width, int height, HWND hwndParent, Command command)
    : m_className{ className }, m_windowName{ windowName }, m_style{ style },
      m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height },
      m_hwndParent{ hwndParent }, m_command{ command }
{
    m_hwnd = CreateWindow(className.data(),
                          windowName.data(),
                          style,
                          x,
                          y,
                          width,
                          height,
                          hwndParent,
                          reinterpret_cast<HMENU>(command),
                          nullptr,
                          nullptr);
}

Control::Control(std::wstring className, std::wstring windowName, DWORD style, int x,
                 int y, int width, int height, HWND hwndParent)
    : m_className{ className }, m_windowName{ windowName }, m_style{ style },
      m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height },
      m_hwndParent{ hwndParent }
{
    m_hwnd = CreateWindow(className.data(),
                          windowName.data(),
                          style,
                          x,
                          y,
                          width,
                          height,
                          hwndParent,
                          0,
                          nullptr,
                          nullptr);
}

Control::Control(std::wstring className, int x, int y, int width, int height,
                 HWND hwndParent)
    : m_className{ className }, m_x{ x }, m_y{ y }, m_width{ width },
      m_height{ height }, m_hwndParent{ hwndParent }
{
    LoadLibrary(_T("Msftedit.dll")); // Load Rich Edit Library
    m_hwnd = CreateWindowEx(0,
                            MSFTEDIT_CLASS,
                            _T(""),
                            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
                                ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            m_x,
                            m_y,
                            m_width,
                            m_height,
                            m_hwndParent,
                            reinterpret_cast<HMENU>(1),
                            nullptr,
                            nullptr);
}

} // namespace Core