// Purchases.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "Purchases.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Resource.h"
#include "Addmoney.h"
#include "SWApp.h"


// Purchases dialog

IMPLEMENT_DYNAMIC(Purchases, CDialog)

Purchases::Purchases(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Purchases, pParent)
	, v_acc_number(_T(""))
	, v_balance(_T(""))
{

}

Purchases::~Purchases()
{
}

void Purchases::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LPrints, v_lprints);
	DDX_Control(pDX, IDC_LCourses, v_lcourses);
	DDX_Text(pDX, IDC_acc_number, v_acc_number);
	DDX_Text(pDX, IDC_balance, v_balance);
}


BEGIN_MESSAGE_MAP(Purchases, CDialog)
	ON_BN_CLICKED(IDC_Bback, &Purchases::OnBnClickedBback)
	ON_BN_CLICKED(IDC_BAddM, &Purchases::OnBnClickedBaddm)
END_MESSAGE_MAP()


myconnectorclassDB MyConnectionPurchW;


BOOL Purchases::OnInitDialog() {
	
	CDialog::OnInitDialog();
	MyConnectionPurchW.connect();

	// Account Number
	v_acc_number = MyConnectionPurchW.GetNumOnAcc(istidofE);
	// Current Balance
	v_balance = MyConnectionPurchW.GetNumOnAccPrice(istidofE);

	// List with all Prints
	v_lprints.InsertColumn(0, L"Name", LVCFMT_LEFT, 150);
	v_lprints.InsertColumn(1, L"Quantity", LVCFMT_LEFT, 55);
	v_lprints.InsertColumn(2, L"Price", LVCFMT_LEFT, 40);
	v_lprints.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// List with all Courses
	v_lcourses.InsertColumn(0, L"Name", LVCFMT_LEFT, 140);
	v_lcourses.InsertColumn(1, L"Price", LVCFMT_LEFT, 40);
	v_lcourses.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int nItem;
	CString v_name, v_quantity, v_price, str_price;
	int NPID = MyConnectionPurchW.NumbOfPID(istidofE);
	for (int i = 0; i < NPID; i++) {
		// Name
		v_name = MyConnectionPurchW.GetPNameQtdPriceOFStd(i, _T("P.product_name"), istidofE);
		nItem = v_lprints.InsertItem(0, v_name);
		// Quantity
		v_quantity = MyConnectionPurchW.GetPNameQtdPriceOFStd(i, _T("SUM(pp.quantity)"), istidofE);
		v_lprints.SetItemText(nItem, 1, v_quantity);
		// Price
		v_price = MyConnectionPurchW.GetPNameQtdPriceOFStd(i, _T("SUM(pp.quantity)*P.price"), istidofE);
		float float_price = _ttof(v_price);
		str_price.Format(_T("%0.2f"), float_price);
		v_lprints.SetItemText(nItem, 2, str_price);
	}
	
	
	int NCID = MyConnectionPurchW.NumbOfCID(istidofE);
	for (int i = 0; i < NCID; i++) {
		// Name
		v_name = MyConnectionPurchW.GetCNameQtdPriceOFStd(i, _T("P.product_name"), istidofE);
		nItem = v_lcourses.InsertItem(0, v_name);
		// Price
		v_price = MyConnectionPurchW.GetCNameQtdPriceOFStd(i, _T("P.price"), istidofE);
		v_lcourses.SetItemText(nItem, 1, v_price);
	}

	UpdateData(FALSE);
	return TRUE;
}

// BACK
void Purchases::OnBnClickedBback()
{
	OnOK();
	SWApp SWA;
	SWA.DoModal();
}

// ADD MONEY
void Purchases::OnBnClickedBaddm()
{
	OnOK();
	Addmoney AM;
	AM.DoModal();
}



