// AttEmail.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "AttEmail.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "EWApp.h"
#include "Resource.h"

// AttEmail dialog

IMPLEMENT_DYNAMIC(AttEmail, CDialog)

AttEmail::AttEmail(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AttEmail, pParent)
	, v_cpc(_T(""))
	, v_istidpc(_T(""))
{

}

AttEmail::~AttEmail()
{
}

void AttEmail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Cpc, v_cpc);
	DDX_Text(pDX, IDC_AEistid, v_istidpc);
}


BEGIN_MESSAGE_MAP(AttEmail, CDialog)
	ON_BN_CLICKED(IDC_BAssign, &AttEmail::OnBnClickedBassign)
END_MESSAGE_MAP()


// AttEmail message handlers
BOOL AttEmail::OnInitDialog() {

	CDialog::OnInitDialog();
	v_cpc = ChosenPC;
	
	UpdateData(FALSE);
	return TRUE;
}

myconnectorclassDB MyConnectionAE;

void AttEmail::OnBnClickedBassign()
{
	MyConnectionAE.connect();
	UpdateData(TRUE);
	if (MyConnectionAE.VerifyID(v_istidpc, _T("Person"))) {
		MessageBox(_T("Number not found or incorrect!"), _T("Error"), MB_ICONERROR);
	}
	else{
		if (MyConnectionAE.VerifyID(v_istidpc, _T("Student"))) {
			MessageBox(_T("You are not a Student!"), _T("Error"), MB_ICONERROR);
		}
		else {
			if (MyConnectionAE.VerifyUserHasPC(v_istidpc, _T("student"))) {

				MessageBox(_T("Computer assigned!"), _T(""), MB_ICONINFORMATION);
				time_of_startTime = CTime::GetCurrentTime().Format("%H:%M:%S");
				date_of_startTime = CTime::GetCurrentTime().Format("%Y-%m-%d");
				istidSwithPC = _T("ist") + v_istidpc;

				MyConnectionAE.InsertStudEmpl(ChosenPC, istidSwithPC, date_of_startTime, time_of_startTime, _T("student")); //insert student in use_student
				OnOK();
				
			}
			else {
				MessageBox(_T("This student already has a computer assigned!"), _T("Error"), MB_ICONERROR);
			}
		}
	}
}


