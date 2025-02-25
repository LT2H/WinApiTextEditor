#include "ReplaceDialog.h"

#include <windows.h>
#include <Richedit.h>
#include <tchar.h>
#include <iostream>

namespace Core
{

// Function to show Replace Dialog
// void ShowReplaceDialog(HWND hwnd)
//{
//    ZeroMemory(&fr, sizeof(FINDREPLACE));
//
//    fr.lStructSize      = sizeof(FINDREPLACE);
//    fr.hwndOwner        = hwnd;
//    fr.lpstrFindWhat    = szFindText;
//    fr.lpstrReplaceWith = szReplaceText;
//    fr.wFindWhatLen     = sizeof(szFindText) / sizeof(TCHAR);
//    fr.wReplaceWithLen  = sizeof(szReplaceText) / sizeof(TCHAR);
//    fr.Flags            = FR_DOWN;
//
//    ReplaceText(&fr);
//}

ReplaceDialog::ReplaceDialog(HWND mainWindohwnd)
    : m_szFindWhat(80, L'\0'), m_szReplaceText(80, L'\0')
{
    ZeroMemory(&m_fr, sizeof(FINDREPLACE));

    m_fr.lStructSize      = sizeof(FINDREPLACE);
    m_fr.hwndOwner        = mainWindohwnd;
    m_fr.lpstrFindWhat    = m_szFindWhat.data();
    m_fr.lpstrReplaceWith = m_szReplaceText.data();
    m_fr.wFindWhatLen     = static_cast<int>(m_szFindWhat.size());
    m_fr.Flags            = 0;
    m_fr.wReplaceWithLen  = static_cast<int>(m_szReplaceText.size());

    m_hdlg = ReplaceText(&m_fr);

    // Hide "Find Next" button after the dialog is created
    if (m_hdlg)
    {
        HWND hFindNextButton{ GetDlgItem(m_hdlg, IDOK) };
        if (hFindNextButton)
        {
            ShowWindow(hFindNextButton, SW_HIDE); // Hide button
        }
    }
}

void ReplaceDialog::findAndReplaceText(HWND hEditField, LPCTSTR searchStr,
                                       LPCTSTR szReplaceText, BOOL matchCase,
                                       BOOL wholeWord)
{
    FINDTEXTEX ft{};
    CHARRANGE cr{};
    SendMessage(hEditField, EM_EXGETSEL, 0, (LPARAM)&cr);

    ft.chrg.cpMin = cr.cpMax;
    ft.chrg.cpMax = -1;
    ft.lpstrText  = searchStr;

    int flags{ FR_DOWN };
    if (matchCase)
    {
        flags |= FR_MATCHCASE;
    }
    if (wholeWord)
    {
        flags |= FR_WHOLEWORD;
    }

    int64_t foundPos{ SendMessage(hEditField, EM_FINDTEXTEX, flags, (LPARAM)&ft) };

    if (foundPos != -1)
    {
        SendMessage(hEditField, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
        SendMessage(hEditField, EM_REPLACESEL, TRUE, (LPARAM)szReplaceText);
    }
    else
    {
        MessageBox(
            NULL, _T("Text not found!"), _T("Replace"), MB_OK | MB_ICONINFORMATION);
    }
}

void ReplaceDialog::findAndReplaceAllText(HWND hEditField, LPCTSTR searchStr,
                                          LPCTSTR szReplaceText, BOOL matchCase,
                                          BOOL wholeWord)
{
    FINDTEXTEX ft{};
    CHARRANGE cr{};
    SendMessage(hEditField, EM_EXGETSEL, 0, (LPARAM)&cr);

    ft.chrg.cpMin = cr.cpMax;
    ft.chrg.cpMax = -1;
    ft.lpstrText  = searchStr;

    int flags{ FR_DOWN };
    if (matchCase)
    {
        flags |= FR_MATCHCASE;
    }
    if (wholeWord)
    {
        flags |= FR_WHOLEWORD;
    }

    while (true)
    {
        int64_t foundPos{ SendMessage(
            hEditField, EM_FINDTEXTEX, flags, (LPARAM)&ft) };
        if (foundPos != -1)
        {
            SendMessage(hEditField, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
            SendMessage(hEditField, EM_REPLACESEL, TRUE, (LPARAM)szReplaceText);
        }
        else
        {
            MessageBox(NULL,
                       _T("Text not found!"),
                       _T("Replace"),
                       MB_OK | MB_ICONINFORMATION);
            break;
        }
    }
}

} // namespace Core