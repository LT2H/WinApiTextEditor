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

void createNewWindow(HINSTANCE hInst)
{
    Core::Window mainWindow{ hInst,       IDC_ARROW, COLOR_WINDOW, L"myWindowClass",
                             L"My Title", 100,       100,          800,
                             900,         nullptr };
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

    auto mainMenu{ std::make_unique<Core::Menu>(mainWindowHwnd) };

    auto fileMenu{ std::make_unique<Core::Menu>() };

    auto subMenu{ std::make_unique<Core::Menu>() };

    auto helpMenu{ std::make_unique<Core::Menu>() };

    fileMenu->appendMenu(MF_STRING, Core::Command::openFile, L"Open...\tCtrl+O");
    mainWindow.registerFunc(Core::Command::openFile,
                            [mainWindowHwnd, editField]()
                            { openFile(mainWindowHwnd, editField); });

    fileMenu->appendMenu(
        MF_STRING, Core::Command::saveFileAs, L"Save As...\tCtrl+Shift+S");
    mainWindow.registerFunc(Core::Command::saveFileAs,
                            [mainWindowHwnd, editField]()
                            { saveFile(mainWindowHwnd, editField); });

    fileMenu->appendMenu(
        MF_STRING, Core::Command::newWindow, L"New Window\tCtrl+Shift+N");
    mainWindow.registerFunc(
        Core::Command::newWindow,
        []()
        { ShellExecute(NULL, L"open", L"App.exe", NULL, NULL, SW_SHOWNORMAL); });

    fileMenu->appendMenu(MF_SEPARATOR);

    fileMenu->appendMenu(MF_STRING, Core::Command::exit, L"Exit");

    mainMenu->appendMenu(MF_POPUP, fileMenu->getHwndMenu(), L"File");

    mainMenu->setMenu();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    Core::enableDebugConsole();

    Core::Window mainWindow{ hInst,       IDC_ARROW, COLOR_WINDOW, L"myWindowClass",
                             L"My Title", 100,       100,          800,
                             900,         nullptr };
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

    auto mainMenu{ std::make_unique<Core::Menu>(mainWindowHwnd) };

    auto fileMenu{ std::make_unique<Core::Menu>() };

    auto subMenu{ std::make_unique<Core::Menu>() };

    auto helpMenu{ std::make_unique<Core::Menu>() };

    fileMenu->appendMenu(MF_STRING, Core::Command::openFile, L"Open...\tCtrl+O");
    mainWindow.registerFunc(Core::Command::openFile,
                            [mainWindowHwnd, editField]()
                            { openFile(mainWindowHwnd, editField); });

    fileMenu->appendMenu(
        MF_STRING, Core::Command::saveFileAs, L"Save As...\tCtrl+Shift+S");
    mainWindow.registerFunc(Core::Command::saveFileAs,
                            [mainWindowHwnd, editField]()
                            { saveFile(mainWindowHwnd, editField); });

    fileMenu->appendMenu(
        MF_STRING, Core::Command::newWindow, L"New Window\tCtrl+Shift+N");
    mainWindow.registerFunc(
        Core::Command::newWindow,
        []
        {
            ShellExecute(
                NULL,
                L"open",
                L"D:\\Hung_Dev\\CPP\\repos\\WinApiTextEditor\\Binaries\\windows-x86_"
                L"64\\Debug\\App\\App.exe",
                NULL,
                NULL,
                SW_SHOWNORMAL);
        });

    fileMenu->appendMenu(MF_SEPARATOR);

    fileMenu->appendMenu(MF_STRING, Core::Command::exit, L"Exit");

    mainMenu->appendMenu(MF_POPUP, fileMenu->getHwndMenu(), L"File");

    mainMenu->setMenu();

    return Core::WinApp::run();
}
