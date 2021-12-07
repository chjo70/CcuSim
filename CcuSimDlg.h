// CcuSimDlg.h : header file
//

#if !defined(AFX_CCUSIMDLG_H__D9652AD1_9B93_4AA2_B6CC_CC2A1C463123__INCLUDED_)
#define AFX_CCUSIMDLG_H__D9652AD1_9B93_4AA2_B6CC_CC2A1C463123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "myTcpip.h"
#include "./EditLog/EditLog.h"
#include "./EditLog/editlog_stream.h"

#include "List/reportctrl.h"

#include "./BSP/hw_def.h"
#include "./BSP/hw_str.h"

#include "./INC/_pdw.h"
#include "./INC/_aetipl.h"
#include "./INC/_system.h"
#include "./INC/_sysmsg.h"

#include "CIdAet.h"

#include "CnfSys.h"

#define DivideBy2( A, B )				( ( (A) + (B) + 1 ) / 2 )
#define _DIV( A, B )            (UINT) ( (float) (A) / (float) (B) )
#define UDIV( A, B )            (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define NDIV( A, B )            (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define F_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) - 0.5 )
#define C_NDIV( A, B )          (UINT) ( (float) (A) / (float) (B) )
#define FDIV( A, B )            (float) ( (float) (A) / (float) (B) )
#define F_UDIV( A, B )          (UINT) ( (float) (A) / (float) (B) )
#define C_UDIV( A, B )					(UINT) ( (float) (A) / (float) (B) + 0.9 )
#define IDIV( A, B )						( ( (A) > 0 ) ? UDIV(A,B) : NDIV(A,B) )
#define L_IDIV( A, B )					( ( (A) > 0 ) ? F_UDIV(A,B) : F_NDIV(A,B) )
#define H_IDIV( A, B )					( ( (A) > 0 ) ? C_UDIV(A,B) : C_NDIV(A,B) )
#define UADD( A, B )            (UINT) ( (float) (A) + (float) (B) + 0.5 )
#define FADD( A, B )            (float) ( (float) (A) + (float) (B) )
#define FMUL( A, B )            ( (float) (A) * (float) (B) )
#define UMUL( A, B )            (UINT) ( ( (float) (A) * (float) (B) ) + 0.5 )
#define F_MUL( A, B )           (UINT) ( ( (float) (A) * (float) (B) ) )
#define C_MUL( A, B )						(UINT) ( ( (float) (A) * (float) (B) ) + 0.9 )
#define	WeightedVal( A,B,C,D) 	UDIV( (A*C) + (B*D), C+D)
#define	WeightedAdvVal(A,B,C) 	UDIV( FADD(FMUL( A, B ), C), FADD( 1, A ) )
#define ThreeOverTen( A )       ( UINT ) ( ( ( ( A ) * 3 ) + 5 ) / 10 )
#define HalfThreeOverTen( A )   ( UINT ) ( ( ( ( A ) * 3 ) + 10 ) / 20 )
#define _max(a,b)               ( ( (int)(a) > (int)(b) ) ? (a) : (b) )
#define _min(a,b)               ( ( (int)(a) < (int)(b) ) ? (a) : (b) )
#define _diffabs(a, b)					( (a) > (b) ? (a)-(b) : (b)-(a) )
#define _abs(a)									( (int) (a) >= 0 ? (a) : -(a) )
#define	High( A )								( (int) A >> 8 ) & 0x00ff
#define	Low( A )								( A & 0x00ff )

#define AMPCNV( A )							(int) ( UMUL( A, _spAMPres) + _spPAoffset )
#define FRQCNV( A, B )					(UINT) ( UMUL( (B), gFreqRes[(A)].res ) + gFreqRes[(A)].min )
#define F_FRQCNV( A, B )				(UINT) ( F_MUL( (B), gFreqRes[(A)].res ) + gFreqRes[(A)].min )
#define C_FRQCNV( A, B )				(UINT) ( C_MUL( (B), gFreqRes[(A)].res ) + gFreqRes[(A)].min )
#define	AOACNV( A )							UMUL( (A), _spAOAres )
#define	F_AOACNV( A )						F_MUL( (A), _spAOAres )
#define	C_AOACNV( A )						C_MUL( (A), _spAOAres )
#define	PWCNV( A )							UMUL( (A), _spPWres )
#define	F_PWCNV( A )						F_MUL( (A), _spPWres )
#define	C_PWCNV( A )						C_MUL( (A), _spPWres )
#define	PACNV( A )							( UMUL( (A), _spAMPres ) - 70 )
#define	F_PACNV( A )						( F_MUL( (A), _spAMPres ) - 70 )
#define	C_PACNV( A )						( C_MUL( (A), _spAMPres ) - 70 )
#define	FAOACNV( A )						(float) ( (float) A * _spAOAres )
#define	FPWCNV( A )							(float) ( (float) A * _spPWres )
#define	FPACNV( A )							(float) ( ( (float) A * _spAMPres ) - 70. )
#define FFRQCNV( A, B )					(float) ( ( (float) B * gFreqRes[A].res) + gFreqRes[A].min )

