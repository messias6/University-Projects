// PrintsWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "PrintsWindow.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "SetQuantity.h"
//#include "TCHAR.h"
#include "Resource.h"

// PrintsWindow dialog

IMPLEMENT_DYNAMIC(PrintsWindow, CDialog)

PrintsWindow::PrintsWindow(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PrintsWindow, pParent)
	, v_totalprice(_T(""))
{

}

PrintsWindow::~PrintsWindow()
{
}

void PrintsWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LPrints, v_listprints);
	DDX_Control(pDX, IDC_LIST2, v_listprodTpay);
	DDX_Text(pDX, IDC_TotalPrice, v_totalprice);
}


BEGIN_MESSAGE_MAP(PrintsWindow, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LPrints, &PrintsWindow::OnNMDblclkLprints)
	ON_BN_CLICKED(IDC_BRemoveItem, &PrintsWindow::OnBnClickedBremoveitem)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &PrintsWindow::OnNMClickList2)
	ON_BN_CLICKED(IDC_BProcPay, &PrintsWindow::OnBnClickedBprocpay)
	ON_BN_CLICKED(IDC_Bback, &PrintsWindow::OnBnClickedBback)
END_MESSAGE_MAP()


myconnectorclassDB MyConnectionPW;

float RemovePrice = 0;

BOOL PrintsWindow::OnInitDialog()
{
	CDialog::OnInitDialog();
	MyConnectionPW.connect();
	// Creates list with all Products
	v_listprints.InsertColumn(0, L"Name", LVCFMT_LEFT, 150);           
	v_listprints.InsertColumn(1, L"Price", LVCFMT_LEFT, 40);
	v_listprints.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	int nItem;
	CString v_name, v_priceEcapacity;
	int npc = MyConnectionPW.GetNPrintsECourses(_T("Prints"));
	for (int i = 0; i < npc; i++) {
		v_name = MyConnectionPW.GetPrintsECourses(i, _T("product_name"));
		nItem = v_listprints.InsertItem(0, v_name);
		v_priceEcapacity = MyConnectionPW.GetPrintsECourses(i, _T("price"));
		v_listprints.SetItemText(nItem, 1, v_priceEcapacity);

	}

	// Basket to proceed to payment
	v_listprodTpay.InsertColumn(0, L"Name", LVCFMT_LEFT, 151);
	v_listprodTpay.InsertColumn(1, L"Final Cost", LVCFMT_LEFT, 60);
	v_listprodTpay.SetExtendedStyle(LVS_EX_FULLROWSELECT);


	UpdateData(FALSE);
	return TRUE;
}

void PrintsWindow::OnNMDblclkLprints(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	v_listprints.ScreenToClient(&point);

	int nIndex;
	if ((nIndex = v_listprints.HitTest(point)) != -1) {
	
		CString getvalue = v_listprints.GetItemText(nIndex, 0); //saves chosen value in getvalue
		NameProduct = getvalue; //Name of chosen product
		getvalue = v_listprints.GetItemText(nIndex, 1); 
		UnitPriceProduct = getvalue;  // Unit price of chosen product

		float UPrice = _ttof( UnitPriceProduct );

		SetQuantity SQ;
		SQ.DoModal();

		if (QuantityChosen == 0) {
			// If nothing is inserted in the field of quantity, nothing happens
		}
		else {
			
			float final_cost = UPrice * QuantityChosen;
			TotalPrice = TotalPrice + final_cost;
			
			CString str_final_cost;
			str_final_cost.Format(_T("%0.2f"), final_cost);

			int nItem;
			nItem = v_listprodTpay.InsertItem(0, NameProduct);
			v_listprodTpay.SetItemText(nItem, 1, str_final_cost);
			// Enable Button - Proceed to payment
			GetDlgItem(IDC_BProcPay)->EnableWindow(TRUE);
			
		}
	}

	CString str_final_cost1;
	str_final_cost1.Format(_T("%0.2f"), TotalPrice);

	v_totalprice = str_final_cost1;
	UpdateData(FALSE);
	
	*pResult = 0;
}

void PrintsWindow::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	v_listprodTpay.ScreenToClient(&point);

	int nIndex;
	if ((nIndex = v_listprodTpay.HitTest(point)) != -1) {
		// Enable button - Remove Item
		GetDlgItem(IDC_BRemoveItem)->EnableWindow(TRUE);
		CString getvalue = v_listprodTpay.GetItemText(nIndex, 1); // price of row
		RemovePrice = _ttof(getvalue);
	}
	*pResult = 0;
}

void PrintsWindow::OnBnClickedBremoveitem()
{
	UINT i, uSelectedCount = v_listprodTpay.GetSelectedCount();
	int  nItem;
	if (uSelectedCount > 0)
		for (i = 0; i < uSelectedCount; i++)
		{
			nItem = v_listprodTpay.GetNextItem(-1, LVNI_SELECTED);
			ASSERT(nItem != -1);
			v_listprodTpay.DeleteItem(nItem);
		}

	TotalPrice = TotalPrice - RemovePrice;

	CString str_final_cost1;
	str_final_cost1.Format(_T("%0.2f"), TotalPrice);

	v_totalprice = str_final_cost1;

	if (v_listprodTpay.GetItemCount() == 0) {
		// Disable Button - Proceed to payment
		GetDlgItem(IDC_BProcPay)->EnableWindow(FALSE);
	}

	// Disable button - Remove Item
	GetDlgItem(IDC_BRemoveItem)->EnableWindow(FALSE);
	UpdateData(FALSE);
}


void PrintsWindow::OnBnClickedBprocpay()
{
	MyConnectionPW.connect();
	CString balance_str = MyConnectionPW.GetNumOnAccPrice(istidofE);
	float balance = _ttof(balance_str);
	// MB_YESNO - two buttons appear in the systems language (windows 10) in my case portuguese
	if (MessageBox(_T("Are you sure you want to proceed?"), _T(""), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
		
		if ((balance - TotalPrice) < 0) {
			MessageBox(_T("You do not have enough money in your online account!"), _T("Error"), MB_ICONERROR);

		}
		else {
			CString NumOnAcc = MyConnectionPW.GetNumOnAcc(istidofE); // Account_number

			for (int i = 0; i < v_listprodTpay.GetItemCount(); i++) {
				CString Name = v_listprodTpay.GetItemText(i, 0);
				CString total_unit_price = v_listprodTpay.GetItemText(i, 1);

				CString product_ID;
				float total_unit_priceFloat = _ttof(total_unit_price);
				CString unit_price = MyConnectionPW.GetProdIDeUnitPrice(Name, product_ID);

				float unit_priceFloat = _ttof(unit_price);
				float quantity = total_unit_priceFloat / unit_priceFloat; // quantity

				CString quantity_str;
				quantity_str.Format(_T("%0.2f"), quantity);

				MyConnectionPW.AddPayPrints(NumOnAcc, product_ID, quantity_str);
				CString balance_new;
				balance_new.Format(_T("%0.2f"), (balance - TotalPrice));
				MyConnectionPW.UpdateOABalance(NumOnAcc, balance_new);


			}

			MessageBox(_T("You have made your purchase!\nThank you for buying with us!"), _T(""), MB_ICONINFORMATION);
			OnOK();
		}
	}
}


void PrintsWindow::OnBnClickedBback()
{
	OnOK();
}
