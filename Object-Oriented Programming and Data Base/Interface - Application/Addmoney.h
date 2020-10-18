#pragma once


// Addmoney dialog

class Addmoney : public CDialog
{
	DECLARE_DYNAMIC(Addmoney)

public:
	Addmoney(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Addmoney();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Addmoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBaddtaccount();
	CString v_updbalance;
};
