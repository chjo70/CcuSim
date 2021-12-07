///////////////////////////////////////////////////////////////////////////////
// ReportCtrl.h
//
// CReportCtrl, a CListCtrl derived class that is specialized on "Report View"
// style. 
//
// Features:
//
// 1, Item sorting by clicking on column header.
// 2, Sub-item text edit.
// 3, Item repositioning.
// 4, Customizing checkbox styles, including "single" and "disabled".
// 5, Sending a message to parent window when user clicks on a checkbox.
// 6, Convenient item insertion, deletion, moving, and sub-item text changing.
// 7, Sub-item images and color
// 8, And much more... 
//
// This code may be used in compiled form in any way you desire. This file may be
// redistributed unmodified by any means PROVIDING it is not sold for profit without
// the authors written consent, and providing that this notice and the authors name 
// is included. If the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file .
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Written by Bin Liu (abinn32@yahoo.com)
//
// History
//
// Nov. 26, 2003 - Initial release.
// Dec. 03, 2003 - Fixed a bug in "EndEdit" where item text were not preperly committed.
//                 Completed the implementation of the "Sort-Separator" feature.
// Jan. 01, 2004 - Fixed a bug in "SetItemData".
//               - Added message "WM_EDIT_COMMITTED" which is sent to the parent window
//                 when an item text editing is committed.
//               - Fixed a bug in "SetItemText"(double type).
//               - Fixed a bug where item sorting does not work properly when there
//                 are multiple CReportCtrl objects on same window.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __REPORTCTRL_H__
#define __REPORTCTRL_H__

#include "ToolTipCtrlTrack.h"

// Sent to parent window when user clicked on the checkbox of an item:
// wParam: The item index in the list ctrl
// lParam: The mouse event type(WM_LBUTTONDOWN, WM_RBUTTONDOWN, etc) which generated this event. 
// Note: This message is not sent when the checkbox states were altered programmatically
//       by calling "SetItem", it is only sent when the user "physically" clicked the
//       checkbox using mouse or joystick etc.
#define WM_ON_CHKBOX	(WM_APP + 10000)

// Sent to parent window when a column of items were sorted
// wParam: The column index
// lParam: The sort method, either 0(descending) or 1(ascending)
#define WM_ITEM_SORTED	(WM_APP + 10001)

// Sent to parent window when an item text editing was committed
// wParam: The item index
// lParam: The column index
#define WM_EDIT_COMMITTED	(WM_APP + 10002)

// Checkbox styles.
#define RC_CHKBOX_NONE			0 // No checkbox displayed
#define	RC_CHKBOX_NORMAL		1 // Normal, multiple check allowed
#define	RC_CHKBOX_SINGLE		2 // Single check only
#define	RC_CHKBOX_DISABLED		3 // Disabled, cannot be checked/unchecked by user input,
								  // but can be by your code.

// Item state flags for selection, deletion, etc.
// Multiple flags can be combined together using the bit-or operator.
// Note: If RC_ITEM_ALL is set, all other flags are ignored
#define RC_ITEM_NONE		0x0000 // Void, indicates invalid items only
#define	RC_ITEM_ALL			0x0001 // All items regardless of states
#define	RC_ITEM_SELECTED	0x0002 // Selected items
#define	RC_ITEM_UNSELECTED	0x0004 // Unselected items
#define	RC_ITEM_CHECKED		0x0008 // Checked items
#define	RC_ITEM_UNCHECKED	0x0010 // Unchecked items
#define	RC_ITEM_FOCUSED		0x0020 // Focused item
#define	RC_ITEM_UNFOCUSED	0x0040 // Unfocused items

// Item inverting types
#define RC_INVERT_SELECTION	0 // Invert item selection
#define RC_INVERT_CHECKMARK	1 // Invert item check mark

// Removes any custom color from item text and item backgroun
#define COLOR_INVALID	0xffffffff

//////////////////////////////////////////////////////////////////////////
// The CReportCtrl Class Definition
//////////////////////////////////////////////////////////////////////////

//##ModelId=43D4818002E6
class CReportCtrl : public CListCtrl
{
public:		

	//////////////////////////////////////////////////////////////////////
	//		Constructor & Destructor
	//////////////////////////////////////////////////////////////////////
	//##ModelId=43D481800304
	CReportCtrl();
	//##ModelId=43D48180039B
	virtual ~CReportCtrl();

	//////////////////////////////////////////////////////////////////////
	//		Run-time Creation
	//////////////////////////////////////////////////////////////////////
	//##ModelId=43D481810049
	virtual BOOL Create(CWnd* pParentWnd, UINT nID, LPCRECT lpRect = NULL, DWORD dwStyle = WS_BORDER | WS_TABSTOP);

