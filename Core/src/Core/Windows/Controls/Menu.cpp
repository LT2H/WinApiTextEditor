#include "Menu.h"

namespace Core
{
Menu::Menu(HWND hwndParent, UINT flags, Command command, std::wstring windowName)
    : m_hwndMenu{ CreateMenu() }
{
    m_hwndParent = hwndParent;
    m_flags      = flags;
    m_command    = command;
    m_windowName = windowName;
}

Menu::Menu(UINT flags, Command command, std::wstring windowName)
    : m_hwndMenu{ CreateMenu() }
{
    m_flags      = flags;
    m_command    = command;
    m_windowName = windowName;
}

Menu::Menu(UINT flags) : m_hwndMenu{ CreateMenu() } { m_flags = flags; }

Menu::Menu(HWND hwndParent) : m_hwndMenu{ CreateMenu() }
{
    m_hwndParent = hwndParent;
}

void Menu::appendMenu(const Menu& menu)
{
    AppendMenu(m_hwndMenu,
               menu.getFlags(),
               reinterpret_cast<UINT_PTR>(menu.getHwndMenu()),
               menu.getWindowName().c_str());
}

void Menu::appendMenu()
{
    AppendMenu(m_hwndMenu,
               m_flags,
               reinterpret_cast<UINT_PTR>(m_hwndMenu),
               m_windowName.c_str());
}

void Menu::appendMenu(UINT flags) { AppendMenu(m_hwndMenu, flags, 0, nullptr); }

void Menu::appendMenu(UINT flags, Command command, std::wstring windowName)
{
    AppendMenu(
        m_hwndMenu, flags, static_cast<UINT_PTR>(command), windowName.c_str());
}

void Menu::setMenu() { SetMenu(m_hwndParent, m_hwndMenu); }


} // namespace Core