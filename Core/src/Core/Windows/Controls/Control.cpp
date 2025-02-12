#include "Control.h"

#include <windows.h>

#include <string>

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

//void Control::create()
//{
//    m_hwnd = CreateWindow(m_className.data(),
//                          m_windowName.data(),
//                          m_style,
//                          m_x,
//                          m_y,
//                          m_width,
//                          m_height,
//                          m_hwndParent,
//                          reinterpret_cast<HMENU>(m_command),
//                          nullptr,
//                          nullptr);
//}

} // namespace Core