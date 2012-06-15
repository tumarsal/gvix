// ***
//  
//  CWmimgvwrApp: Application itself 
//
//
// ***

#include "stdafx.h"
#include "wmimgvwr.h"
#include "wmimgvwrDlg.h"

#include "gdal.h"
#include "gdal_alg.h"
#include "ogr_srs_api.h"
#include "cpl_string.h"
#include "cpl_conv.h"
#include "cpl_multiproc.h"

#include "gdal_priv.h"

#include "ogrsf_frmts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWmimgvwrApp

BEGIN_MESSAGE_MAP(CWmimgvwrApp, CWinApp)
	//{{AFX_MSG_MAP(CWmimgvwrApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWmimgvwrApp construction

CWmimgvwrApp::CWmimgvwrApp()
	: CWinApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWmimgvwrApp object

CWmimgvwrApp vg_ceImgVwr;

/////////////////////////////////////////////////////////////////////////////
// CWmimgvwrApp initialization

BOOL CWmimgvwrApp::InitInstance()
{
   RECT tbRect;
   HWND hTaskBar = NULL;
	CWmimgvwrDlg *lpDlg = new CWmimgvwrDlg();

   hTaskBar = ::FindWindow( L"HHTaskBar", L"" );
   if ( hTaskBar )
   {
      if ( ::GetWindowRect(hTaskBar, &tbRect) )
         vg_wintask_h = tbRect.bottom; 
   }

   vg_cmd_line = AfxGetApp()->m_lpCmdLine;

	m_pMainWnd = lpDlg;

	lpDlg->DoModal();

	return FALSE;
}
