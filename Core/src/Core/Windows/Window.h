#pragma once
#include <Core/Windows/Controls/Control.h>
#include <Core/Windows/Controls/Menu.h>
#include <Core/Windows/Controls/FindDialog.h>
#include <Core/Windows/Controls/ReplaceDialog.h>
#include <Core/utils/utils.h>
#include <Core/utils/Hotkey.h>
#include <windows.h>
#include <string>
#include <span>
#include <unordered_map>

namespace Core
{
class Window
{
  public:
    HWND getHandle() { return m_hwnd; }

    void registerControl(const Control& control);

    void registerFindDialog(FindDialog* dialog);

    void registerReplaceDialog(ReplaceDialog* dialog);

    void addMenu(std::unique_ptr<Menu> mainMenu);

    void registerFunc(Command command, std::function<void()> func);

    int registerHotkeys(std::span<Hotkey> m_hotkeys) const;

    static Window& initialize(HINSTANCE hInst, LPCWSTR cursorId, int color,
                              std::wstring className, std::wstring windowName, int x,
                              int y, int width, int height, HWND hwndParent);

    static Window& getInstance();

  private:
    Window(HINSTANCE hInst, LPCWSTR cursorId, int color, std::wstring className,
           std::wstring windowName, int x, int y, int width, int height,
           HWND hwndParent);

    WNDCLASS m_wc{};
    static HWND m_hwnd;
    static UINT m_findMsg;
    static std::unordered_map<std::wstring, Control> m_controls;
    static std::unordered_map<int, HWND> m_control_handles;
    static FindDialog* m_findDialog;
    static ReplaceDialog* m_replaceDialog;
    static std::vector<std::unique_ptr<Menu>> m_menus;

    static std::unordered_map<Command, std::function<void()>> m_registered_funcs;

    static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    static Window* m_instance;
};
} // namespace Core