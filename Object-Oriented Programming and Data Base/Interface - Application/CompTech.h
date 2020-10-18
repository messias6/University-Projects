#pragma once


// CompTech dialog

class CompTech : public CDialog
{
	DECLARE_DYNAMIC(CompTech)

public:
	CompTech(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CompTech();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CompTech };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString v_employID;
	afx_msg void OnBnClickedBlogout();
	afx_msg void OnBnClickedBregnewstd();
	afx_msg void OnBnClickedButton4();
};