	///////////////////////////////////////////////////////////////////////
	//		Column Header attributes
	///////////////////////////////////////////////////////////////////////
	
	//##ModelId=43D48181008F
	BOOL SetColumnHeader(const CString& strHeadings); // Set columns and their formats.
	//##ModelId=43D481810111
	int GetColumnCount() const; // Get the column count.
	//##ModelId=43D481810175
	BOOL DeleteAllColumns();
	//##ModelId=43D4818101BB
	CString GetHeaderText(int nColumn) const;
	//##ModelId=43D4818101D9
	BOOL SetHeaderText(int nColumn, LPCTSTR lpText);	
	//##ModelId=43D4818101ED
	BOOL HasColumnHeader() const; // FALSE if the list control has LVS_NOCOLUMNHEADER flag
	//##ModelId=43D48181021F
	const CHeaderCtrl* GetHeaderCtrl() const;

	///////////////////////////////////////////////////////////////////////
	//		Images & Color
	///////////////////////////////////////////////////////////////////////
	
	// Column header images
	//##ModelId=43D481810234
	BOOL SetHeaderImage(int nColumn, int nImageIndex, BOOL bLeftSide = TRUE);
	//##ModelId=43D48181025C
	int GetHeaderImage(int nColumn) const;
	//##ModelId=43D481810284
	CImageList* SetHeaderImageList(UINT nBitmapID, COLORREF crMask = RGB(255, 0, 255));
	//##ModelId=43D4818102A2
	CImageList* SetHeaderImageList(CImageList* pImageList);
	
	// Sub-item images
	//##ModelId=43D4818102C0
	BOOL SetItemImage(int nItem, int nSubItem, int nImageIndex);
	//##ModelId=43D4818102FC
	int GetItemImage(int nItem, int nSubItem) const;
	//##ModelId=43D48181032E
	CImageList* SetImageList(UINT nBitmapID, COLORREF crMask = RGB(255, 0, 255));
	//##ModelId=43D481810356
	CImageList* SetImageList(CImageList* pImageList);
	//##ModelId=43D48181037E
	CImageList* GetImageList() const;

	// Sub-item Text & Background Color
	//##ModelId=43D4818103A6
	void SetItemTextColor(int nItem = -1, int nSubItem = -1, COLORREF color = COLOR_INVALID, BOOL bRedraw = TRUE);
	//##ModelId=43D4818103C4
	COLORREF GetItemTextColor(int nItem, int nSubItem) const;
	//##ModelId=43D4818103D8
	void SetItemBkColor(int nItem = -1, int nSubItem = -1, COLORREF color = COLOR_INVALID, BOOL bRedraw = TRUE);
	//##ModelId=43D48182000E
	COLORREF GetItemBkColor(int nItem, int nSubItem) const;

	//////////////////////////////////////////////////////////////////////
	//		Control Styles & Attributes
	//////////////////////////////////////////////////////////////////////
	
	//##ModelId=43D481820022
	void ResizeToFitParent(); // Resize the list control to occupy parent's client area
	//##ModelId=43D48182004A
	void SetGridLines(BOOL bSet = TRUE); // Show grid lines.
	//##ModelId=43D4818200AE
	void SetCheckboxeStyle(int nStyle = RC_CHKBOX_NORMAL); // Set checkbox styles.	
	//##ModelId=43D481820109
	int GetCheckboxStyle() const;	
	//##ModelId=43D481820145
	BOOL IsSortable() const; // Is sort allowed?
	//##ModelId=43D481820177
	BOOL SetSortable(BOOL bSet); // Allow/disallow sorting
	//##ModelId=43D4818201B3
	BOOL IsEditable() const; // Is Item text editable?
	//##ModelId=43D4818201F9
	void SetEditable(BOOL bSet = TRUE); // Allow item text editting
	
	///////////////////////////////////////////////////////////////////////
	//		Item attributes & operations
	///////////////////////////////////////////////////////////////////////	

