// CoursesW.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "CoursesW.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "Resource.h"


// CoursesW dialog

IMPLEMENT_DYNAMIC(CoursesW, CDialog)

CoursesW::CoursesW(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CoursesW, pParent)
	, v_ccoursesregist(_T(""))
{

}

CoursesW::~CoursesW()
{
}

void CoursesW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LCourses, v_lcourses);
	DDX_Control(pDX, IDC_CcoursesRegist, v_cbcoursesregist);
	DDX_CBString(pDX, IDC_CcoursesRegist, v_ccoursesregist);
}


BEGIN_MESSAGE_MAP(CoursesW, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LCourses, &CoursesW::OnNMDblclkLcourses)
	ON_CBN_DROPDOWN(IDC_CcoursesRegist, &CoursesW::OnCbnDropdownCcoursesregist)
	ON_CBN_SELCHANGE(IDC_CcoursesRegist, &CoursesW::OnCbnSelchangeCcoursesregist)
	ON_BN_CLICKED(IDC_Bunenroll, &CoursesW::OnBnClickedBunenroll)
	ON_BN_CLICKED(IDC_Bback, &CoursesW::OnBnClickedBback)
END_MESSAGE_MAP()


// CoursesW message handlers

myconnectorclassDB MyConnectionCW;

// LIST OF COURSES
BOOL CoursesW::OnInitDialog(){

	CDialog::OnInitDialog();
	MyConnectionCW.connect();
	run_time = 0;

	// List with all Courses
	v_lcourses.InsertColumn(0, L"Name", LVCFMT_LEFT, 135);
	v_lcourses.InsertColumn(1, L"Availability", LVCFMT_LEFT, 70);
	v_lcourses.InsertColumn(2, L"Price", LVCFMT_LEFT, 40);
	v_lcourses.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int j = 0;
	int nItem;
	CString v_name, v_availability, v_price;
	int ncourses = MyConnectionCW.GetNPrintsECourses(_T("Courses")); //- MyConnectionCW.NumbOfCID(istidofE);
	for (int i = 0; i < ncourses; i++) {
		// Name
		v_name = MyConnectionCW.GetCourses(i, _T("P.product_name"));
		// CString getname = MyConnectionCW.CheckStdISinC(j, istidofE);

		if (MyConnectionCW.CheckStdISinC(istidofE,v_name)) {
			nItem = v_lcourses.InsertItem(0, v_name);
			// Places available
			v_availability = MyConnectionCW.GetCourses(i, _T("(C.capacity - COUNT(pc.product_ID))"));
			v_lcourses.SetItemText(nItem, 1, v_availability);
			// Price
			v_price = MyConnectionCW.GetCourses(i, _T("P.price"));
			v_lcourses.SetItemText(nItem, 2, v_price);
		}
	}

	UpdateData(FALSE);
	return TRUE;
}

// DOUBLE CLICK IN LIST
void CoursesW::OnNMDblclkLcourses(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	v_lcourses.ScreenToClient(&point);

	MyConnectionCW.connect();

	int nIndex;
	if ((nIndex = v_lcourses.HitTest(point)) != -1) {

		CString getvalue = v_lcourses.GetItemText(nIndex, 0); //saves chosen value in getvalue
		NameProduct = getvalue; //Name of chosen product	
		getvalue = v_lcourses.GetItemText(nIndex, 2);
		UnitPriceProduct = getvalue;  // Unit price of chosen product

		float UPrice = _ttof(UnitPriceProduct);
		
		run_time = 0;

		// Money in online_account
		CString balance_str = MyConnectionCW.GetNumOnAccPrice(istidofE);
		float balance = _ttof(balance_str);

		if ((balance - UPrice) < 0) {
			MessageBox(_T("You do not have enough money in your online account!"), _T("Error"), MB_ICONERROR);
		}
		else {
			CString account_number = MyConnectionCW.GetNumOnAcc(istidofE); // account_number
			CString prod_ID = MyConnectionCW.GetIDofProdName(NameProduct); // product_ID

			// Balance update
			update_balance.Format(_T("%0.2f"), (balance - UPrice));

			MessageBox(_T("You have enrolled in the course: ") + NameProduct + ("!\n"));
			MyConnectionCW.AddToPayCourses(account_number, prod_ID);
			MyConnectionCW.UpdateOABalance(account_number, update_balance);

		}

		// Update List of Courses
		v_lcourses.SetRedraw(FALSE);
		v_lcourses.DeleteAllItems();
		v_lcourses.SetRedraw(TRUE);

		int j = 0;
		int nItem;
		CString v_name, v_availability, v_price;
		int ncourses = MyConnectionCW.GetNPrintsECourses(_T("Courses")); //- MyConnectionCW.NumbOfCID(istidofE);
		for (int i = 0; i < ncourses; i++) {
			// Name
			v_name = MyConnectionCW.GetCourses(i, _T("P.product_name"));
			// CString getname = MyConnectionCW.CheckStdISinC(j, istidofE);

			if (MyConnectionCW.CheckStdISinC(istidofE, v_name)) {
				nItem = v_lcourses.InsertItem(0, v_name);
				// Places available
				v_availability = MyConnectionCW.GetCourses(i, _T("(C.capacity - COUNT(pc.product_ID))"));
				v_lcourses.SetItemText(nItem, 1, v_availability);
				// Price
				v_price = MyConnectionCW.GetCourses(i, _T("P.price"));
				v_lcourses.SetItemText(nItem, 2, v_price);
			}
		}

		// Update the combo list after assigning a computer
		v_cbcoursesregist.ResetContent();
		if (run_time == 0) {
			CString v_listcoursesregist;
			MyConnectionCW.connect();
			int ncoursesregis = MyConnectionCW.NumbofCRegist(istidofE);
			for (int i = 0; i < ncoursesregis; i++) {
				v_listcoursesregist = MyConnectionCW.GetCoursesRegist(i, istidofE);
				v_cbcoursesregist.AddString(v_listcoursesregist);
			}
			UpdateData(FALSE);
			run_time++;
		}
		GetDlgItem(IDC_Bunenroll)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}
	*pResult = 0;
}


