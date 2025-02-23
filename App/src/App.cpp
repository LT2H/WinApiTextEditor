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
#include <array>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
#ifdef DEBUG
    Core::enableDebugConsole();
#endif // DEBUG
    Core::Window& mainWindow{ Core::Window::initialize(hInst,
                                                       IDC_ARROW,
                                                       COLOR_WINDOW,
                                                       L"myWindowClass",
                                                       L"My Title",
                                                       100,
                                                       100,
                                                       800,
                                                       900,
                                                       nullptr) };

    TextEditor textEditor{};

    return Core::WinApp::run();
}
