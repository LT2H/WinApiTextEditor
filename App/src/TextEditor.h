#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Core/Windows/Controls/Control.h"

int displayFile(const std::wstring& path, const Core::Control& editField);

void openFile(HWND hwnd, const Core::Control& editField);

void saveFile(HWND hwnd, const Core::Control& editField);

int writeFile(const std::wstring& path, const Core::Control& editField);
