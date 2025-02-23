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
    Menu(UINT flags, Menu menu, std::wstring windowName);
    Menu(HWND hwndParent, Command command);
    Menu(HWND hwndParent);
    Menu();
    // Menu(UINT flags);

    Menu(const Menu& that)            = delete;
    Menu& operator=(const Menu& that) = delete;
    Menu(Menu&& that) noexcept;
    Menu& operator=(Menu&& that) noexcept;

    void appendMenu(std::unique_ptr<Menu> menu);
    void appendMenu(UINT flags, Command command, std::wstring_view windowName);
    void appendMenu(UINT flags, Command command, std::wstring_view windowName,
                    std::function<void()> handler);
    void appendMenu(UINT flags);
    void appendMenu(UINT flags, HMENU hMenu, std::wstring_view windowName);
    void appendSelf();
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
        std::cout << "Registered commands: ";
        for (const auto& [cmd, handlers] : m_commandHandlers)
        {
            std::cout << static_cast<int>(cmd) << " ";
        }
        std::cout << std::endl;

        // Check if this menu has the command handler
        auto it = m_commandHandlers.find(command);
        if (it != m_commandHandlers.end())
        {
            for (const auto& handler : it->second)
            {
                std::cout << "Executing handler for command: "
                          << static_cast<int>(command) << "\n";
                handler();
            }
            return; // Command handled, no need to search children
        }

        // If not found, search child menus
        for (const auto& child : m_children)
        {
            if (child.second) // Ensure child is valid
            {
                child.second->handleCommand(command);
            }
        }
    }

    void addHandler(std::function<void()> handler)
    {
        m_commandHandlers[m_command].push_back(handler);
    }

  private:
    HMENU m_hwndMenu{};
    HWND m_hwndParent{};
    UINT m_flags{};
    Command m_command{};
    std::wstring m_windowName{};
    std::unordered_map<Command, std::unique_ptr<Menu>> m_children;
    std::unordered_map<Command, std::vector<std::function<void()>>>
        m_commandHandlers;
};
} // namespace Core