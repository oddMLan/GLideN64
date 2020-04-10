#define _WTL_NO_CSTRING

#pragma once
#include "WTL\atlcrack.h"
#include <atlstr.h>

class CAutoCombo : public CWindowImpl<CAutoCombo, CComboBox>
{
protected:
    bool	m_bAutoComplete;
public:

    CAutoCombo()
    {
        m_bAutoComplete = TRUE;
    }
    BEGIN_MSG_MAP(CAutoCombo)
        //MESSAGE_HANDLER(WM_CHAR, OnKeyDown)
        REFLECTED_COMMAND_CODE_HANDLER_EX(CBN_EDITUPDATE, OnEditUpdate)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    BOOL SubclassWindow(HWND hWnd)
    {
        return(CWindowImpl< CAutoCombo, CComboBox >::SubclassWindow(hWnd));
    }

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnEditUpdate(UINT, int, HWND)
    {
        MessageBox(L"OnEditUpdate");
        // if we are not to auto update the text, get outta here
        if (!m_bAutoComplete) {
            MessageBox(L"cancellation succesfull");
            return S_OK;
        }

        // Get the text in the edit box
        ATL::CString str;
        GetWindowText(str);
        int nLength = str.GetLength();

        // Currently selected range
        DWORD dwCurSel = GetEditSel();
        WORD dStart = LOWORD(dwCurSel);
        WORD dEnd = HIWORD(dwCurSel);

        // Search for, and select in, and string in the combo box that is prefixed
        // by the text in the edit box
        if (SelectString(-1, str) == CB_ERR)
        {
            SetWindowText(str);		// No text selected, so restore what was there before
            if (dwCurSel != CB_ERR)
                SetEditSel(dStart, dEnd);	//restore cursor postion
        }

        // Set the text selection as the additional text that we have added
        if (dEnd < nLength && dwCurSel != CB_ERR)
            SetEditSel(dStart, dEnd);
        else
            SetEditSel(nLength, -1);
        return S_OK;
    }

    LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        // Need to check for backspace/delete. These will modify the text in
        // the edit box, causing the auto complete to just add back the text
        // the user has just tried to delete.
        if (wParam == VK_DELETE || wParam == VK_BACK)
        {
            MessageBox(L"inside if");
            m_bAutoComplete = FALSE;
            bHandled = TRUE;
            return S_OK;
        }
        MessageBox(L"outside if");
        m_bAutoComplete = TRUE;
        bHandled = FALSE;
        return S_OK;
    }
};
