// SetQuantity.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "SetQuantity.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "PrintsWindow.h"


// SetQuantity dialog

IMPLEMENT_DYNAMIC(SetQuantity, CDialog)

SetQuantity::SetQuantity(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SetQuantity, pParent)
	, v_productname(_T(""))
	, v_unitprice(_T(""))
	, v_desiredquantity(0)
{

}

SetQuantity::~SetQuantity()
{
}

void SetQuantity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_productName, v_productname);
	DDX_Text(pDX, IDC_unitPrice, v_unitprice);
	DDX_Text(pDX, IDC_desiredQtd, v_desiredquantity);
}


BEGIN_MESSAGE_MAP(SetQuantity, CDialog)
	ON_BN_CLICKED(IDC_BAdd, &SetQuantity::OnBnClickedBadd)
END_MESSAGE_MAP()


myconnectorclassDB MyConnectionSQ;


BOOL SetQuantity::OnInitDialog() {
	CDialog::OnInitDialog();
	MyConnectionSQ.connect();

	v_productname = NameProduct;
	v_unitprice = UnitPriceProduct;
	
	UpdateData(FALSE);
	return TRUE;
}

void SetQuantity::OnBnClickedBadd()
{
	UpdateData(TRUE);
	QuantityChosen = v_desiredquantity;
	UpdateData(FALSE);
	OnOK();	
}
