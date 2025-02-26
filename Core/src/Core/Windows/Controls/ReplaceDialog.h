#pragma once
#include <windows.h>

#include <vector>

namespace Core
{
class ReplaceDialog
{
  public:
    ReplaceDialog() {};
    ReplaceDialog(HWND mainWindohwnd);

    void findAndReplaceText(HWND hEditField, LPCTSTR searchStr,
                            LPCTSTR szReplaceText, BOOL matchCase, BOOL wholeWord);

    void findAndReplaceAllText(HWND hEditField, LPCTSTR searchStr,
                               LPCTSTR szReplaceText, BOOL matchCase,
                               BOOL wholeWord);

    HWND getHdlg() const { return m_hdlg; }
    std::vector<wchar_t> getSZFindWhat() const { return m_szFindWhat; }

  private:
    HWND m_hdlg{};
    std::vector<wchar_t> m_szFindWhat{};
    std::vector<wchar_t> m_szReplaceText{};
    FINDREPLACE m_fr{};
};

} // namespace Core
