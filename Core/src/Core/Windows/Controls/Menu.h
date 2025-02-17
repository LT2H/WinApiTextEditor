#pragma once
#include <Core/utils/utils.h>

#include <windows.h>

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <iostream>

namespace Core
{
class Menu
{
  public:
    // Menu() = default;

    Menu(HWND hwndParent, UINT flags, Command command, std::wstring windowName);
    Menu(UINT flags, Command command, std::wstring windowName);
    Menu(HWND hwndParent, Command command);
    // Menu(UINT flags);

    Menu(const Menu& that)            = delete;
    Menu& operator=(const Menu& that) = delete;
    Menu(Menu&& that) noexcept;
    Menu& operator=(Menu&& that) noexcept;

    void appendMenu(std::unique_ptr<Menu> menu);

    void addChild(std::unique_ptr<Menu> menu);

    void setMenu();

    void setCommand(Command command) { m_command = command; }

    HMENU getHwndMenu() const { return m_hwndMenu; }

    UINT getFlags() const { return m_flags; }

    Command getCommand() const { return m_command; }

    std::wstring getWindowName() const { return m_windowName; }

    void setMenu() const { SetMenu(m_hwndParent, m_hwndMenu); }

    void handleCommand(const Command command)
    {
        std::cout << "at handleCommand m_commandHandler's size is: "
                  << m_commandHandlers.size() << std::endl;

        if (m_commandHandlers.find(command) == m_commandHandlers.end())
        {
            std::cout << "No handler found for command: "
                      << static_cast<int>(command) << "\n";
            return;
        }

        for (const auto& handler : m_commandHandlers[command])
        {
            std::cout << "Executing handler for command: "
                      << static_cast<int>(command) << "\n";
            handler();
        }
    }

    void addHandler(std::function<void()> handler)
    {
        m_commandHandlers[m_command].push_back(handler);
        std::cout << "at addHandler m_commandHandler's size is: "
                  << m_commandHandlers.size() << std::endl;
    }

  private:
    HMENU m_hwndMenu{};
    HWND m_hwndParent{};
    UINT m_flags{};
    Command m_command{};
    std::wstring m_windowName{};
    std::unordered_map<Command, std::unique_ptr<Menu>> m_menus;
    std::unordered_map<Command, std::vector<std::function<void()>>>
        m_commandHandlers;
};
} // namespace Core