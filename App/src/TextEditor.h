#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Core/Windows/Controls/Control.h"

class TextEditor
{
  public:
    TextEditor();

    int displayFile(const std::wstring& path, const Core::Control& editField);

    void openFile(HWND hwnd, const Core::Control& editField);

    void saveFile(HWND hwnd, const Core::Control& editField);

    void saveFileAs(HWND hwnd, const Core::Control& editField);

    int writeFile(std::wstring_view path, const Core::Control& editField);

    void launchNewWindow();

private:
    std::wstring currentFilePath{};
};

