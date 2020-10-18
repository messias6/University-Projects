#pragma once


// EWApp dialog

class EWApp : public CDialog
{
	DECLARE_DYNAMIC(EWApp)

public:
	EWApp(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EWApp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EWApp };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString v_ewstudentid;
	CString v_ewstudentemail;
	afx_msg void OnBnClickedEwlogout();
	CListCtrl v_List2;
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox v_cbcupcs;
	CString v_cupcs;
	int run_time;
	afx_msg void OnCbnSelchangeCupcs();
	afx_msg void OnCbnDropdownCupcs();
	afx_msg void OnBnClickedBrsfpc();
	CString v_rstufrpc;
};
