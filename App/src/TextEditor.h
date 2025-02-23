#include <Core/Windows/Controls/Control.h>
#include <Core/utils/utils.h>
#include <Core/Utils/Hotkey.h>

#include <windows.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

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

    void undo();

  private:
    std::wstring m_currentFilePath{};
    Core::Control m_editField;
    std::array<Core::Hotkey, 5> m_hotkeys{
        { { MOD_CONTROL, Core::Command::openFile, 'O' },
          { MOD_CONTROL, Core::Command::saveFile, 'S' },
          { MOD_CONTROL | MOD_SHIFT, Core::Command::saveFileAs, 'S' },
          { MOD_CONTROL, Core::Command::undo, 'Z' },
          { MOD_CONTROL, Core::Command::help, 'H' } }
    };
};
