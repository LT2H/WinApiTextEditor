#include <Core/Windows/Controls/Control.h>
#include <Core/Windows/Controls/FindDialog.h>
#include <Core/Windows/Controls/ReplaceDialog.h>
#include <Core/utils/utils.h>
#include <Core/Utils/Hotkey.h>

#include <windows.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <memory>

class TextEditor
{
  public:
    TextEditor();

    void openFile(HWND hwnd, const Core::Control& editField);

    void saveFile(HWND hwnd, const Core::Control& editField);

    void saveFileAs(HWND hwnd, const Core::Control& editField);

    int writeFile(std::wstring_view path, const Core::Control& editField);

    void showFindDialog(HWND mainWindowHwnd);

    void showReplaceDialog(HWND mainWindowHwnd);

    void launchNewWindow();

    void undo();

    void redo();

    void selectAll();

  private:
    std::wstring m_currentFilePath{};
    Core::Control m_editField;

    std::array<Core::Hotkey, 8> m_hotkeys{ {
        { MOD_CONTROL, Core::Command::openFile, 'O' },
        { MOD_CONTROL, Core::Command::saveFile, 'S' },
        { MOD_CONTROL | MOD_SHIFT, Core::Command::saveFileAs, 'S' },
        { MOD_CONTROL, Core::Command::undo, 'Z' },
        { MOD_CONTROL, Core::Command::redo, 'Y' },
        { MOD_CONTROL, Core::Command::selectAll, 'A' },
        { MOD_CONTROL, Core::Command::showFindDialog, 'F' },
        { MOD_CONTROL, Core::Command::showReplaceDialog, 'H' },
    } };

    std::unique_ptr<Core::FindDialog> m_findDialog;
    std::unique_ptr<Core::ReplaceDialog> m_replaceDialog;

  private: // member functions
    int displayFile(const std::wstring& path, const Core::Control& editField);
};
