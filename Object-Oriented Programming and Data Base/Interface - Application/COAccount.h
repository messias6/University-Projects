#pragma once


// COAccount dialog

class COAccount : public CDialog
{
	DECLARE_DYNAMIC(COAccount)

public:
	COAccount(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COAccount();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COAccount };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString v_coaiban;
	afx_msg void OnBnClickedBcreateaccount();
};
