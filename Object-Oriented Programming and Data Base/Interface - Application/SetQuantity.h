#pragma once


// SetQuantity dialog

class SetQuantity : public CDialog
{
	DECLARE_DYNAMIC(SetQuantity)

public:
	SetQuantity(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SetQuantity();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SetQuantity };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString v_productname;
	CString v_unitprice;
	int v_desiredquantity;
	afx_msg void OnBnClickedBadd();
};
