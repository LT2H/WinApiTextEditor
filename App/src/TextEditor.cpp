#include "TextEditor.h"
#include <windows.h>
#include <iostream>
#include <array>
#include <filesystem>

int displayFile(const std::wstring& path, const Core::Control& editField)
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

    SetWindowText(editField.getHwnd(), content.data());
}

void openFile(HWND hwnd, const Core::Control& editField)
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
        displayFile(ofn.lpstrFile, editField);
    }
}

void saveFile(HWND hwnd, const Core::Control& editField)
{
    OPENFILENAME ofn{};
    std::vector<wchar_t> fileName(100, L'\0'); // Initialize with null characters

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hwnd;
    ofn.lpstrFile    = fileName.data();
    ofn.nMaxFile     = static_cast<DWORD>(fileName.size());
    ofn.lpstrFilter  = L"All Files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_OVERWRITEPROMPT; // This will show a built-in overwrite warning

    if (GetSaveFileName(&ofn))
    {
        std::wstring filePath{ ofn.lpstrFile };

        writeFile(ofn.lpstrFile, editField);
        MessageBox(nullptr, fileName.data(), L"Saved File To", MB_OK);
    }
}

int writeFile(const std::wstring& path, const Core::Control& editField)
{
    std::wofstream outfile(path, std::ios::binary);
    if (!outfile)
    {
        MessageBox(
            nullptr, L"Uh oh, could not open file!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    int editLength{ GetWindowTextLength(editField.getHwnd()) + 1 };

    std::vector<wchar_t> data(editLength);

    GetWindowText(editField.getHwnd(), data.data(), editLength);

    std::wstringstream buffer{};
    buffer << data.data();

    outfile << buffer.str();
}
void launchNewWindow()
{
    std::array<wchar_t, MAX_PATH> exePath{};
    GetModuleFileNameW(nullptr, exePath.data(), MAX_PATH);

    // Remove the executable name, keep only the directory
    wchar_t* lastSlash{ wcsrchr(exePath.data(), L'\\') };
    if (lastSlash)
    {
        *lastSlash = L'\0'; // Terminate at the last backslash
    }

    // Construct the new path to App.exe
    std::wstring newWindowPath{ std::wstring(exePath.data()) + L"\\App.exe" };

    ShellExecuteW(
        nullptr, L"open", newWindowPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}
