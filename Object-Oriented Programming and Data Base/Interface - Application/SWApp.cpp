// SWApp.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "SWApp.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "MFCApp3Dlg.h"
#include "Resource.h"
#include "PrintsWindow.h"
#include "Purchases.h"
#include "CoursesW.h"
#include "COAccount.h"

// SWApp dialog

IMPLEMENT_DYNAMIC(SWApp, CDialog)

SWApp::SWApp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SWApp, pParent)
	, v_stidlogin(_T(""))
{

}

SWApp::~SWApp()
{
}

void SWApp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_StIDLogIn, v_stidlogin);
}


BEGIN_MESSAGE_MAP(SWApp, CDialog)
	ON_BN_CLICKED(IDC_BSWAlogout, &SWApp::OnBnClickedBswalogout)
	ON_BN_CLICKED(IDC_BBankAccount, &SWApp::OnBnClickedBbankaccount)
	ON_BN_CLICKED(IDC_BPrints, &SWApp::OnBnClickedBprints)
	ON_BN_CLICKED(IDC_BCourses, &SWApp::OnBnClickedBcourses)
END_MESSAGE_MAP()


// SWApp message handlers

myconnectorclassDB MyConnectionSWA;

// LOG OUT BUTTON
void SWApp::OnBnClickedBswalogout()
{
	MyConnectionSWA.connect();

	OnOK();  
	CMFCApp3Dlg LO;
	LO.DoModal(); 
}

BOOL SWApp::OnInitDialog()
{
	v_stidlogin = istidofE;

	UpdateData(FALSE);
	return TRUE;
}

// BANK ACCOUNT BUTTON and SHOPPING RECORD
void SWApp::OnBnClickedBbankaccount()
{
	MyConnectionSWA.connect();

	if (MyConnectionSWA.VerifyStIDhasOnlineAccount(istidofE)) {
		// Create online account
		MessageBox(_T("You do not have an online account!\nPlease proceed if you wish to create one!"), _T(""), MB_ICONEXCLAMATION);
		COAccount COA;
		COA.DoModal();
	}
	else {
		// Add money or check shopping record
		OnOK();
		Purchases PurchW;
		PurchW.DoModal();
	}
}

// PRINTS BUTTON
void SWApp::OnBnClickedBprints()
{
	MyConnectionSWA.connect();

	if (MyConnectionSWA.VerifyStIDhasOnlineAccount(istidofE)) {
		MessageBox(_T("You do not have an Online Account!\nGo back and create one by clicking - Bank Account - button!"), _T(""), MB_ICONSTOP);
	}
	else {
		PrintsWindow PW;
		PW.DoModal();
	}
	
}

// COURSES BUTTON
void SWApp::OnBnClickedBcourses()
{
	MyConnectionSWA.connect();

	if (MyConnectionSWA.VerifyStIDhasOnlineAccount(istidofE)) {
		MessageBox(_T("You do not have an Online Account!\nGo back and create one by clicking - Bank Account - button!"), _T(""), MB_ICONSTOP);
	}
	else {
		CoursesW CW;
		CW.DoModal();
	}
}

