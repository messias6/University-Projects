#pragma once


// CoursesW dialog

class CoursesW : public CDialog
{
	DECLARE_DYNAMIC(CoursesW)

public:
	CoursesW(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CoursesW();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CoursesW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl v_lcourses;
	afx_msg void OnNMDblclkLcourses(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox v_cbcoursesregist;
	CString v_ccoursesregist;
	afx_msg void OnCbnDropdownCcoursesregist();
	int run_time;
	afx_msg void OnCbnSelchangeCcoursesregist();
	afx_msg void OnBnClickedBunenroll();
	afx_msg void OnBnClickedBback();
	CString update_balance;
};
