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

// void FindAndReplaceText()
//{
//     if (_tcslen(szFindText) == 0 || _tcslen(szReplaceText) == 0)
//         return;
//
//     FINDTEXTEX ft{};
//     CHARRANGE cr{};
//     SendMessage(hEdit, EM_EXGETSEL, 0, (LPARAM)&cr);
//
//     ft.chrg.cpMin = cr.cpMax;
//     ft.chrg.cpMax = -1;
//     ft.lpstrText  = szFindText;
//
//     int foundPos = SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, (LPARAM)&ft);
//     if (foundPos != -1)
//     {
//         // Select the found text
//         SendMessage(hEdit, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
//
//         // Replace text
//         SendMessage(hEdit, EM_REPLACESEL, TRUE, (LPARAM)szReplaceText);
//     }
//     else
//     {
//         MessageBox(
//             NULL, _T("Text not found!"), _T("Replace"), MB_OK |
//             MB_ICONINFORMATION);
//     }
// }

void FindDialog::searchFile(HWND hEditField, LPCTSTR searchStr, BOOL searchDown,
                            BOOL matchCase)
{
    FINDTEXTEX ft{};
    CHARRANGE cr{};
    SendMessage(hEditField, EM_EXGETSEL, 0, (LPARAM)&cr); // Get current selection

    int textLength{ GetWindowTextLength(hEditField) };

    std::cout << textLength << "\n";

    if (searchDown)
    {
        std::cout << "Searching downward\n";
        ft.chrg.cpMin = cr.cpMax;
        ft.chrg.cpMax = textLength;
    }
    else
    {
        ft.chrg.cpMin = cr.cpMin; // Start at current selection
        ft.chrg.cpMax = 0;        // Search backward to the beginning
    }
    ft.lpstrText = searchStr;

    int flags{ matchCase ? FR_MATCHCASE : 0 };

    int64_t foundPos{ SendMessage(hEditField, EM_FINDTEXTEX, flags, (LPARAM)&ft) };
    if (foundPos != -1)
    {
        SendMessage(hEditField, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
        SendMessage(hEditField, EM_SCROLLCARET, 0, 0);

        // Apply Character Format
        CHARFORMAT2 cf{};
        cf.cbSize      = sizeof(CHARFORMAT2);
        cf.dwMask      = CFM_BACKCOLOR;    // Enable background color change
        cf.crBackColor = RGB(0, 120, 215); // Blue background

        SendMessage(hEditField, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
    }
    else
    {
        MessageBox(
            NULL, _T("Text not found!"), _T("Find"), MB_OK | MB_ICONINFORMATION);
    }
}

void FindDialog::clearSelection(HWND hEditField)
{
    // Reset character formatting for the whole text
    CHARFORMAT2 cf{};
    cf.cbSize      = sizeof(CHARFORMAT2);
    cf.dwMask      = CFM_BACKCOLOR;
    cf.crBackColor = GetSysColor(COLOR_WINDOW); // Reset to default background color

    SendMessage(hEditField, EM_SETSEL, 0, -1);  // Select all text
    SendMessage(hEditField, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
    SendMessage(hEditField, EM_SETSEL, -1, 0);  // Deselect text
}


} // namespace Core