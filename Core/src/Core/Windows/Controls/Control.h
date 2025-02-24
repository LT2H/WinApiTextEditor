#pragma once
#include <Core/utils/utils.h>

#include <windows.h>

#include <string>
#include <functional>

namespace Core
{
class Control
{
  private:
    std::wstring m_className{};
    std::wstring m_windowName{};
    DWORD m_style{};
    int m_x{};
    int m_y{};
    int m_width{};
    int m_height{};
    HWND m_hwndParent{};
    Command m_command{};
    HWND m_hwnd{};
    std::unordered_map<Command, std::vector<std::function<void()>>>
        m_commandHandlers{};

  public:
    Control() = default;
    Control(std::wstring className, std::wstring windowName, DWORD style, int x,
            int y, int width, int height, HWND hwndParent, Command command);

    Control(std::wstring className, std::wstring windowName, DWORD style, int x,
            int y, int width, int height, HWND hwndParent);

    Control(std::wstring className, int x, int y, int width, int height,
            HWND hwndParent);

    // void create();

    constexpr std::wstring getClassName() const { return m_className; }
    constexpr std::wstring getWindowName() const { return m_windowName; }
    constexpr DWORD getStyle() const { return m_style; }
    constexpr int getX() const { return m_x; }
    constexpr int getY() const { return m_y; }
    constexpr int getWidth() const { return m_width; }
    constexpr int getHeight() const { return m_height; }
    constexpr HWND getHwndParent() const { return m_hwndParent; }
    constexpr Command getCommand() const { return m_command; }
    constexpr HWND getHwnd() const { return m_hwnd; }

    void addHandler(std::function<void()> handler)
    {
        m_commandHandlers[m_command].push_back(handler);
    }

    void handleCommand(const Command command)
    {
        for (const auto& handler : m_commandHandlers[command])
        {
            handler();
        }
    }
};
} // namespace Core