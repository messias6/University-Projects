#pragma once


// AddProducts dialog

class AddProducts : public CDialog
{
	DECLARE_DYNAMIC(AddProducts)

public:
	AddProducts(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddProducts();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddProducts };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString v_prodName;
	CString v_unitprice;
	afx_msg void OnBnClickedBback();
	afx_msg void OnBnClickedBaddproduct();
	afx_msg void OnCbnDropdownCprintcourse();
	CComboBox v_cprintcourse;
	afx_msg void OnCbnSelchangeCprintcourse();
	CString v_printcourse;
	int run_time = 0;
};

