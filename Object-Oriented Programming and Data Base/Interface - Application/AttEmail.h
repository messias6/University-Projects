#pragma once


// AttEmail dialog

class AttEmail : public CDialog
{
	DECLARE_DYNAMIC(AttEmail)

public:
	AttEmail(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AttEmail();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AttEmail };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString v_cpc;
	afx_msg void OnBnClickedBassign();
	

	CString v_istidpc;
};
