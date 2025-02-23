#include "TextEditor.h"
#include "Core/Windows/Window.h"

#include <windows.h>

#include <iostream>
#include <array>
#include <filesystem>

TextEditor::TextEditor() {
    auto& mainWindow{ Core::Window::getInstance() };
    mainWindow.registerHotkeys();
    auto mainWindowHwnd{ mainWindow.getHandle() };

    Core::Control editField{ L"Edit",
                             L"",
                             WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER |
                                 ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL |
                                 WS_HSCROLL,
                             10,
                             50,
                             400,
                             300,
                             mainWindowHwnd };

    Core::Menu mainMenu{ mainWindowHwnd };
    Core::Menu fileMenu;
    Core::Menu subMenu;
    Core::Menu helpMenu;

    
    fileMenu.appendMenu(
        MF_STRING, Core::Command::newWindow, L"New Window\tCtrl+Shift+N");
    mainWindow.registerFunc(Core::Command::newWindow, [this] { launchNewWindow(); });

    fileMenu.appendMenu(MF_STRING, Core::Command::openFile, L"Open...\tCtrl+O");
    mainWindow.registerFunc(Core::Command::openFile,
                            [this, mainWindowHwnd, &editField]()
                            { openFile(mainWindowHwnd, editField); });

    fileMenu.appendMenu(MF_STRING, Core::Command::saveFile, L"Save\tCtrl+S");
    mainWindow.registerFunc(Core::Command::saveFile,
                            [this, mainWindowHwnd, &editField]()
                            { saveFile(mainWindowHwnd, editField); });

    fileMenu.appendMenu(
        MF_STRING, Core::Command::saveFileAs, L"Save As...\tCtrl+Shift+S");
    mainWindow.registerFunc(Core::Command::saveFileAs,
                            [this, mainWindowHwnd, &editField]()
                            { saveFileAs(mainWindowHwnd, editField); });

    fileMenu.appendMenu(MF_SEPARATOR);

    fileMenu.appendMenu(MF_STRING, Core::Command::exit, L"Exit");

    mainMenu.appendMenu(MF_POPUP, fileMenu.getHwndMenu(), L"File");

    mainMenu.setMenu();
}

int TextEditor::displayFile(const std::wstring& path, const Core::Control& editField)
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

void TextEditor::openFile(HWND hwnd, const Core::Control& editField)
{
    OPENFILENAME ofn{};
    std::vector<wchar_t> fileName(100);

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hwnd;
    ofn.lpstrFile    = fileName.data();
    ofn.nMaxFile     = static_cast<DWORD>(fileName.size());
    ofn.lpstrFilter  = L"All Files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    if (GetOpenFileName(&ofn))
    {
        currentFilePath = fileName.data(); // Store the selected file path

        MessageBox(nullptr, fileName.data(), L"Selected File", MB_OK);
        displayFile(ofn.lpstrFile, editField);
    }
}

void TextEditor::saveFile(HWND hwnd, const Core::Control& editField)
{
    if (currentFilePath.empty())
    {
        saveFileAs(hwnd, editField);
    }
    else
    {
        writeFile(currentFilePath, editField);
    }
}

void TextEditor::saveFileAs(HWND hwnd, const Core::Control& editField)
{
    OPENFILENAME ofn{};
    std::vector<wchar_t> fileName(100);

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hwnd;
    ofn.lpstrFile    = fileName.data();
    ofn.nMaxFile     = static_cast<DWORD>(fileName.size());
    ofn.lpstrFilter  = L"All Files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_OVERWRITEPROMPT; // This will show a built-in overwrite warning

    if (GetSaveFileName(&ofn))
    {
        currentFilePath = fileName.data(); // Store the file path

        std::wstring_view filePath{ ofn.lpstrFile };

        writeFile(filePath, editField);
        MessageBox(nullptr, fileName.data(), L"Saved File To", MB_OK);
    }
}

int TextEditor::writeFile(std::wstring_view path, const Core::Control& editField)
{
    std::wofstream outfile(path.data(), std::ios::binary);
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

void TextEditor::launchNewWindow()
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
