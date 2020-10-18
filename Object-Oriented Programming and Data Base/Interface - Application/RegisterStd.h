#pragma once


// RegisterStd dialog

class RegisterStd : public CDialog
{
	DECLARE_DYNAMIC(RegisterStd)

public:
	RegisterStd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RegisterStd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RegisterStd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString v_stdid;
	CString v_name;
	CString v_nif;
	CString v_email;
	CString v_pass;
	afx_msg void OnBnClickedBback();
	afx_msg void OnBnClickedBregisterstd();
};
