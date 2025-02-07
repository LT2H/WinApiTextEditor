#include "Core/Core.h"
#include <windows.h>

LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

void addControls(HWND hwnd);

constexpr int OPEN_FILE_BUTTON{ 1 };
constexpr int SAVE_FILE_BUTTON{ 2 };

HWND hMainWindow{};
HWND hEdit{};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    // MessageBox(nullptr, L"HELLO", L"My title", MB_OK);
    WNDCLASSW wc{};

    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance     = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc   = windowProc;

    if (!RegisterClass(&wc))
        return -1;

    hMainWindow = CreateWindow(wc.lpszClassName,
                               L"My Title",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               100,
                               100,
                               800,
                               900,
                               nullptr,
                               nullptr,
                               nullptr,
                               nullptr);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
        addControls(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}

void addControls(HWND hwnd)
{
    CreateWindow(L"Button",
                 L"Open File",
                 WS_VISIBLE | WS_CHILD,
                 10,
                 10,
                 150,
                 36,
                 hwnd,
                 reinterpret_cast<HMENU>(OPEN_FILE_BUTTON),
                 nullptr,
                 nullptr);

    CreateWindow(L"Button",
                 L"Save File",
                 WS_VISIBLE | WS_CHILD,
                 170,
                 10,
                 150,
                 36,
                 hwnd,
                 reinterpret_cast<HMENU>(SAVE_FILE_BUTTON),
                 nullptr,
                 nullptr);

    hEdit =
        CreateWindow(L"Edit",
                     L"",
                     WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER |
                         ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL,
                     10,
                     50,
                     400,
                     300,
                     hwnd,
                     nullptr,
                     nullptr,
                     nullptr);
}