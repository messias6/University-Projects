// AddProducts.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "AddProducts.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <cmath>
#include <iostream>
#include <cfloat>
#include <cctype>
#include <string>
#include <exception>

// AddProducts dialog

IMPLEMENT_DYNAMIC(AddProducts, CDialog)

AddProducts::AddProducts(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AddProducts, pParent)
	, v_prodName(_T(""))
	, v_unitprice(_T(""))
	, v_printcourse(_T(""))
{

}

AddProducts::~AddProducts()
{
}

void AddProducts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PName, v_prodName);
	DDX_Text(pDX, IDC_unitPrice, v_unitprice);
	DDX_Control(pDX, IDC_CPrintCourse, v_cprintcourse);
	DDX_CBString(pDX, IDC_CPrintCourse, v_printcourse);
}


BEGIN_MESSAGE_MAP(AddProducts, CDialog)
	ON_BN_CLICKED(IDC_Bback, &AddProducts::OnBnClickedBback)
	ON_BN_CLICKED(IDC_BAddProduct, &AddProducts::OnBnClickedBaddproduct)
	ON_CBN_DROPDOWN(IDC_CPrintCourse, &AddProducts::OnCbnDropdownCprintcourse)
	ON_CBN_SELCHANGE(IDC_CPrintCourse, &AddProducts::OnCbnSelchangeCprintcourse)
END_MESSAGE_MAP()



myconnectorclassDB MyConnectionAP;

// Button Back
void AddProducts::OnBnClickedBback()
{
	OnOK();
}


// COMBO BOX
void AddProducts::OnCbnDropdownCprintcourse()
{
	if (run_time == 0) {
		v_cprintcourse.AddString(_T("Prints"));
		v_cprintcourse.AddString(_T("Courses"));
	}
	UpdateData(FALSE);
	run_time++;
	
}


void AddProducts::OnCbnSelchangeCprintcourse()
{
	// Gets the value and saves it in v_ccoursesregist
	v_cprintcourse.GetLBText(v_cprintcourse.GetCurSel(), v_printcourse);
	UpdateData(FALSE);
	if (v_printcourse[0] == '\0') {
		// Nothing was selected
	}
	else {
		// To enable the button to unenroll but only after selecting a course
		GetDlgItem(IDC_BAddProduct)->EnableWindow(TRUE);
	}
}


// Button - ADD PRODUCT
void AddProducts::OnBnClickedBaddproduct()
{
	UpdateData(TRUE);
	MyConnectionAP.connect();
	CString pName = v_prodName;
	CString pUnitPrice = v_unitprice;
	

	CString ss;
	float ff;
	GetDlgItemText(IDC_unitPrice, ss);
	LPCTSTR lpszString = ss;
	TCHAR *endptr;
	ff = (float)_tcstod(lpszString, &endptr);

	// If unitPrice is int or float
	if (endptr != lpszString && *endptr == '\0') {

		if (MessageBox(_T("Are you sure you want to proceed?"), _T(""), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {

			// Add 1
			int NewIDD = MyConnectionAP.NumbofProducts() + 1;

			// Converts ID to string
			CString NewID;
			NewID.Format(_T("%d"), (NewIDD));

			MyConnectionAP.NewProduct(NewID, pName, pUnitPrice); // Insert New Product into Product Table

			if (v_printcourse == _T("Prints")) {
				// If Prints was chosen in the combo box
				MyConnectionAP.NewPrints(NewID);
				GetDlgItem(IDC_BAddProduct)->EnableWindow(FALSE);
			}
			else {
				// If courses was chosen in the combo box
				// Capacity is always equal for this case
				MyConnectionAP.NewCourses(NewID);
				GetDlgItem(IDC_BAddProduct)->EnableWindow(FALSE);
			}

			OnOK();
			UpdateData(FALSE);
		}
	}	
	// When it's not a number - int or float
	else {
		
		MessageBox(_T("Please insert a number!!"), _T("Error"), MB_ICONERROR);
	}	
	
}
