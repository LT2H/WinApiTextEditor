#include "TextEditor.h"
#include <iostream>

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