//------------------------------------------------------------
//                    UNENROLL COURSES
//------------------------------------------------------------


// COMBO LIST
void CoursesW::OnCbnDropdownCcoursesregist()
{
	if (run_time == 0) {
		CString v_listcoursesregist;
		MyConnectionCW.connect();
		int ncoursesregis = MyConnectionCW.NumbofCRegist(istidofE);
		for (int i = 0; i < ncoursesregis; i++) {
			v_listcoursesregist = MyConnectionCW.GetCoursesRegist(i, istidofE);
			v_cbcoursesregist.AddString(v_listcoursesregist);
		}
		UpdateData(FALSE);
		run_time++;
	}
}

// COMBO LIST
void CoursesW::OnCbnSelchangeCcoursesregist()
{
	// Gets the value and saves it in v_ccoursesregist
	v_cbcoursesregist.GetLBText(v_cbcoursesregist.GetCurSel(), v_ccoursesregist);
	UpdateData(FALSE);
	if (v_ccoursesregist[0] == '\0') {

	}
	else {
		// To enable the button to unenroll but only after selecting a course
		GetDlgItem(IDC_Bunenroll)->EnableWindow(TRUE);
	}
}


// BUTTON - Unenroll from Course
void CoursesW::OnBnClickedBunenroll()
{
	MyConnectionCW.connect();
	CString acc_numb = MyConnectionCW.GetNumOnAcc(istidofE); // Get's the account_number of the student
	CString prodid = MyConnectionCW.GetIDofProdName(v_ccoursesregist);

	MyConnectionCW.UnenrollCourseOfStd(acc_numb, prodid);

	float UPrice_Unenroll = _ttof(UnitPriceProduct);

	// Money in online_account
	CString balance_str = MyConnectionCW.GetNumOnAccPrice(istidofE);
	float balance = _ttof(balance_str);

	// Balance new
	update_balance.Format(_T("%0.2f"), (balance + UPrice_Unenroll));

	MyConnectionCW.UpdateOABalance(acc_numb, update_balance);

	run_time = 0; // For only run Dropdown CUPcs once

	// Update List of Courses
	v_lcourses.SetRedraw(FALSE);
	v_lcourses.DeleteAllItems();
	v_lcourses.SetRedraw(TRUE);

	int j = 0;
	int nItem;
	CString v_name, v_availability, v_price;
	int ncourses = MyConnectionCW.GetNPrintsECourses(_T("Courses")); //- MyConnectionCW.NumbOfCID(istidofE);
	for (int i = 0; i < ncourses; i++) {
		// Name
		v_name = MyConnectionCW.GetCourses(i, _T("P.product_name"));
		// CString getname = MyConnectionCW.CheckStdISinC(j, istidofE);

		if (MyConnectionCW.CheckStdISinC(istidofE, v_name)) {
			nItem = v_lcourses.InsertItem(0, v_name);
			// Places available
			v_availability = MyConnectionCW.GetCourses(i, _T("(C.capacity - COUNT(pc.product_ID))"));
			v_lcourses.SetItemText(nItem, 1, v_availability);
			// Price
			v_price = MyConnectionCW.GetCourses(i, _T("P.price"));
			v_lcourses.SetItemText(nItem, 2, v_price);
		}
	}

	// Update the combo list after assigning a computer
	v_cbcoursesregist.ResetContent();
	if (run_time == 0) {
		CString v_listcoursesregist;
		MyConnectionCW.connect();
		int ncoursesregis = MyConnectionCW.NumbofCRegist(istidofE);
		for (int i = 0; i < ncoursesregis; i++) {
			v_listcoursesregist = MyConnectionCW.GetCoursesRegist(i, istidofE);
			v_cbcoursesregist.AddString(v_listcoursesregist);
		}
		UpdateData(FALSE);
		run_time++;
	}
	GetDlgItem(IDC_Bunenroll)->EnableWindow(FALSE);
	UpdateData(FALSE);
}


void CoursesW::OnBnClickedBback()
{
	OnOK();
}
