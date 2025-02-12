#pragma once
#include <windows.h>

#include <string>
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
    int m_id{};

  public:
    explicit Control(std::wstring className, std::wstring windowName, DWORD style,
                     int x, int y, int width, int height, HWND hwndParent, int id);

    std::wstring getClassName() const { return m_className; }
    std::wstring getWindowName() const { return m_windowName; }
    DWORD getStyle() const { return m_style; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    HWND getHwndParent() const { return m_hwndParent; }
    int getId() const { return m_id; }
};
} // namespace Core