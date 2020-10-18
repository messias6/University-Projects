// COAccount.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "COAccount.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Purchases.h"


// COAccount dialog

IMPLEMENT_DYNAMIC(COAccount, CDialog)

COAccount::COAccount(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_COAccount, pParent)
	, v_coaiban(_T(""))
{

}

COAccount::~COAccount()
{
}

void COAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COAIban, v_coaiban);
}


BEGIN_MESSAGE_MAP(COAccount, CDialog)
	ON_BN_CLICKED(IDC_BCreateAccount, &COAccount::OnBnClickedBcreateaccount)
END_MESSAGE_MAP()


// COAccount message handlers

myconnectorclassDB MyConnectionCOA;

void COAccount::OnBnClickedBcreateaccount()
{
	MyConnectionCOA.connect();
	UpdateData(TRUE);

	// Insert in Online Account
	MyConnectionCOA.InsertInOA(v_coaiban);
	// Istid with online account in Table: has
	MyConnectionCOA.InsertStudentInHas(istidofE, v_coaiban);
	OnOK();
	Purchases P;
	P.DoModal();

}

