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
    mainWindow.registerHotkeys();
    auto mainWindowHwnd{ mainWindow.getHandle() };

    /* Core::Control openFileButon{
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

     openFileButon.addHandler([mainWindowHwnd, editField]()
                              { openFile(mainWindowHwnd, editField); });

     saveFileButon.addHandler([mainWindowHwnd, editField]()
                              { saveFile(mainWindowHwnd, editField); });*/

    // auto fileMenu{ std::make_unique<Core::Menu>(
    //     MF_POPUP, Core::Command::nothing, L"File") };
    // auto newMenu{ std::make_unique<Core::Menu>(
    //     MF_STRING, Core::Command::nothing, L"New") };

    // auto openSubMenu{ std::make_unique<Core::Menu>(
    //     MF_POPUP, Core::Command::nothing, L"Open SubMenu") };
    // auto changeTitleSubMenu{ std::make_unique<Core::Menu>(
    //     MF_STRING, Core::Command::nothing, L"Change Title") };

    // openSubMenu->appendMenu(std::move(changeTitleSubMenu));

    //// auto seperator{ std::make_unique<Core::Menu>(MF_SEPARATOR) };
    // auto exitMenu{ std::make_unique<Core::Menu>(
    //     MF_STRING, Core::Command::nothing, L"Exit") };

    // fileMenu->appendMenu(std::move(newMenu));
    // fileMenu->appendMenu(std::move(openSubMenu));
    //// fileMenu->appendMenu(seperator);
    // fileMenu->appendMenu(std::move(exitMenu));

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
        MF_STRING, Core::Command::saveFileAs, L"Save As...\tCtrl+S");
    mainWindow.registerFunc(Core::Command::saveFileAs,
                            [mainWindowHwnd, editField]()
                            { saveFile(mainWindowHwnd, editField); });

    fileMenu->appendMenu(MF_STRING, Core::Command::exit, L"Exit");

    mainMenu->appendMenu(MF_POPUP, fileMenu->getHwndMenu(), L"File");

    mainMenu->setMenu();

    /*  mainWindow.addControl(openFileButon);
      mainWindow.addControl(saveFileButon);
      mainWindow.addControl(editField);*/

    return Core::WinApp::run();
}
