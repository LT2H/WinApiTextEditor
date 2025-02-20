#include "Menu.h"

namespace Core
{
Menu::Menu(HWND hwndParent, UINT flags, Command command, std::wstring windowName)
    : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }, m_flags{ flags },
      m_command{ command }, m_windowName{ windowName }
{
}

Menu::Menu(UINT flags, Command command, std::wstring windowName)
    : m_flags{ flags }, m_command{ command }, m_windowName{ windowName }
{
}

Menu::Menu(UINT flags, Menu menu, std::wstring windowName)
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

// Menu::Menu(UINT flags) : m_hwndMenu{ CreateMenu() } { m_flags = flags; }

// Menu::Menu(const Menu& that)
//     : m_hwndMenu{ that.m_hwndMenu }, m_hwndParent{ that.m_hwndParent },
//       m_flags{ that.m_flags }, m_command{ that.m_command },
//       m_windowName{ that.m_windowName }, m_menus{ that.m_menus },
//       m_commandHandlers{ that.m_commandHandlers }
//{
// }
//
// Menu& Menu::operator=(const Menu& that)
//{
//     m_hwndMenu        = that.m_hwndMenu;
//     m_hwndParent      = that.m_hwndParent;
//     m_flags           = that.m_flags;
//     m_command         = that.m_command;
//     m_windowName      = that.m_windowName;
//     m_menus           = that.m_menus;
//     m_commandHandlers = that.m_commandHandlers;
//
//     return *this;
// }

Menu::Menu(Menu&& that) noexcept
    : m_hwndMenu{ that.m_hwndMenu },
      m_hwndParent{ that.m_hwndParent },            // No need for std::move
      m_flags{ that.m_flags },                      // No need for std::move
      m_command{ that.m_command },
      m_windowName{ std::move(that.m_windowName) }, // Strings should still be moved
      m_children{ std::move(that.m_children) },
      m_commandHandlers{ std::move(that.m_commandHandlers) }
{
    that.m_hwndMenu   = nullptr; // Avoid double deletion in destructor
    that.m_hwndParent = nullptr;
}

Menu& Menu::operator=(Menu&& that) noexcept
{
    m_hwndMenu        = std::move(that.m_hwndMenu);
    m_hwndParent      = std::move(that.m_hwndParent);
    m_flags           = std::move(that.m_flags);
    m_command         = std::move(that.m_command);
    m_windowName      = std::move(that.m_windowName);
    m_children        = std::move(that.m_children);
    m_commandHandlers = std::move(that.m_commandHandlers);

    return *this;
}

void Menu::appendSelf()
{
    AppendMenu(m_hwndMenu,
               m_flags,
               // reinterpret_cast<UINT_PTR>(menu->getHwndMenu()),
               static_cast<int>(m_command),
               m_windowName.c_str());
}

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

void Menu::appendMenu(UINT flags) { AppendMenu(m_hwndMenu, flags, 0, nullptr); }


void Menu::appendMenu(UINT flags, HMENU hMenu, std::wstring_view windowName)
{
    AppendMenu(m_hwndMenu,
               flags,
               reinterpret_cast<UINT_PTR>(hMenu),
               // static_cast<int>(menu->getCommand()),
               windowName.data());
}

void Menu::appendMenu(std::unique_ptr<Menu> menu)
{
    AppendMenu(m_hwndMenu,
               menu->getFlags(),
               reinterpret_cast<UINT_PTR>(menu->getHwndMenu()),
               // static_cast<int>(menu->getCommand()),
               menu->getWindowName().c_str());

    addChild(std::move(menu));
}

void Menu::addChild(std::unique_ptr<Menu> menu)
{
    // Make sure you use the correct command here and it’s not zero
    if (menu->getCommand() != Command::nothing)
    {
        std::cout << "Command passed to addChild is good!" << std::endl;
        m_children[menu->getCommand()] = std::move(menu);
    }
    else
    {
        std::cout << "Command passed to addChild is 1!" << std::endl;
    }
}

void Menu::setMenu() { SetMenu(m_hwndParent, m_hwndMenu); }

} // namespace Core