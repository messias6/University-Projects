
// MFCApp3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApp3App:
// See MFCApp3.cpp for the implementation of this class
//

class CMFCApp3App : public CWinApp
{
public:
	CMFCApp3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApp3App theApp;
extern CString EmailConnect;
extern CString ChosenPC;
extern CString istidofE;
extern CString istidSwithPC;
extern CString time_of_startTime;
extern CString date_of_startTime;
extern CString NameProduct;
extern CString UnitPriceProduct;
extern int QuantityChosen;
extern float TotalPrice;
extern CString AddToBalance;