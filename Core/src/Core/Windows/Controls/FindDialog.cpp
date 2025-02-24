#include "FindDialog.h"
#include "Core\Windows\Window.h"
#include <windows.h>
#include <Richedit.h>
#include <tchar.h>
namespace Core
{
FindDialog::FindDialog(HWND mainWindohwnd) : m_szFindWhat(80, L'\0')
{
    ZeroMemory(&m_fr, sizeof(FINDREPLACE));

    m_fr.lStructSize   = sizeof(FINDREPLACE);
    m_fr.hwndOwner     = mainWindohwnd;
    m_fr.lpstrFindWhat = m_szFindWhat.data();
    m_fr.wFindWhatLen  = static_cast<int>(m_szFindWhat.size());
    m_fr.Flags         = 0;

    m_hdlg = FindText(&m_fr);
}

void FindDialog::searchFile(HWND hEditField, LPCTSTR searchStr, BOOL searchDown,
                            BOOL matchCase)
{
    FINDTEXTEX ft{};
    CHARRANGE cr{};
    SendMessage(hEditField, EM_EXGETSEL, 0, (LPARAM)&cr); // Get current selection

    ft.chrg.cpMin = cr.cpMax; // Start after current selection
    ft.chrg.cpMax = -1;       // Search till end
    ft.lpstrText  = searchStr;

    int flags = searchDown ? FR_DOWN : 0;
    if (matchCase)
        flags |= FR_MATCHCASE;

    int foundPos = SendMessage(hEditField, EM_FINDTEXTEX, flags, (LPARAM)&ft);
    if (foundPos != -1)
    {
        std::cout << "Found\n";

        SendMessage(hEditField, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
        SendMessage(hEditField, EM_SCROLLCARET, 0, 0);

        // Apply Character Format
        CHARFORMAT2 cf{};
        cf.cbSize      = sizeof(CHARFORMAT2);
        cf.dwMask      = CFM_BACKCOLOR;    // Enable background color change
        cf.crBackColor = RGB(0, 120, 215); // Blue background (Windows Accent Blue)

        SendMessage(hEditField, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
    }
    else
    {
        MessageBox(
            NULL, _T("Text not found!"), _T("Find"), MB_OK | MB_ICONINFORMATION);
    }
}


} // namespace Core