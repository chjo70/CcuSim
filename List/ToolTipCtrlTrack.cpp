// ToolTipCtrlTrack.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTipCtrlTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipCtrlTrack

//##ModelId=43D48180003D
CToolTipCtrlTrack::CToolTipCtrlTrack()
{
}

//##ModelId=43D48180008D
CToolTipCtrlTrack::~CToolTipCtrlTrack()
{
}


BEGIN_MESSAGE_MAP(CToolTipCtrlTrack, CToolTipCtrl)
	//{{AFX_MSG_MAP(CToolTipCtrlTrack)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipCtrlTrack message handlers

//##ModelId=43D48180008F
int CToolTipCtrlTrack::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolTipCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CToolTipCtrlTrack::InitToolTip
// 반환되는 형  : BOOL
// 함 수 인 자  : CWnd *pWnd
// 함 수 인 자  : LPCTSTR pszText
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2004-09-07 17:50:22
//
//##ModelId=43D481800079
BOOL CToolTipCtrlTrack::InitToolTip(CWnd *pWnd, LPCTSTR pszText)
{

	m_pWnd = pWnd;

	// GetToolInfo( m_ti, pWnd );

	m_ti.cbSize = sizeof( TOOLINFO );
	m_ti.uFlags = TTF_IDISHWND| TTF_TRACK |TTF_ABSOLUTE | TTF_SUBCLASS;
  m_ti.hwnd = pWnd->GetSafeHwnd();
  m_ti.uId = (WPARAM) pWnd->GetSafeHwnd();
  m_ti.hinst = AfxGetInstanceHandle();
  m_ti.lpszText = (LPTSTR) pszText;

	SetToolInfo( & m_ti );
	SetTipBkColor( RGB(255,0,0) );
	SetTipTextColor( RGB(255,255,255) );
	SetMaxTipWidth( 100 );
	AddTool( m_pWnd, "AAAAA" );

	Activate( FALSE );

	////delay time setting..
	SendMessage(TTM_SETDELAYTIME,(WPARAM)TTDT_INITIAL,MAKELONG(100,0));		
	
	//popup time setting..
	SendMessage(TTM_SETDELAYTIME,(WPARAM)TTDT_AUTOPOP,MAKELONG(5000,0));

	// SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE,(LPARAM)&m_ti );

  return (BOOL) SendMessage (TTM_ADDTOOL, 0, (LPARAM) &m_ti );

	return TRUE;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CToolTipCtrlTrack::SetTrackToolTip
// 반환되는 형  : void
// 함 수 인 자  : LPCTSTR pszText
// 함 수 인 자  : int x
// 함 수 인 자  : int y
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2004-09-14 11:06:21
//
//##ModelId=43D481800065
void CToolTipCtrlTrack::SetTrackToolTip( LPCTSTR pszText, int x, int y )
{

	m_ti.lpszText = (LPTSTR) pszText;

	SendMessage(TTM_UPDATETIPTEXT,0,(LPARAM)&m_ti);


	SendMessage( TTM_TRACKPOSITION, 0, (LPARAM)MAKELPARAM( x, y ));

	Activate( TRUE );
	SendMessage( TTM_TRACKACTIVATE,(WPARAM)TRUE,(LPARAM)&m_ti );

}