	// Item states operation
	//##ModelId=43D48182023F
	int GetFirstItem(DWORD dwStates = RC_ITEM_ALL, int nStartAfter = -1) const;
	//##ModelId=43D48182025D
	int GetLastItem(DWORD dwStates = RC_ITEM_ALL, int nStartBefore = -1) const;
	//##ModelId=43D48182027B
	int GetItemCount(DWORD dwStates = RC_ITEM_ALL) const;	
	//##ModelId=43D4818202A3
	DWORD GetItemStates(int nItem) const;
	//##ModelId=43D4818202C1
	BOOL ExamItemStates(int nItem, DWORD dwStates) const;
	//##ModelId=43D4818202DF
	BOOL SetItemStates(int nItem, DWORD dwNewStates);
	//##ModelId=43D4818202FD
	int SetAllItemStates(DWORD dwOldStates, DWORD dwNewStates);
	//##ModelId=43D48182031B
	void InvertItems(int nType); // RC_INVERT_SELECTION or RC_INVERT_CHECKMARK

	// Item Insertion & Deletion	
	//##ModelId=43D481820339
	int InsertItemEx(int nItem, LPCTSTR lpText, ...); 	
	//##ModelId=43D481820389
	BOOL DeleteItem(int nItem, BOOL bSelectNextItem = FALSE); // Delete an item.
	//##ModelId=43D481830024
	int DeleteAllItems(DWORD dwStates = RC_ITEM_ALL); // Delete all qualified items.

	// Item positioning	
	//##ModelId=43D481830092
	int MoveUp(int nItem, int nCount = 1); // Move an item upwards by "nCount" positions.
	//##ModelId=43D4818300EC
	int MoveDown(int nItem, int nCount = 1); // Move an item downwards by "nCount" positions.
	//##ModelId=43D481830146
	int MoveToTop(int nItem); // Move an item up to the top.
	//##ModelId=43D481830196
	int MoveToBottom(int nItem); // Move an item down to the bottom.
	//##ModelId=43D4818301DC
	int MoveTo(int nItem, int nNewPosition); // Move an item to a particular position 
	//##ModelId=43D481830240
	BOOL SwapItems(int nItem1, int nItem2);	// Swap two items in the list, including all attributes.

	// Convenient versions of "CListCtrl::SetItemText"	
	//##ModelId=43D48183029B
	BOOL SetItemText(int nItem, int nSubItem, INT val);
	//##ModelId=43D4818302F5
	BOOL SetItemText(int nItem, int nSubItem, UINT val);
	//##ModelId=43D48183034F
	BOOL SetItemText(int nItem, int nSubItem, LONG val);
	//##ModelId=43D48183039F
	BOOL SetItemText(int nItem, int nSubItem, ULONG val);
	//##ModelId=43D481840007
	BOOL SetItemText(int nItem, int nSubItem, TCHAR val);
	//##ModelId=43D481840061
	BOOL SetItemText(int nItem, int nSubItem, DOUBLE val, int nPrecision = -1);
	//##ModelId=43D4818400BB
	BOOL SetItemText(int nItem, int nSubItem, const COleDateTime& dateTime, DWORD dwFlags = 0);

	// Sorting	
	//##ModelId=43D481840115
	BOOL IsSortAscending() const;
	//##ModelId=43D481840129
	int GetSortedColumn() const;
	//##ModelId=43D481840147
	void SortItems(int nColumn, BOOL bAscending); // Sort a specified column.
	//##ModelId=43D4818401B6
	void SetSortSeparator(LPCTSTR lpSortSeparator = NULL); // Sort-separator, NULL=disabled
	//##ModelId=43D4818401FC
	LPCTSTR GetSortSeparator() const;

	// Item text edit	
	//##ModelId=43D481840242
	BOOL StartEdit(int nItem, int nSubItem); // Display the editbox, previous edit are committed
	//##ModelId=43D48184026A
	BOOL EndEdit(BOOL bCommit = TRUE); // Commit/cancel text edit, hide the editbox
	//##ModelId=43D481840288
	CEdit* GetEditControl();	

	///////////////////////////////////////////////////////////////////////
	//		Necessary overloading but Irrelevant to Users
	///////////////////////////////////////////////////////////////////////
	
	//##ModelId=43D4818402BA
	int InsertColumn(int nCol, LPCTSTR lpColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	//##ModelId=43D481840332
	int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	//##ModelId=43D481840396
	BOOL DeleteColumn(int nCol);
	//##ModelId=43D481850012
	BOOL SetCheck(int nItem, BOOL bCheck = TRUE); // overloaded to guard the "single" checkbox style
	//##ModelId=43D481850027
	BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
	//##ModelId=43D481850059
	BOOL SetItem(const LVITEM* pItem);
	//##ModelId=43D481850063
	BOOL GetItem(LVITEM* pItem) const;
	//##ModelId=43D481850077
	DWORD GetItemData(int nItem) const;
	//##ModelId=43D481850081
	BOOL SetItemData(int nItem, DWORD dwData);
	//##ModelId=43D481850095
	DWORD SetExtendedStyle(DWORD dwNewStyle);
	//##ModelId=43D4818500D1
	BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	//##ModelId=43D4818500F9
	BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	//##ModelId=43D481850135
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam);
	//##ModelId=43D4818501AD
	int InsertItem(int nItem, LPCTSTR lpItem, int nImage);
	//##ModelId=43D48185021B
	int InsertItem(const LVITEM* pItem);
	//##ModelId=43D48185027F
	int InsertItem(int nIndex, LPCTSTR lpText);
	//##ModelId=43D4818502EE
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpText);

	// 이전에 선택한 행을 알기 위한 함수
	//##ModelId=43D481850366
	inline int GetSelectedRow() { return m_SelectedRow; }
