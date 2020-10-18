// CompTech.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "MFCApp3Dlg.h"
#include "CompTech.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Resource.h"
#include "AddProducts.h"
#include "RegisterStd.h"



// CompTech dialog

IMPLEMENT_DYNAMIC(CompTech, CDialog)

CompTech::CompTech(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CompTech, pParent)
	, v_employID(_T(""))
{

}

CompTech::~CompTech()
{
}

void CompTech::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_employID, v_employID);
}


BEGIN_MESSAGE_MAP(CompTech, CDialog)
	ON_BN_CLICKED(IDC_Blogout, &CompTech::OnBnClickedBlogout)
	ON_BN_CLICKED(IDC_BRegNewStd, &CompTech::OnBnClickedBregnewstd)
	ON_BN_CLICKED(IDC_BUTTON4, &CompTech::OnBnClickedButton4)
END_MESSAGE_MAP()


// CompTech message handlers

myconnectorclassDB MyConnectionCT;

BOOL CompTech::OnInitDialog() {
	CDialog::OnInitDialog();
	MyConnectionCT.connect();
	v_employID = istidofE;

	UpdateData(FALSE);
	return TRUE;
}

void CompTech::OnBnClickedBlogout()
{
	OnOK();  // Close the open dialog
	CMFCApp3Dlg LO;
	LO.DoModal(); // Open the dialog
}


void CompTech::OnBnClickedBregnewstd()
{
	RegisterStd RS;
	RS.DoModal();
}


void CompTech::OnBnClickedButton4()
{
	AddProducts AP;
	AP.DoModal();
}



