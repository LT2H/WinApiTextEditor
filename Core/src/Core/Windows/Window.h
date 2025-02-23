#pragma once
#include <Core/Windows/Controls/Control.h>
#include <Core/Windows/Controls/Menu.h>
#include <Core/utils/utils.h>
#include <Core/utils/Hotkey.h>
#include <windows.h>
#include <string>
#include <span>
#include <unordered_map>

namespace Core
{

constexpr int OPEN_FILE_BUTTON{ 1 };
constexpr int SAVE_FILE_BUTTON{ 2 };

class Window
{
  public:
    HWND getHandle() { return m_hwnd; }

    void addControl(const Control& control);

    void addMenu(std::unique_ptr<Menu> mainMenu);

    void registerFunc(Command command, std::function<void()> func);

    int registerHotkeys(std::span<Hotkey> m_hotkeys) const;

    static Window& initialize(HINSTANCE hInst, LPCWSTR cursorId, int color,
                       std::wstring className, std::wstring windowName, int x, int y,
                       int width, int height, HWND hwndParent);

    static Window& getInstance();

  private:
    Window(HINSTANCE hInst, LPCWSTR cursorId, int color, std::wstring className,
           std::wstring windowName, int x, int y, int width, int height,
           HWND hwndParent);

    WNDCLASS m_wc{};
    static HWND m_hwnd;
    static std::vector<Control> m_controls;
    static std::unordered_map<int, HWND> m_control_handles;

    static std::vector<std::unique_ptr<Menu>> m_menus;

    static std::unordered_map<Command, std::function<void()>> m_registered_funcs;

    static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    static Window* m_instance;
};
} // namespace Core