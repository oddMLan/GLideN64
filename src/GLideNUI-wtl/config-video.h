#define _WTL_NO_CSTRING

#pragma once
#include "config-tab.h"
#include "config-overscan.h"
#include "wtl-AutoComplete.h"
#include "wtl-BitmapPicture.h"
#include "resource.h"
#include <vector>

class CVideoTab :
    public CConfigTab
{
public:
    CContainedWindow m_Edit;

    BEGIN_MSG_MAP(CVideoTab)
        MSG_WM_INITDIALOG(OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLORDLG, OnColorStatic)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnColorStatic)
        MESSAGE_HANDLER(WM_PRINTCLIENT, OnColorStatic)
        NOTIFY_HANDLER_EX(IDC_TAB_OVERSCAN, TCN_SELCHANGE, OnOverscanTabChange)
        COMMAND_HANDLER_EX(IDC_CMB_FULL_SCREEN_RES, CBN_SELCHANGE, OnFullScreenChanged)
        COMMAND_HANDLER_EX(IDC_CHK_OVERSCAN, BN_CLICKED, OnOverscan)
        MESSAGE_HANDLER(WM_HSCROLL, OnScroll)
        MESSAGE_HANDLER(WM_VSCROLL, OnScroll)
        REFLECT_NOTIFICATIONS()
        ALT_MSG_MAP(1)
            //MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
            MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
    END_MSG_MAP()

    CVideoTab();
    ~CVideoTab();

    BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
    LRESULT OnScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    void OnOverscan(UINT /*Code*/, int id, HWND /*ctl*/);
    LRESULT OnColorStatic(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnOverscanTabChange(NMHDR* /*pNMHDR*/);
    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    void OnFullScreenChanged(UINT /*Code*/, int id, HWND /*ctl*/);
    void AddOverScanTab(const wchar_t * caption);
    void ShowOverScanTab(int nTab);
    void LoadSettings(bool blockCustomSettings);
    void SaveSettings();

    CAutoCombo m_WindowedResolutionComboBox;
    CTabCtrl m_OverScanTab;
    std::vector<COverScanTab *> m_OverscanTabs;
    CTrackBarCtrl m_AliasingSlider;
    CTrackBarCtrl m_AnisotropicSlider;
    CBitmapPicture m_AAInfoIcon;
};
