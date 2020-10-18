// RegisterStd.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "RegisterStd.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Resource.h"
#include <cctype>

// RegisterStd dialog

IMPLEMENT_DYNAMIC(RegisterStd, CDialog)

RegisterStd::RegisterStd(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RegisterStd, pParent)
	, v_stdid(_T(""))
	, v_name(_T(""))
	, v_nif(_T(""))
	, v_email(_T(""))
	, v_pass(_T(""))
{

}

RegisterStd::~RegisterStd()
{
}

void RegisterStd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_stdID, v_stdid);
	DDX_Text(pDX, IDC_name, v_name);
	DDX_Text(pDX, IDC_NIF, v_nif);
	DDX_Text(pDX, IDC_email, v_email);
	DDX_Text(pDX, IDC_Pass, v_pass);
}


BEGIN_MESSAGE_MAP(RegisterStd, CDialog)
	ON_BN_CLICKED(IDC_Bback, &RegisterStd::OnBnClickedBback)
	ON_BN_CLICKED(IDC_BRegisterStd, &RegisterStd::OnBnClickedBregisterstd)
END_MESSAGE_MAP()


// RegisterStd message handlers

myconnectorclassDB MyConnectionRS;

void RegisterStd::OnBnClickedBback()
{
	OnOK();
}

// See if cstring is a number
// isnan wasn't working, don't know why
BOOL is_number(CString str) {
	for (int i = 0; i < str.GetLength(); i++) {
		if (!std::isdigit(str[i]))
			// string is not a number
			return FALSE;
	}
	// String is number
	return TRUE;
}


void RegisterStd::OnBnClickedBregisterstd()
{
	UpdateData(TRUE);
	MyConnectionRS.connect();

	CString rID = v_stdid;
	CString rName = v_name;
	CString rNIF = v_nif;
	CString rEmail = v_email;
	CString rPass = v_pass;

	if (is_number(rID)) {
		if (is_number(rNIF)) {

			if (MyConnectionRS.SeeIDExists(rID)) {

				if (MessageBox(_T("Are you sure you want to proceed?"), _T(""), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
					MyConnectionRS.NewPerson(rID, rName, rNIF, rEmail, rPass);
					MyConnectionRS.NewStdOREmployee(rID, _T("Student"));
				}
				OnOK();
			}
			else {
				MessageBox(_T("This person already has an account!"), _T("Error"), MB_ICONEXCLAMATION);
			}
			UpdateData(FALSE);
		}
		else {
			MessageBox(_T("Please insert a number"), _T("Error"), MB_ICONERROR);
		}
	}
	else {
		MessageBox(_T("Please insert a number"), _T("Error"), MB_ICONERROR);
	}
	UpdateData(FALSE);
}
		
	

