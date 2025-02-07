#include "Core/Core.h"
#include "Core/WinApp.h"
#include "Core/Windows/Window.h"
#include "Core/Windows/Controls/Control.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

void addControls(HWND hwnd);

int displayFile(const std::wstring& path);

void openFile(HWND hwnd);

int writeFile(const std::wstring& path);

void saveFile(HWND hwnd);

constexpr int OPEN_FILE_BUTTON{ 1 };
constexpr int SAVE_FILE_BUTTON{ 2 };

HWND hMainWindow{};
HWND hEdit{};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    /*WNDCLASSW wc{};

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
                               nullptr);*/

    /*Window::Window(HINSTANCE hInst,
                   LPCWSTR cursorId,
                   HBRUSH color,
                   std::wstring className,
                   std::wstring windowName,
                   int x,
                   int y,
                   int width,
                   int height,
                   HWND hwndParent)*/

    Core::Window mainWindow{ hInst,       IDC_ARROW, COLOR_WINDOW, L"myWindowClass",
                             L"My Title", 100,       100,          800,
                             900,         nullptr };

    Core::Control openFileButon{
        L"Button", L"Open File",           WS_VISIBLE | WS_CHILD, 10, 10, 150,
        36,        mainWindow.getHandle(), OPEN_FILE_BUTTON
    };

    Core::Control saveFileButon{
        L"Button", L"Save File",           WS_VISIBLE | WS_CHILD, 170, 10, 150,
        36,        mainWindow.getHandle(), SAVE_FILE_BUTTON
    };

    Core::Control editFileButon{ L"Edit",
                                 L"",
                                 WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER |
                                     ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL |
                                     WS_HSCROLL,
                                 10,
                                 50,
                                 400,
                                 300,
                                 mainWindow.getHandle(),
                                 0 };

    return Core::WinApp::run();
}

// LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//     switch (msg)
//     {
//     case WM_CREATE:
//         addControls(hwnd);
//         break;
//
//     case WM_COMMAND:
//         switch (wp)
//         {
//         case OPEN_FILE_BUTTON:
//         {
//             openFile(hwnd);
//             break;
//         }
//
//         case SAVE_FILE_BUTTON:
//             saveFile(hwnd);
//             break;
//
//         default:
//             break;
//         }
//
//         break;
//
//     case WM_DESTROY:
//         PostQuitMessage(0);
//         break;
//
//     default:
//         return DefWindowProc(hwnd, msg, wp, lp);
//     }
// }

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

int displayFile(const std::wstring& path)
{
    std::wifstream file(path, std::ios::binary);
    if (!file)
    {
        MessageBox(nullptr, L"Failed to open file!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    std::wstringstream buffer{};
    buffer << file.rdbuf();

    std::wstring content{};
    content = buffer.str();

    SetWindowText(hEdit, content.data());
}

void openFile(HWND hwnd)
{
    OPENFILENAME ofn{};
    std::vector<wchar_t> fileName(100); // Initialize with null characters

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hwnd;
    ofn.lpstrFile    = fileName.data();
    ofn.nMaxFile     = static_cast<DWORD>(fileName.size());
    ofn.lpstrFilter  = L"All Files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    if (GetOpenFileName(&ofn))
    {
        MessageBox(nullptr, fileName.data(), L"Selected File", MB_OK);
        displayFile(ofn.lpstrFile);
    }
}

int writeFile(const std::wstring& path)
{
    std::wofstream outfile(path, std::ios::binary);
    if (!outfile)
    {
        MessageBox(
            nullptr, L"Uh oh, could not open file!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    int editLength{ GetWindowTextLength(hEdit) + 1 };

    std::vector<wchar_t> data(editLength);

    GetWindowText(hEdit, data.data(), editLength);

    std::wstringstream buffer{};
    buffer << data.data();

    outfile << buffer.str();
}

void saveFile(HWND hwnd)
{
    OPENFILENAME ofn{};
    std::vector<wchar_t> fileName(100, L'\0'); // Initialize with null characters

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hwnd;
    ofn.lpstrFile    = fileName.data();
    ofn.nMaxFile     = static_cast<DWORD>(fileName.size());
    ofn.lpstrFilter  = L"All Files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    if (GetSaveFileName(&ofn))
    {
        MessageBox(nullptr, fileName.data(), L"Saved File To", MB_OK);
        writeFile(ofn.lpstrFile);
    }
}