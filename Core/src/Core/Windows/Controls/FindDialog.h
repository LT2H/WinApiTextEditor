#pragma once

#include <windows.h>
#include <vector>

namespace Core
{
class FindDialog
{
  public:
    FindDialog() {};
    FindDialog(HWND mainWindohwnd);

    void searchFile(HWND hEditField, LPCTSTR searchStr, BOOL searchDown,
                    BOOL matchCase, BOOL matchWholeWord);

    HWND getHdlg() const { return m_hdlg; }
    std::vector<wchar_t> getSZFindWhat() const { return m_szFindWhat; }

  private:
    HWND m_hdlg{};
    std::vector<wchar_t> m_szFindWhat{};
    FINDREPLACE m_fr{};
};

} // namespace Core
