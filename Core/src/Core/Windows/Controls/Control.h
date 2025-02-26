#pragma once
#include <Core/utils/utils.h>

#include <windows.h>

#include <string>
#include <functional>

namespace Core
{
class Control
{
  public:
    Control() = default;

    Control(std::wstring_view className, std::wstring_view windowName, DWORD style,
            int x, int y, int width, int height, HWND hwndParent, Command command);

    Control(std::wstring_view className, std::wstring_view windowName, DWORD style,
            int x, int y, int width, int height, HWND hwndParent);

    Control(std::wstring_view className, int x, int y, int width, int height,
            HWND hwndParent);

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
};
} // namespace Core