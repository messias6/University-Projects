// EWApp.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "MFCApp3Dlg.h"
#include "EWApp.h"
#include "myconnectorclassDB.h"
#include "afxdialogex.h"
#include "AttEmail.h"
#include "Resource.h"



// EWApp dialog

IMPLEMENT_DYNAMIC(EWApp, CDialog)

EWApp::EWApp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EWApp, pParent)
	, v_ewstudentid(_T(""))
	, v_ewstudentemail(_T(""))
	, v_cupcs(_T(""))
{

}

EWApp::~EWApp()
{
}

void EWApp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EStudentID, v_ewstudentid);
	DDX_Text(pDX, IDC_EStudentEmail, v_ewstudentemail);
	DDX_Control(pDX, IDC_LIST2, v_List2);
	DDX_Control(pDX, IDC_CUPcs, v_cbcupcs);
	DDX_CBString(pDX, IDC_CUPcs, v_cupcs);
	
}


BEGIN_MESSAGE_MAP(EWApp, CDialog)
	ON_BN_CLICKED(IDC_EWLogout, &EWApp::OnBnClickedEwlogout)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &EWApp::OnNMDblclkList2)
	ON_CBN_SELCHANGE(IDC_CUPcs, &EWApp::OnCbnSelchangeCupcs)
	ON_CBN_DROPDOWN(IDC_CUPcs, &EWApp::OnCbnDropdownCupcs)
	ON_BN_CLICKED(IDC_BRSfpc, &EWApp::OnBnClickedBrsfpc)
END_MESSAGE_MAP()


// EWApp message handlers

myconnectorclassDB MyConnectionEWA;

void EWApp::OnBnClickedEwlogout()
{
	CString tnow = CTime::GetCurrentTime().Format("%H:%M:%S");
	MyConnectionEWA.connect();


	MyConnectionEWA.LogOutEmployee(istidofE, tnow);    // Add the end_time value when logging out!

	OnOK();  // Close the open dialog
	CMFCApp3Dlg LO;
	LO.DoModal(); // Open the dialog
}

BOOL EWApp::OnInitDialog()
{
	CDialog::OnInitDialog();
	MyConnectionEWA.connect();
	v_ewstudentid = istidofE;
	v_ewstudentemail = EmailConnect;
	run_time = 0;

	v_List2.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_LEFT,    // Relative position of items under header 
		40);           // Width of items under header

	v_List2.InsertColumn(1, L"Location", LVCFMT_LEFT, 80);
	v_List2.SetExtendedStyle(LVS_EX_FULLROWSELECT);


	int nItem;
	CString v_listp, v_location;
	int npcsUsed = MyConnectionEWA.GetNTPCs() - MyConnectionEWA.GetNPCsUsed(_T("student")) - MyConnectionEWA.GetNPCsUsed(_T("employee"));
	for (int i = 0; i < npcsUsed; i++) {
		v_listp = MyConnectionEWA.GetPCseLocation(i, _T("pc_ID"));
		nItem = v_List2.InsertItem(0, v_listp);
		v_location = MyConnectionEWA.GetPCseLocation(i, _T("location"));
		v_List2.SetItemText(nItem,1, v_location);

	}

	UpdateData(FALSE);
	return TRUE;
}



