#pragma once


// Test2 dialog

class Test2 : public CDialog
{
	DECLARE_DYNAMIC(Test2)

public:
	Test2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Test2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Test2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
