// Test2.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp3.h"
#include "Test2.h"
#include "afxdialogex.h"


// Test2 dialog

IMPLEMENT_DYNAMIC(Test2, CDialog)

Test2::Test2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Test2, pParent)
{

}

Test2::~Test2()
{
}

void Test2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Test2, CDialog)
END_MESSAGE_MAP()


// Test2 message handlers
