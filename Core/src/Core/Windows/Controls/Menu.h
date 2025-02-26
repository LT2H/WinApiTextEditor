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
    Menu(HWND hwndParent, UINT flags, Command command, std::wstring_view windowName);
    Menu(UINT flags, Command command, std::wstring_view windowName);
    Menu(UINT flags, Menu menu, std::wstring_view windowName);
    Menu(HWND hwndParent, Command command);
    Menu(HWND hwndParent);
    Menu();

    Menu(const Menu& that)            = delete;
    Menu& operator=(const Menu& that) = delete;

    void appendMenu(UINT flags, Command command, std::wstring_view windowName);
    void appendMenu(UINT flags, Command command, std::wstring_view windowName,
                    std::function<void()> handler);
    void appendMenu(UINT flags) const;
    void appendMenu(UINT flags, HMENU hMenu, std::wstring_view windowName) const;

    void setMenu();

    constexpr HMENU getHwndMenu() const { return m_hwndMenu; }
    constexpr UINT getFlags() const { return m_flags; }
    constexpr Command getCommand() const { return m_command; }
    constexpr std::wstring getWindowName() const { return m_windowName; }

    void setCommand(Command command) { m_command = command; }
    void setMenu() const { SetMenu(m_hwndParent, m_hwndMenu); }

  private:
    HMENU m_hwndMenu{};
    HWND m_hwndParent{};
    UINT m_flags{};
    Command m_command{};
    std::wstring m_windowName{};
};

} // namespace Core