#define _spBand1		1
#define _spBand2		2
#define _spBand3		3
#define _spBdAll		4
#define _spBand4		5	// SIO's port4 

#define		IPL_VERSION		0x19991010

#define		MAX_AET_LIST	(256)

typedef struct {
	int index;
	char *buffer;
} STR_LAN_BUFFER ;

typedef struct {			// frequency band code를 위한 구조체 
	UINT min;				// min frequency
  UINT max;				// max frequency
  float res;		// 각 구간에 따른 resolution

} FREQ_RESOL ;

/////////////////////////////////////////////////////////////////////////////
// CCcuSimDlg dialog

class CCcuSimDlg : public CDialog, public CMyTcpIp
{
// 변수 정의
protected:
	BOOL m_bAudioEnable;

	UINT m_CoRecvSbit;

	BOOL m_bStartSbit;
	int m_noEMT;

	int m_nTotalAet;
	int m_nRowAetList[256];
	STR_LAN_BUFFER m_buffer;

	CCIdAet	m_id;
	
	/*! 랜 메시지 변수 */
	STR_LAN_MSG m_lanmsg;

	CBitmap m_bmpLampGreenBigOn;
	CBitmap m_bmpLampBigOff;

	CEditLog m_EditLogger;

	CCnfSys theCnfSys;

	// ANSI and UNICODE stream buffers for the EditLogger
	std::editstreambuf	m_EditStrBuf;
	std::weditstreambuf m_EditStrBufW;

	// Used to save the previos values for cout and wcout
	std::basic_streambuf<char>*	m_pOldBuf;
	std::basic_streambuf<wchar_t>* m_pOldBufW;
	
// Construction
public:
	void AudioEnable( BOOL bSwitch );
	BOOL IsExistEmitter( int noEMT );
	void LostAetList( STR_AET *pAet, int row );
	void UpdateAetList( STR_AET *pAet, int row );
	void DeleteAetInfo(STR_LAN_MSG *pLanMsg);
	void LostAetInfo(STR_LAN_MSG *pLanMsg);
	void UpdateAetInfo( STR_LAN_MSG *pLanMsg);
	void InsertAetInfo( STR_LAN_MSG *pLanMsg );
	void DISP_LanMsg(STR_LAN_MSG *pLanMsg, int mode, int rsBsize);
	int ParsingMessage();
	int LogOutput( char *format, ... );
	void DisConnectMessaage();
	void ConnectMessage( sockaddr_in *pSockaddrInternet );
	void ReceiveMessage( char *pBuff, int length );
	void LanConnectionSwitch( BOOL bStatus );
	CCcuSimDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCcuSimDlg)
	enum { IDD = IDD_CCUSIM_DIALOG };
	CEdit	m_CEditNoEmitter;
	//CReportCtrl	m_CListEsm;
	CEdit	m_CEditLog;
	CStatic	m_CStaticLampLANConnection;
	int		m_RadioAudioEnable;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCcuSimDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCcuSimDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonIBit();
	afx_msg void OnButtonESMode();
	afx_msg void OnButtonEWMode();
	afx_msg void OnButtonReadyMode();
	afx_msg void OnButtonSBit();
	afx_msg void OnButtonURBit();
	afx_msg void OnButtonCBit();
	virtual void OnOK();
	afx_msg void OnButtonIPLVersion();
	afx_msg void OnDestroy();
	afx_msg void OnButtonLogClear();
	afx_msg void OnButtonThreshold();
	afx_msg void OnButtonIPLDownload();
	afx_msg void OnButtonReqScan();
	afx_msg void OnButtonSysStart();
	afx_msg void OnButtonSbitStop();
	afx_msg void OnItemclickListEsm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListEsm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListEsm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonAudioEnable();
	afx_msg void OnButtonReqCnSsys();
	afx_msg void OnButtonSetCnfSys();
	afx_msg void OnButtonAudioRange();
	afx_msg void OnRadioAudioEnable();
	afx_msg void OnButtonSetAllCnfSys();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCUSIMDLG_H__D9652AD1_9B93_4AA2_B6CC_CC2A1C463123__INCLUDED_)
