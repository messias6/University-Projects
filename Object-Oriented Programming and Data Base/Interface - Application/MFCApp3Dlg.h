
// MFCApp3Dlg.h : header file
//

#pragma once


// CMFCApp3Dlg dialog
class CMFCApp3Dlg : public CDialogEx
{
// Construction
public:
	CMFCApp3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPP3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString v_lemail;
	afx_msg void OnBnClickedLbutt();
	afx_msg void OnBnClickedFpass();
private:
	CString v_lpass;
public:
	CString v_femail;
};
