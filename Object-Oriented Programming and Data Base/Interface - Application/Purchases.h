#pragma once


// Purchases dialog

class Purchases : public CDialog
{
	DECLARE_DYNAMIC(Purchases)

public:
	Purchases(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Purchases();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Purchases };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl v_lprints;
	CListCtrl v_lcourses;
	afx_msg void OnBnClickedBback();
	CString v_acc_number;
	CString v_balance;
	afx_msg void OnBnClickedBaddm();
	
};
