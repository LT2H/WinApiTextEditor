#include "Menu.h"

namespace Core
{
Menu::Menu(HWND hwndParent, UINT flags, Command command, std::wstring windowName)
    : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }, m_flags{ flags },
      m_command{ command }, m_windowName{ windowName }
{
}

Menu::Menu(UINT flags, Command command, std::wstring windowName)
    : m_hwndMenu{ CreateMenu() }, m_flags{ flags }, m_command{ command },
      m_windowName{ windowName }
{
}

Menu::Menu(HWND hwndParent, Command command)
    : m_hwndMenu{ CreateMenu() }, m_hwndParent{ hwndParent }, m_flags{ 0 },
      m_command{ command }
{
}

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
    : m_hwndMenu{ std::move(that).m_hwndMenu },
      m_hwndParent{ std::move(that).m_hwndParent },
      m_flags{ std::move(that).m_flags }, m_command{ std::move(that).m_command },
      m_windowName{ std::move(that).m_windowName },
      m_menus{ std::move(that).m_menus },
      m_commandHandlers{ std::move(that).m_commandHandlers }
{
}

Menu& Menu::operator=(Menu&& that) noexcept
{
    m_hwndMenu        = std::move(that.m_hwndMenu);
    m_hwndParent      = std::move(that.m_hwndParent);
    m_flags           = std::move(that.m_flags);
    m_command         = std::move(that.m_command);
    m_windowName      = std::move(that.m_windowName);
    m_menus           = std::move(that.m_menus);
    m_commandHandlers = std::move(that.m_commandHandlers);

    return *this;
}

void Menu::appendMenu(std::unique_ptr<Menu> menu)
{
    std::cout << "Appending menu with command: "
              << static_cast<int>(menu->getCommand()) << std::endl;

    AppendMenu(m_hwndMenu,
               menu->getFlags(),
               reinterpret_cast<UINT_PTR>(menu->getHwndMenu()),
               menu->getWindowName().c_str());

    addChild(std::move(menu));
}

void Menu::addChild(std::unique_ptr<Menu> menu)
{
    std::cout << "command at addChild() is: " << static_cast<int>(menu->getCommand())
              << std::endl;
    // Make sure you use the correct command here and it’s not zero
    if (menu->getCommand() != Command::nothing)
    {
        m_menus[menu->getCommand()] = std::move(menu);
    }
    else
    {
        std::cout << "Invalid command passed to addChild!" << std::endl;
    }
}

void Menu::setMenu() { SetMenu(m_hwndParent, m_hwndMenu); }

} // namespace Core