protected:	
	
	// Helper functions for internal use
	//##ModelId=43D481850370
	BOOL _IsValidIndex(int nIndex) const;
	//##ModelId=43D48186000A
	BOOL _ItemCheckMonitor(int nIndex, BOOL bBefore, BOOL bAfter, UINT nMsg);
	//##ModelId=43D48186005A
	BOOL _IsEditVisible() const;
	//##ModelId=43D481860096
	void _MouseClkMonitor(UINT nMsg, UINT nFlags, CPoint point, BOOL bTriggerEdit);
	//##ModelId=43D4818600D2
	static void _StringSplit(const CString &str, CStringArray& arr, TCHAR chDelimitior);
	//##ModelId=43D481860118
	void _UnsetSortedColumn();
	//##ModelId=43D48186012C
	BOOL _SetItemStatesNoVerify(int nItem, DWORD dwNewStates);
	//##ModelId=43D48186014A
	void _EnsureSingleCheck(int nItem);
	//##ModelId=43D48186015E
	DWORD _GetHeaderTextFormat(int nColumn) const;
	//##ModelId=43D481860186
	void _UpdateColumn(int nColumn, BOOL bInsert);
	//##ModelId=43D48186019A
	void _AllocItemMemory(int nItem);
	//##ModelId=43D4818601AF
	void _FreeItemMemory(int nItem);
	//##ModelId=43D4818601B9
	BOOL _PartialSort(int nStart, int nEnd);
	//##ModelId=43D4818601CE
	int _FindSeparator(int nStartAfter, int nColumn) const;
	//##ModelId=43D4818601E1
	void _QuickSortRecursive(int* pArr, int nLow, int nHigh);
	//##ModelId=43D4818601F6
	int _CompareItems(int nItem1, int nItem2);

	// Member data	
	//##ModelId=43D48186020A
	CEdit* m_pWndEdit; // Edit control, for subitem edit
	//##ModelId=43D48186021D
	LPTSTR m_pszSeparator; // Sort separator
	//##ModelId=43D481860227
	BOOL m_bAllowEdit; // Is subitem edit allowed?
	//##ModelId=43D48186023C
	POINT m_ptEditting; // Position of the subitem that is currently being edited
	//##ModelId=43D48186024F
	int m_nChkStyle; // Checkbox style
	//##ModelId=43D481860263
	DWORD m_dwPrevEditFmt; // Format of previously edited subitem
	//##ModelId=43D48186026E
	CImageList m_imgList; // Image list for items
	//##ModelId=43D481860282
	CImageList m_headerImgList; // Image list for the header control
	//##ModelId=43D481860295
	int m_nSortCol; // The sorted column, -1 if none
	//##ModelId=43D4818602A9
	BOOL m_bSortAscending; // Is sort ascending?
	//##ModelId=43D4818602BD
	int m_SelectedRow;

	//##ModelId=43D4818602D2
	CToolTipCtrlTrack *m_pTextTip;

	//////////////////////////////////////////////////////////////////////
	// Wizard Generated Stuff
	//////////////////////////////////////////////////////////////////////

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrl)
	public:
	//##ModelId=43D4818602DB
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//##ModelId=43D481860321
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//##ModelId=43D48186035D
	virtual void PreSubclassWindow();
	//##ModelId=43D48186038F
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//##ModelId=43D481870047
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions

protected:	

	//{{AFX_MSG(CReportCtrl)
	//##ModelId=43D4818700DE
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//##ModelId=43D48187017E
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//##ModelId=43D481870214
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=43D481880017
	afx_msg void OnDestroy();
	//##ModelId=43D4818802E8
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//##ModelId=43D481890004
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//##ModelId=43D4818900C2
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	//##ModelId=43D4818901DB
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//##ModelId=43D48189028F
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//##ModelId=43D481890325
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// End of CReportCtrl Class Definition
//////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __REPORTCTRL_H__
