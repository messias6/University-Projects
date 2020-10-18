// Addmoney.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "Addmoney.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Resource.h"
#include "Purchases.h"


// Addmoney dialog

IMPLEMENT_DYNAMIC(Addmoney, CDialog)

Addmoney::Addmoney(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Addmoney, pParent)
	, v_updbalance(_T(""))
{

}

Addmoney::~Addmoney()
{
}

void Addmoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_UpdBalance, v_updbalance);
}


BEGIN_MESSAGE_MAP(Addmoney, CDialog)
	ON_BN_CLICKED(IDC_BAddTAccount, &Addmoney::OnBnClickedBaddtaccount)
END_MESSAGE_MAP()


myconnectorclassDB MyConnectionAddM;

void Addmoney::OnBnClickedBaddtaccount()
{
	MyConnectionAddM.connect();
	UpdateData(TRUE);
	CString account_number = MyConnectionAddM.GetNumOnAcc(istidofE);
	MyConnectionAddM.AddMoneyToAccount(account_number, v_updbalance);
	UpdateData(FALSE);

	OnOK();
	Purchases P;
	P.DoModal();
}
