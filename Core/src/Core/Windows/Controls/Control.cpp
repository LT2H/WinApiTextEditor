#include "Control.h"

#include <windows.h>

#include <string>

namespace Core
{
Control::Control(std::wstring className, std::wstring windowName, DWORD style, int x,
                 int y, int width, int height, HWND hwndParent, int id)
    : m_className{ className }, m_windowName{ windowName }, m_style{ style },
      m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height },
      m_hwndParent{ hwndParent }, m_id{ id }
{
    /*  CreateWindow(className.data(),
                   windowName.data(),
                   style,
                   x,
                   y,
                   width,
                   height,
                   hwndParent,
                   reinterpret_cast<HMENU>(id),
                   nullptr,
                   nullptr);*/
}

} // namespace Core