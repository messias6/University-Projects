#pragma once


// SWApp dialog

class SWApp : public CDialog
{
	DECLARE_DYNAMIC(SWApp)

public:
	SWApp(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SWApp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SWApp };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString v_stidlogin;
	afx_msg void OnBnClickedBswalogout();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBbankaccount();
	afx_msg void OnBnClickedBprints();
	afx_msg void OnBnClickedBpurchases();
	afx_msg void OnBnClickedBcourses();
};
