#if !defined(AFX_TOOLTIPCTRLTRACK_H__03FA8E28_7856_4E1E_B846_619094164050__INCLUDED_)
#define AFX_TOOLTIPCTRLTRACK_H__03FA8E28_7856_4E1E_B846_619094164050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTipCtrlTrack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolTipCtrlTrack window

//##ModelId=43D481800029
class CToolTipCtrlTrack : public CToolTipCtrl
{
// Construction
public:
	//##ModelId=43D48180003D
	CToolTipCtrlTrack();

// Attributes
public:
protected:
	//##ModelId=43D481800048
	TOOLINFO m_ti;
	//##ModelId=43D481800052
	CWnd *m_pWnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipCtrlTrack)
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=43D481800065
	void SetTrackToolTip(LPCTSTR pszText, int x, int y);
	//##ModelId=43D481800079
	BOOL InitToolTip(CWnd *pWnd, LPCTSTR pszText);
	//##ModelId=43D48180008D
	virtual ~CToolTipCtrlTrack();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipCtrlTrack)
	//##ModelId=43D48180008F
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPCTRLTRACK_H__03FA8E28_7856_4E1E_B846_619094164050__INCLUDED_)
