#include "Core/Core.h"
#include "Core/WinApp.h"
#include "Core/Windows/Window.h"
#include "Core/Windows/Controls/Control.h"
#include "Core/Windows/Controls/Menu.h"
#include "TextEditor.h"

#include <windows.h>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    Core::enableDebugConsole();

    Core::Window mainWindow{ hInst,       IDC_ARROW, COLOR_WINDOW, L"myWindowClass",
                             L"My Title", 100,       100,          800,
                             900,         nullptr };
    auto mainWindowHwnd{ mainWindow.getHandle() };

    Core::Control openFileButon{
        L"Button", L"Open File",   WS_VISIBLE | WS_CHILD,  10, 10, 150,
        36,        mainWindowHwnd, Core::Command::openFile
    };

    Core::Control saveFileButon{
        L"Button", L"Save File",   WS_VISIBLE | WS_CHILD,  170, 10, 150,
        36,        mainWindowHwnd, Core::Command::saveFile
    };

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

    openFileButon.addHandler(Core::Command::openFile,
                             [mainWindowHwnd, editField]()
                             { openFile(mainWindowHwnd, editField); });

    saveFileButon.addHandler(Core::Command::saveFile,
                             [mainWindowHwnd, editField]()
                             { saveFile(mainWindowHwnd, editField); });

    Core::Menu menu{ mainWindowHwnd, MF_STRING, Core::Command::openFile, L"Open" };
    menu.setMenu();

    mainWindow.addControl(openFileButon);
    mainWindow.addControl(saveFileButon);
    mainWindow.addControl(editField);

    return Core::WinApp::run();
}
