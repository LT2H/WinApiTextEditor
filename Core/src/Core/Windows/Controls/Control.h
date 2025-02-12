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
    explicit Control(std::wstring className, std::wstring windowName, DWORD style,
                     int x, int y, int width, int height, HWND hwndParent,
                     Command command);

    explicit Control(std::wstring className, std::wstring windowName, DWORD style,
                     int x, int y, int width, int height, HWND hwndParent);

    // void create();

    std::wstring getClassName() const { return m_className; }
    std::wstring getWindowName() const { return m_windowName; }
    DWORD getStyle() const { return m_style; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    HWND getHwndParent() const { return m_hwndParent; }
    Command getCommand() const { return m_command; }
    HWND getHwnd() const { return m_hwnd; }

    void addHandler(const Command command, std::function<void()> handler)
    {
        m_commandHandlers[command].push_back(handler);
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