void EWApp::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	v_List2.ScreenToClient(&point);

	int nIndex;
	if ((nIndex = v_List2.HitTest(point)) != -1) {
		// If you are in this if block, that means an item on the list
		//   was chosen and nIndex is the index of the selected item
		//   from the list.
		CString getvalue = v_List2.GetItemText(nIndex, 0);
		ChosenPC = getvalue;

		// Opens new window to insert student's number
		AttEmail AE;
		AE.DoModal();

		run_time = 0; // For only run Dropdown CUPcs once

		// To update the table of the available computers
		int nItem;
		CString v_listp, v_location;
		MyConnectionEWA.connect();
		v_List2.SetRedraw(FALSE);
		v_List2.DeleteAllItems();
		v_List2.SetRedraw(TRUE);
		int npcsAvail = MyConnectionEWA.GetNTPCs() - MyConnectionEWA.GetNPCsUsed(_T("student")) - MyConnectionEWA.GetNPCsUsed(_T("employee"));
		for (int i = 0; i < npcsAvail; i++) {
			v_listp = MyConnectionEWA.GetPCseLocation(i, _T("pc_ID"));
			nItem = v_List2.InsertItem(0, v_listp);
			v_location = MyConnectionEWA.GetPCseLocation(i, _T("location"));
			v_List2.SetItemText(nItem, 1, v_location);

		}

		// Update the combo list after assigning a computer
		v_cbcupcs.ResetContent();
		if (run_time == 0) {
			CString v_listpcNused;
			MyConnectionEWA.connect();
			int nPCsNAvail1 = MyConnectionEWA.GetNPCsUsed(_T("student"));
			for (int i = 0; i < nPCsNAvail1; i++) {
				v_listpcNused = MyConnectionEWA.GetPCsNotAvail(i);
				v_cbcupcs.AddString(v_listpcNused);
			}
			UpdateData(FALSE);
			run_time++;
		}
		return;
	}
	*pResult = 0;
}



void EWApp::OnCbnSelchangeCupcs()
{
	// Gets the value and saves it in v_cupcs
	v_cbcupcs.GetLBText(v_cbcupcs.GetCurSel(), v_cupcs);
	UpdateData(FALSE);
	if (v_cupcs[0] == '\0') {

	}
	else {
		GetDlgItem(IDC_BRSfpc)->EnableWindow(TRUE);
	}
}


void EWApp::OnCbnDropdownCupcs()
{
	if (run_time == 0) {
		CString v_listpcNused;
		MyConnectionEWA.connect();
		int nPCsNAvail = MyConnectionEWA.GetNPCsUsed(_T("student"));
		for (int i = 0; i < nPCsNAvail; i++) {
			v_listpcNused = MyConnectionEWA.GetPCsNotAvail(i);
			v_cbcupcs.AddString(v_listpcNused);
		}
		UpdateData(FALSE);
		run_time++;
	}
}

// Button to Remove Student from PC
void EWApp::OnBnClickedBrsfpc()
{

		MyConnectionEWA.connect();
		CString end_time_now = CTime::GetCurrentTime().Format("%H:%M:%S");
		time_of_startTime = MyConnectionEWA.GetStimeEdateFRid(v_cupcs, istidSwithPC, date_of_startTime);

		// Remove student from PC
		MyConnectionEWA.RemoveStudentFrPC(v_cupcs, end_time_now, istidSwithPC, date_of_startTime, time_of_startTime);
		MessageBox(_T("Computer ") + v_cupcs + _T(" removed!"), _T(""), MB_ICONINFORMATION);
		
		run_time = 0; // For only run Dropdown CUPcs once

		// To update the table of the available computers
		int nItem;
		CString v_listp, v_location;
		MyConnectionEWA.connect();
		v_List2.SetRedraw(FALSE);
		v_List2.DeleteAllItems();
		v_List2.SetRedraw(TRUE);
		int npcsAvail = MyConnectionEWA.GetNTPCs() - MyConnectionEWA.GetNPCsUsed(_T("student")) - MyConnectionEWA.GetNPCsUsed(_T("employee"));
		for (int i = 0; i < npcsAvail; i++) {
			v_listp = MyConnectionEWA.GetPCseLocation(i, _T("pc_ID"));
			nItem = v_List2.InsertItem(0, v_listp);
			v_location = MyConnectionEWA.GetPCseLocation(i, _T("location"));
			v_List2.SetItemText(nItem, 1, v_location);

		}

		// Update the combo list after assigning a computer
		v_cbcupcs.ResetContent();
		if (run_time == 0) {
			CString v_listpcNused;
			MyConnectionEWA.connect();
			int nPCsNAvail = MyConnectionEWA.GetNPCsUsed(_T("student"));
			for (int i = 0; i < nPCsNAvail; i++) {
				v_listpcNused = MyConnectionEWA.GetPCsNotAvail(i);
				v_cbcupcs.AddString(v_listpcNused);
			}
			UpdateData(FALSE);
			run_time++;
		}
		GetDlgItem(IDC_BRSfpc)->EnableWindow(FALSE);
		UpdateData(FALSE);

}
