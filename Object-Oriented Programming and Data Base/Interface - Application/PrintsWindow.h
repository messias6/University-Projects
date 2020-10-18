#pragma once


// PrintsWindow dialog

class PrintsWindow : public CDialog
{
	DECLARE_DYNAMIC(PrintsWindow)

public:
	PrintsWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PrintsWindow();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PrintsWindow };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl v_listprints;
	afx_msg void OnNMDblclkLprints(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl v_listprodTpay;
	CString v_totalprice;
	afx_msg void OnBnClickedBremoveitem();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBprocpay();
	afx_msg void OnBnClickedBback();
};
