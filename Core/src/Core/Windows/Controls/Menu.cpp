#include "Menu.h"
#include "Core/Windows/Window.h"

namespace Core
{
Menu::Menu(HWND hwndParent, UINT flags, Command command,
           std::wstring_view windowName)
    : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }, m_flags{ flags },
      m_command{ command }, m_windowName{ windowName }
{
}

Menu::Menu(UINT flags, Command command, std::wstring_view windowName)
    : m_flags{ flags }, m_command{ command }, m_windowName{ windowName }
{
}

Menu::Menu(UINT flags, Menu menu, std::wstring_view windowName)
    : m_hwndMenu{ CreateMenu() }, m_flags{ flags }, m_windowName{ windowName }
{
}

Menu::Menu(HWND hwndParent, Command command)
    : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }, m_flags{ 0 },
      m_command{ command }
{
}

Menu::Menu(HWND hwndParent) : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }
{
}

Menu::Menu() : m_hwndMenu{ CreateMenu() } {}

void Menu::appendMenu(UINT flags, Command command, std::wstring_view windowName)
{
    m_flags      = flags;
    m_command    = command;
    m_windowName = windowName;

    AppendMenu(m_hwndMenu,
               m_flags,
               // reinterpret_cast<UINT_PTR>(menu->getHwndMenu()),
               static_cast<int>(m_command),
               m_windowName.data());
}

void Menu::appendMenu(UINT flags, Command command, std::wstring_view windowName,
                      std::function<void()> handler)
{
    m_flags      = flags;
    m_command    = command;
    m_windowName = windowName;

    AppendMenu(m_hwndMenu,
               m_flags,
               // reinterpret_cast<UINT_PTR>(menu->getHwndMenu()),
               static_cast<int>(m_command),
               m_windowName.data());

    Window::getInstance().registerFunc(m_command, handler);
}

void Menu::appendMenu(UINT flags) const
{
    AppendMenu(m_hwndMenu, flags, 0, nullptr);
}


void Menu::appendMenu(UINT flags, HMENU hMenu, std::wstring_view windowName) const
{
    AppendMenu(m_hwndMenu,
               flags,
               reinterpret_cast<UINT_PTR>(hMenu),
               // static_cast<int>(menu->getCommand()),
               windowName.data());
}

void Menu::setMenu() { SetMenu(m_hwndParent, m_hwndMenu); }

} // namespace Core