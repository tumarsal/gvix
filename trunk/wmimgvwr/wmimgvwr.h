#if !defined(AFX_WMIMGVWR_H__765DFCF1_42A2_4D79_BBCB_F0E35DF36CA1__INCLUDED_)
#define AFX_WMIMGVWR_H__765DFCF1_42A2_4D79_BBCB_F0E35DF36CA1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWmimgvwrApp:
// See wmimgvwr.cpp for the implementation of this class
//

class CWmimgvwrApp : public CWinApp
{
public:
	CWmimgvwrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWmimgvwrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWmimgvwrApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMIMGVWR_H__765DFCF1_42A2_4D79_BBCB_F0E35DF36CA1__INCLUDED_)
