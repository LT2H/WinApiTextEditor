#pragma once
#include <Core/utils/utils.h>

#include <windows.h>

#include <string>
#include <unordered_map>
#include <functional>

namespace Core
{
class Menu
{
  public:
    Menu(HWND hwndParent, UINT flags, Command command, std::wstring windowName);
    Menu(UINT flags, Command command, std::wstring windowName);
    Menu(HWND hwndParent);
    Menu(UINT flags);

    void appendMenu(const Menu& menu);

    void appendMenu();

    void appendMenu(UINT flags);

    void appendMenu(UINT flags, Command command, std::wstring windowName);

    void setMenu();

    HMENU getHwndMenu() const { return m_hwndMenu; }

    UINT getFlags() const { return m_flags; }

    Command getCommand() const { return m_command; }

    std::wstring getWindowName() const { return m_windowName; }

    void setMenu() const { SetMenu(m_hwndParent, m_hwndMenu); }

  private:
    HMENU m_hwndMenu{};
    HWND m_hwndParent{};
    UINT m_flags{};
    Command m_command{};
    std::wstring m_windowName{};

    std::unordered_map<Command, std::vector<std::function<void()>>>
        m_commandHandlers{};
};
} // namespace Core