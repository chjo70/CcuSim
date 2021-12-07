// CcuSimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CcuSim.h"
#include "CcuSimDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

enum { LIST_STAT=0, LIST_NO=0, LIST_AOA, LIST_SIGTYPE, LIST_FREQ, LIST_PRI, LIST_LEVEL, LIST_PW, LIST_PA, LIST_SCAN, LIST_FIRST_SEEN, LIST_LAST_SEEN, LIST_ID, LIST_EMITTER_NAME, LIST_ETC } ;

FREQ_RESOL 			gFreqRes[4] = { {    0,     0, 0     } ,
			   												{    0,  2560, 0.625 } ,   /* LOW  FREQUENCY */
			        	        				{ 1280,  6400, 1.25  } ,   /* MID  FREQUENCY */
           		   	   	    			{ 5866, 18740, 1.5   } } ; /* HIGH FREQUENCY */

//////////////////////////////////////////////////////////////////////////
// 에미터 문자 정보 정의
const char aet_stat[16][9] =	{ "Normal", "PMOP", "Chirp_Up", "Chirp_Dn", "CW",
								"5","6","7","8","9","10","11","12","13","14", "Bit" } ;

const char aet_freq_bandcode[4][7] = { "Unkwn", "Band1", "Band2", "Band3" };

const char aet_signal_type[5][3]  = { "UK" , "NP" , "CW" , "DP" , "HP" };
const char aet_signal_type_ch[4]   = { 'U' , 'R' , 'C' , 'D' };

const char ipl_pulse_type[6][10]   = {	"Unkwn" ,
										"Reglr" ,
										"CW" ,
										"ChpUp" ,
										"ChpDn" ,
										"PMOP" };
													
const char aet_freq_type[8][3]  = { "UK" , "F_" , "RA" , "PA", "HP", "C+", "C-", "PM" };
char	   aet_freq_type_ch[8]   = { 'U' , 'F' , 'A' , 'T' , 'H', '+' , '-' , 'P' };

const char ipl_freq_type[7][16]  = { "Unknown" , "Fixed" , "Random Agile" , "Pattern Agile", "Chirp Up", "Chirp Down", "PMOP" };

const char aet_freq_ptype[4][15] = { "Unkwn" , "SineW" , "Saw+W" , "Saw+W" } ;
const char aet_freq_ptype_ch[5]  = { 'U', 'S', '+', '-', 'D' } ;
const char ipl_freq_ptype[4][15] = { "Unkwn" , "SineW" , "Saw-W" , "Saw+W" } ;

const char aet_pri_type[6][3]    = { "UK" , "ST" , "SG" , "JT" , "PT", "DW" } ;
const char aet_pri_ptype_ch[5]   = { 'U', 'S', '+', '-', 'D' } ;
char	   aet_asp_type_ch[7][3] = { "UK" , "CR" , "SC" , "TW" , "CO" , "ST" , "MA" } ;
char	   aet_pri_type_ch[5]    = { 'U' , 'S' , 'T' , 'J' , 'P' } ;

const char aet_pri_ptype[5][14]  = {	"Unkwn" ,
										"Sin-W" ,
										"Tri-W" ,
										"Saw-W" ,
										"D&S" } ;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCcuSimDlg dialog

CCcuSimDlg::CCcuSimDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCcuSimDlg::IDD, pParent), m_EditStrBuf( m_EditLogger ), m_EditStrBufW( m_EditLogger )
{
	//{{AFX_DATA_INIT(CCcuSimDlg)
	m_RadioAudioEnable = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCcuSimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCcuSimDlg)
	DDX_Control(pDX, IDC_EDIT_NOEMITTER, m_CEditNoEmitter);
	//DDX_Control(pDX, IDC_LIST_ESM, m_CListEsm);
	DDX_Control(pDX, IDC_EDIT_LOG, m_CEditLog);
	DDX_Control(pDX, IDC_STATIC_LAN_CONNECTION, m_CStaticLampLANConnection);
	DDX_Radio(pDX, IDC_RADIO_AUDIO_ENABLE, m_RadioAudioEnable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCcuSimDlg, CDialog)
	//{{AFX_MSG_MAP(CCcuSimDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_IBIT, OnButtonIBit)
	ON_BN_CLICKED(IDC_BUTTON_ESMODE, OnButtonESMode)
	ON_BN_CLICKED(IDC_BUTTON_EWMODE, OnButtonEWMode)
	ON_BN_CLICKED(IDC_BUTTON_READYMODE, OnButtonReadyMode)
	ON_BN_CLICKED(IDC_BUTTON_SBIT, OnButtonSBit)
	ON_BN_CLICKED(IDC_BUTTON_URBIT, OnButtonURBit)
	ON_BN_CLICKED(IDC_BUTTON_URBIT2, OnButtonCBit)
	ON_BN_CLICKED(IDC_BUTTON_IPLVERSION, OnButtonIPLVersion)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON__LOGCLEAR, OnButtonLogClear)
	ON_BN_CLICKED(IDC_BUTTON_THRESHOLD, OnButtonThreshold)
	ON_BN_CLICKED(IDC_BUTTON_IPLDOWNLOAD, OnButtonIPLDownload)
	ON_BN_CLICKED(IDC_BUTTON_REQSCAN, OnButtonReqScan)
	ON_BN_CLICKED(IDC_BUTTON_SYSSTART, OnButtonSysStart)
	ON_BN_CLICKED(IDC_BUTTON_SBIT_STOP, OnButtonSbitStop)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_ESM, OnItemclickListEsm)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ESM, OnColumnclickListEsm)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ESM, OnClickListEsm)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_ENABLE, OnButtonAudioEnable)
	ON_BN_CLICKED(IDC_BUTTON_REQCNFSYS, OnButtonReqCnSsys)
	ON_BN_CLICKED(IDC_BUTTON_SETCNFSYS, OnButtonSetCnfSys)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_RANGE, OnButtonAudioRange)
	ON_BN_CLICKED(IDC_RADIO_AUDIO_ENABLE, OnRadioAudioEnable)
	ON_BN_CLICKED(IDC_BUTTON_SETALLCNFSYS, OnButtonSetAllCnfSys)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCcuSimDlg message handlers

BOOL CCcuSimDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// EditControl 연결하기.
	//m_EditLogger.SetEditCtrl( m_CEditLog.m_hWnd );

	// Redirect cout to our Edit-Control
	m_pOldBuf = cout.rdbuf( & m_EditStrBuf );
	// and also the unicode version
	m_pOldBufW = wcout.rdbuf( & m_EditStrBufW );

	//cout << "cout (ANSI) works :-)" << endl;
	//wcout << L"wcout (UNICODE) works also ;-)" << endl;
	//cout << "\n\n";

	// TODO: Add extra initialization here
	m_bmpLampBigOff.LoadBitmap( IDB_BIGOFF );
	m_bmpLampGreenBigOn.LoadBitmap( IDB_BLUEBIGON );

	theCnfSys.SysRead();
		
	CMyTcpIp::Create( 13030 );

	m_bAudioEnable = TRUE;

	if( m_id.IplRead( "ipl.txt" ) != TRUE ) {
		MessageBox( "위협변수목록이 없어서 진행을 못합니다.\r\n위협변수목록(ipl.txt)를 복사해주세요!" , NULL, MB_ICONWARNING );
	}

	//m_CListEsm.SetColumnHeader( _T("#,30;방위,90;신호,34;주파수(MHz),160;PRI(us),140;S/J,30;PW(ns),110;세기(dB),90;스캔(초),70;최초시간,60;최근시간,60;식별,100;에미터명,100;기타,300" ) );

	//m_CListEsm.SetGridLines( FALSE );		// Show grid lines
	//m_CListEsm.SetEditable( FALSE );			// Disturb sub-text edit
	//m_CListEsm.DeleteAllItems();

	m_buffer.index = 0;
	m_buffer.buffer = (char *) malloc( sizeof( char ) * 1024 * 10 );

	m_noEMT = -1;

	AudioEnable( FALSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCcuSimDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCcuSimDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCcuSimDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::LanConnectionSwitch
// 반환되는 형  : void
// 함 수 인 자  : BOOL bStatus
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-12 11:23:10
//
void CCcuSimDlg::LanConnectionSwitch(BOOL bStatus)
{
	if( bStatus )
		m_CStaticLampLANConnection.SetBitmap( HBITMAP( m_bmpLampGreenBigOn ) );
	else	
		m_CStaticLampLANConnection.SetBitmap( HBITMAP( m_bmpLampBigOff ) );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::ReceiveMessage
// 반환되는 형  : void
// 함 수 인 자  : char *pBuff
// 함 수 인 자  : int length
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-12 11:48:16
//
void CCcuSimDlg::ReceiveMessage( char *pBuff, int length )
{
    int iCoParsedMessage;
	STR_LAN_MSG *pLanMsg;

	pLanMsg = ( STR_LAN_MSG * ) & m_buffer.buffer[0];
	memcpy( & m_buffer.buffer[ m_buffer.index ], pBuff, length );
	m_buffer.index += length;

	iCoParsedMessage = ParsingMessage();
	//m_buffer.index -= coParsedMessage;

	memcpy( & m_buffer.buffer[0], & m_buffer.buffer[iCoParsedMessage], m_buffer.index );
	

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::ConnectMessage
// 반환되는 형  : void
// 함 수 인 자  : sockaddr_in *pSockaddrInternet
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-12 17:44:31
//
void CCcuSimDlg::ConnectMessage( sockaddr_in *pSockaddrInternet )
{
	m_CoRecvSbit = 0;

	m_bStartSbit = FALSE;
	
	m_nTotalAet = 0;
	m_buffer.index = 0;
	for( int i=0 ; i < 256 ; ++i )
		m_nRowAetList[i] = -1;

	//m_CListEsm.DeleteAllItems();
	
	LanConnectionSwitch( TRUE );
	LogOutput( "\n*%d.%d.%d.%d 과 랜 연결이 되었습니다." , pSockaddrInternet->sin_addr.S_un.S_un_b.s_b1, pSockaddrInternet->sin_addr.S_un.S_un_b.s_b2, pSockaddrInternet->sin_addr.S_un.S_un_b.s_b3, pSockaddrInternet->sin_addr.S_un.S_un_b.s_b4 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : DisConnectMessaage
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-12 17:45:35
//
void CCcuSimDlg::DisConnectMessaage()
{
	m_CoRecvSbit = 0;

	m_bStartSbit = FALSE;
	m_nTotalAet = 0;
	m_buffer.index = 0;

	LanConnectionSwitch( FALSE );
	LogOutput( "\n*랜 연결이 끊어졌습니다." );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonESMode
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:36:01
//
void CCcuSimDlg::OnButtonESMode() 
{
	// TODO: Add your control notification handler code here
	m_nTotalAet = 0;
	for( int i=0 ; i < 256 ; ++i ) {
		m_nRowAetList[i] = -1;
    }

	//m_CListEsm.DeleteAllItems();

	LogOutput( "\n-> ES 체계로 운영합니다." );

	m_lanmsg.code = Msys_SetMode;
	m_lanmsg.size = sizeof(UINT);
	m_lanmsg.para.data.d1 = 1;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) ) {
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
		LanConnectionSwitch( FALSE );
	}
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonEWMode
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:45:02
//
void CCcuSimDlg::OnButtonEWMode() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> EW 체계로 운영합니다." );

	m_lanmsg.code = Msys_SetMode;
	m_lanmsg.size = sizeof(UINT);
	m_lanmsg.para.data.d1 = 2;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) ) {
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
		LanConnectionSwitch( FALSE );
	}
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonReadyMode
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:45:06
//
void CCcuSimDlg::OnButtonReadyMode() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> 모드 전환입니다." );

	m_lanmsg.code = Msys_SetMode;
	m_lanmsg.size = sizeof(UINT);
	m_lanmsg.para.data.d1 = 3;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) ) {
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
		LanConnectionSwitch( FALSE );		
	}

	CMyTcpIp::RequesetClose();

	LanConnectionSwitch( FALSE );

}
//        tmp = ( char *) & sndMsg;
//        sndByte = send(fds[1].fd, (char *) tmp, 4, 0);
//        sndByte = send(fds[1].fd, (char *) (tmp+4), sndMsg.size+_spSndSizeOffset-4, 0);

//////////////////////////////////////////////////////////////////////////
// 자체점검 운용 메시지

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonIBit
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-12 11:48:18
//
void CCcuSimDlg::OnButtonIBit() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> IBIT를 요구했습니다." );

	m_lanmsg.code = Mbit_ReqIbit;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) ) {
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
		LanConnectionSwitch( FALSE );
	}

/*
	char *tmp = ( char *) & m_lanmsg;
	if( 0 > CMyTcpIp::Send( ( char *) tmp, 4 ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );			*/
	//Sleep( 5000 );

	//if( 0 > CMyTcpIp::Send( ( char *) (tmp+4), m_lanmsg.size+_spSndSizeOffset-4 ) )
		//LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

/*
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg., m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
*/

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonSBit
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:46:28
//
void CCcuSimDlg::OnButtonSBit() 
{
	// TODO: Add your control notification handler code here
	m_bStartSbit = TRUE;

	LogOutput( "\n-> SBIT를 요구했습니다." );

	m_lanmsg.code = Mbit_StartSbit;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) ) {
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
		LanConnectionSwitch( FALSE );
	}
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnButtonSbitStop
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-16 18:38:58
//! \warning
//
void CCcuSimDlg::OnButtonSbitStop() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> SBIT 중지 요청을 했습니다." );

	m_lanmsg.code = Mbit_StopSbit;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonURBit
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:46:31
//
void CCcuSimDlg::OnButtonURBit() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> URBIT를 요구했습니다." );

	m_lanmsg.code = Mbit_ReqUbit;
	m_lanmsg.size = sizeof(UINT);
	m_lanmsg.para.data.d1 = _bitObjRsa;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonCBit
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-13 17:47:45
//
void CCcuSimDlg::OnButtonCBit() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> CBIT를 요구했습니다." );

	m_lanmsg.code = Mbit_ReqCbit;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
			LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
}

//////////////////////////////////////////////////////////////////////////
// 전술 운용 메시지

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnButtonSysStart
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-16 18:30:50
//! \warning
//
void CCcuSimDlg::OnButtonSysStart() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> 분석 시작을 전송했습니다." );

	m_lanmsg.code = Msys_Start;
	m_lanmsg.size = sizeof(UINT);
	m_lanmsg.para.data.d1 = (int) time( NULL );
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
			LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );	
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnButtonReqScan
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-17 09:47:43
//! \warning
//
void CCcuSimDlg::OnButtonReqScan() 
{
	// TODO: Add your control notification handler code here
	if( m_noEMT >= 1 ) {
		LogOutput( "\n-> %d 번 에게 스캔 분석 요구를 전송했습니다." , m_noEMT );

		m_lanmsg.code = Maet_ReqScan;
		m_lanmsg.size = sizeof( UINT );
		m_lanmsg.para.data.d1 = m_noEMT;

		if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
			LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
	}
	else {
		LogOutput( "\n -: 에미터가 없어 전송하지 않았습니다." );
	}
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnButtonDelete
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-17 11:40:34
//! \warning
//
void CCcuSimDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if( m_noEMT >= 1 ) {
		LogOutput( "\n-> %d 번 에게 삭제 요청을 했습니다." , m_noEMT );

		m_lanmsg.code = Maet_Clear;
		m_lanmsg.size = sizeof( UINT );
		m_lanmsg.para.data.d1 = m_noEMT;

		if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
			LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
	}
	else {
		LogOutput( "\n -: 에미터가 없어 전송하지 않았습니다." );
	}	
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnButtonAudioEnable
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-23 16:21:30
//! \warning
//
void CCcuSimDlg::OnButtonAudioEnable() 
{
	// TODO: Add your control notification handler code here

	m_bAudioEnable = ! m_bAudioEnable;

	m_lanmsg.code = Mcnf_Audio;
	m_lanmsg.size = sizeof( UINT );

	m_lanmsg.para.data.d1 = m_bAudioEnable;

	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnOK
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-14 09:33:41
//
void CCcuSimDlg::OnOK() 
{
	// TODO: Add extra validation here
	// OnButtonReadyMode();

	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonIPLVersion
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-14 09:55:45
//
void CCcuSimDlg::OnButtonIPLVersion() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> IPL 버젼 요구를 했습니다." );

	m_lanmsg.code = Mipl_ReqVersion;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonIPLDownload
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-19 17:52:01
//
void CCcuSimDlg::OnButtonIPLDownload() 
{
	// TODO: Add your control notification handler code here
	int i;
	int count;
	char *pTmp;

	count = m_id.GetCoIpl();
	LogOutput( "\n-> %d 개의 IPL 다운로드를 진행합니다." , count );

	m_lanmsg.code = Mipl_Start;
    m_lanmsg.size = sizeof(UINT)*2;
	m_lanmsg.para.data.d1 = IPL_VERSION;
	m_lanmsg.para.data.d2 = count;

	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );
	else {
		for( i=1 ; i <= count ; ++i ) {
			int div_len;

			m_lanmsg.code = Mipl_Download;
			m_lanmsg.size = sizeof( STR_IPL );
			memcpy( & m_lanmsg.para.ipl, & m_id.gIpl[i], sizeof( STR_IPL ) );

			// div_len = ( rand() * sizeof( ) ) % ( m_lanmsg.size+_spSndSizeOffset );

			div_len = 4;

			pTmp = ( char *) & m_lanmsg;

			CMyTcpIp::Send( pTmp+0, 16 );
			CMyTcpIp::Send( pTmp+16, 24 );
			CMyTcpIp::Send( pTmp+40, sizeof( STR_IPL )+_spSndSizeOffset-40 );

/*
			if( div_len != 0 ) {
				Sleep( 100 );
				CMyTcpIp::Send( ( char *) & m_lanmsg, div_len );
			}		*/
		}
	
		m_lanmsg.code = Mipl_End;
		m_lanmsg.size = 0;
		CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset );
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonThreshold
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-19 17:44:54
//
void CCcuSimDlg::OnButtonThreshold() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> SP1, SP2, SP3 장치에 임계값 설정 명령을 전송했습니다." );

	m_lanmsg.code = Mcnf_RxThreshold;
	m_lanmsg.size = sizeof( UINT ) * 2;
	m_lanmsg.para.data.d1 = _spBand1;
	m_lanmsg.para.data.d2 = 0x3A;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

	m_lanmsg.code = Mcnf_RxThreshold;
	m_lanmsg.size = sizeof( UINT ) * 2;
	m_lanmsg.para.data.d1 = _spBand2;
	m_lanmsg.para.data.d2 = 0x3A;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

	m_lanmsg.code = Mcnf_RxThreshold;
	m_lanmsg.size = sizeof( UINT ) * 2;
	m_lanmsg.para.data.d1 = _spBand3;
	m_lanmsg.para.data.d2 = 0x3A;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnDestroy
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-14 10:31:09
//
void CCcuSimDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	free( m_buffer.buffer );
	
	// TODO: Add your message handler code here
	cout.rdbuf( m_pOldBuf );
	wcout.rdbuf( m_pOldBufW );	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::OnButtonLogClear
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-14 10:31:07
//
void CCcuSimDlg::OnButtonLogClear() 
{
	// TODO: Add your control notification handler code here
	HWND hEdit = m_CEditLog.m_hWnd;

	BOOL bReadOnly = ::GetWindowLong( hEdit, GWL_STYLE ) & ES_READONLY;
	if( bReadOnly )
		::SendMessage( hEdit, EM_SETREADONLY, FALSE, 0 );
	::SendMessage( hEdit, EM_SETSEL, 0, -1 );
	::SendMessage( hEdit, WM_CLEAR, 0, 0 );
	if( bReadOnly )
		::SendMessage( hEdit, EM_SETREADONLY, TRUE, 0 );
	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCcuSimDlg::LogOutput
// 반환되는 형  : int
// 함 수 인 자  : char *format
// 함 수 인 자  : ...
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-04-19 17:35:10
//
int CCcuSimDlg::LogOutput( char *format, ... )
{
	int cnt;
	char str[100];

	va_list argptr;

	va_start( argptr, format );

  cnt = vsprintf( str, format, argptr );
  va_end( argptr );

    TRACE( str );
	//cout << str;
	//cout.flush();

	return cnt;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::ParsingMessage 
//!					 랜 메시지로부터 수신한 랜 데이터를 해석해서 해당 창에 전시하도록 한다.
//!	\author  조철희
//!	\param	 pBuff	인자형태 char *
//! \param	 length	인자형태 int
//!	\return	 int
//! \version 1.0
//! \date		 2006-05-10 14:08:57
//! \warning
//
int CCcuSimDlg::ParsingMessage( )
{
	int count, size;
	int coParsedMessage=0;
	int co_remained_message;

	STR_LAN_MSG *pLanMsg;
    STR_LAN_HEADER strLanHeader;

    co_remained_message = m_buffer.index;

	pLanMsg = ( STR_LAN_MSG * ) & m_buffer.buffer[coParsedMessage];
	while( co_remained_message >= sizeof(int)*2 ) {
        memcpy( & strLanHeader, pLanMsg, sizeof(int)*2 );
        BEModeChange( (char *) & strLanHeader, sizeof(int)*2 );

        if( co_remained_message >= ( 2*sizeof( int ) + strLanHeader.uiLength ) ) {
            BEModeChange( (char *) pLanMsg, sizeof(int)*2+strLanHeader.uiLength );

            count = 2 * sizeof( int ) + pLanMsg->size;
            coParsedMessage += count;

            DISP_LanMsg( pLanMsg, 1, count );

            // 화면 처리를 한다.
            switch( pLanMsg->code ) {
                // SBIT 처리

                // 시스템 변수
                case Ecnf_SetSys :			
                    break;

                    // 에미터 관련 메시지
                case Maet_Update_Ccu : 
                    UpdateAetInfo( pLanMsg );
                    break;

                case Maet_Lost_Ccu : 
                    LostAetInfo( pLanMsg );
                    break;

                case Maet_Delete_Ccu : 
                    DeleteAetInfo( pLanMsg );
                    break;

                case Maet_New_Ccu : 
                    if( m_bStartSbit == FALSE ) {
                        InsertAetInfo( pLanMsg );
                    }
                    else {
                        ++ m_CoRecvSbit;

                        if( m_CoRecvSbit == 3 ) {
                            m_lanmsg.code = Mbit_StopSbit;
                            m_lanmsg.size = 0;
                            if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
                                LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

                            m_CoRecvSbit = 0;

                        }
                    }
                    break;

                default :
                    break;
            }

            co_remained_message -= count;
            TRACE( "\nco_remained_message[%d]" , co_remained_message );
            m_buffer.index -= count;

            pLanMsg = ( STR_LAN_MSG * ) & m_buffer.buffer[ coParsedMessage ];
        }
        else {
            break;
        }
    }

    return coParsedMessage;

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::DISP_LanMsg
//!	\author  조철희
//! \param	 pLanMsg	인자형태 STR_LAN_MSG *
//! \param	 mode	인자형태 int
//! \param	 rsBsize	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 14:46:10
//! \warning
//
void CCcuSimDlg::DISP_LanMsg(STR_LAN_MSG *pLanMsg, int mode, int rsBsize) 
{

	if( mode != _spZero) {

		if( rsBsize == _spZero ) {
			LogOutput( "\n[W] Invalid Send !" );
			return;
		}
		LogOutput( "\n<- op[%4d] size[%3d] rcv[%3d] :", pLanMsg->code, pLanMsg->size, rsBsize );

    switch( pLanMsg->code ) {
			case Msys_Error          :LogOutput(" Msys_Error...[%d,%d]" , pLanMsg->para.data.d1, pLanMsg->para.data.d2 );
			CASE Esys_SetMode        :LogOutput(" Esys_SetMode..." );
			CASE Mbit_ResultEsIbit   :LogOutput(" Mbit_ResultEsIbit...[%08x]" , pLanMsg->para.ibit.w32 );
			CASE Mbit_ResultEsSbit   :LogOutput(" Ebit_ResultEsSbit...[%08x,%08x,%08x,%08x]" , pLanMsg->para.sbit.rsa.w32,
																pLanMsg->para.sbit.sp[0].w32, pLanMsg->para.sbit.sp[1].w32, pLanMsg->para.sbit.sp[2].w32 );
			CASE Mbit_Aet            :LogOutput(" Mbit_Aet...[AET No. %d]", pLanMsg->para.aet.noEMT );

      CASE Mbit_ResultEsCbit   :LogOutput(" Mbit_ResultEsCbit...[%x,%x,%x,%x]", pLanMsg->para.cbit.rsa.w32,
                                pLanMsg->para.cbit.sp[0].w32, pLanMsg->para.cbit.sp[1].w32, pLanMsg->para.cbit.sp[2].w32 );
      CASE Mbit_ResultEsUbit   :LogOutput(" Mbit_ResultEsUbit...RSA [%8x]", pLanMsg->para.ubit.rsa.w32 );
                                LogOutput("SP  [%8x,%8x,%8x]", pLanMsg->para.ubit.sp[0].w32, pLanMsg->para.ubit.sp[1].w32,
                                pLanMsg->para.ubit.sp[2].w32 );
      CASE Mipl_Version        :LogOutput(" Mipl_Version...[%x,%d]", pLanMsg->para.data.d1, pLanMsg->para.data.d2 );
      CASE Mipl_WriteStatus    :LogOutput(" Mipl_WriteStatus...[%3d]", pLanMsg->para.data.d1 );
      CASE Maet_New_Ccu        :LogOutput(" Maet_New......[%3d] AOA[%d]", pLanMsg->para.data.d1, AOACNV( pLanMsg->para.aet.aoa ) );
      CASE Maet_Update_Ccu     :LogOutput(" Maet_Update...[%3d]", pLanMsg->para.data.d1 );
      CASE Maet_Lost_Ccu       :LogOutput(" Maet_Lost.....[%3d]", pLanMsg->para.data.d1 );
      CASE Maet_Delete_Ccu     :LogOutput(" Maet_Delete...[%d]", pLanMsg->para.data.d1 );
      CASE Maet_AllSend_Ccu 	 :LogOutput(" Maet_AllSend_Ccu...");
      CASE Ecnf_SetSys         :LogOutput(" Ecnf_SetSys..." );
                                LogOutput("AD[%d-%d-%d]" , pLanMsg->para.cnf.spaoadiff[0],
                                                        pLanMsg->para.cnf.spaoadiff[1],
                                                        pLanMsg->para.cnf.spaoadiff[2]);
                                LogOutput("\n\t\tFD[%d-%d-%d]" , pLanMsg->para.cnf.spfrqdiff[0],
                                                              pLanMsg->para.cnf.spfrqdiff[1],
                                                              pLanMsg->para.cnf.spfrqdiff[2]);
                                LogOutput("\n\t\tTK[%d,%d,%d]" , pLanMsg->para.cnf.sptrkaoa,
                                                              pLanMsg->para.cnf.sptrkfixfrq,
                                                              pLanMsg->para.cnf.sptrkagifrq);
                                LogOutput("\n\t\tMG[%d,%d]" , pLanMsg->para.cnf.spmrgaoa,
                                                           pLanMsg->para.cnf.spmrgfrq);
                                LogOutput("\n\t\tMP[%d,%d,%d,%d]" , pLanMsg->para.cnf.spminstb,
                                                                 pLanMsg->para.cnf.spminjit,
                                                                 pLanMsg->para.cnf.spminrefpri,
                                                                 pLanMsg->para.cnf.spminagipri );
                                LogOutput("\n\t\tMP[%d,%d]" , pLanMsg->para.cnf.spshiftaoa,
                                                           pLanMsg->para.cnf.spshiftfrq );
			CASE Mdebug_Snd_Pdw			:LogOutput(" Mdebug_Snd_Pdw...");
      DEFAULT : printf(" Unknown Msg..."); break;
		}
	}
	else
	{
#ifdef M68K			// for CCU Simulator message
//		RPrintf("\n\t*[RcvLan] op[%4d] size[%3d] rcv[%3d] :", pLanMsg->code, pLanMsg->size, rsBsize);
//		timeTick = time(NULL);
//		printf( "\n%s" , ctime( & timeTick ) );
		printf("\n\t*[RcvLan] op[%4d] size[%3d] rcv[%3d] :", pLanMsg->code, pLanMsg->size, rsBsize);
#else
		printf("\n\t*[SndLan] op[%4d] size[%3d] snd[%3d] :", pLanMsg->code, pLanMsg->size, rsBsize);
#endif
		switch(pLanMsg->code)
		{
            case Msys_Error          :printf(" Msys_Error...[%08x,%08x]" ,
                                      pLanMsg->para.data.d1, pLanMsg->para.data.d2 );
            CASE Msys_SetMode        :printf(" Msys_SetMode...[%d]",
                                      pLanMsg->para.data.d1 );
            CASE Msys_Start          :printf(" Msys_Start...[%d]",
//                                    ctime( (time_t *) &(pLanMsg->para.data.d1) ) );
                                      pLanMsg->para.data.d1 );
            CASE Mbit_ReqIbit        :printf(" Mbit_ReqIbit...");
            CASE Mbit_StartSbit      :printf(" Mbit_StartSbit...");
            CASE Mbit_StartSbit_V3	 :printf(" Mbit_StartSbit_V3...");
            CASE Mbit_StopSbit       :printf(" Mbit_StopSbit...");
            CASE Mbit_ReqCbit        :printf(" Mbit_ReqCbit...");
            CASE Mbit_ReqUbit        :printf(" Mbit_ReqUbit...[%x]" ,
                                      pLanMsg->para.data.d1 );
            CASE Mipl_ReqVersion     :printf(" Mipl_ReqVersion...");
            CASE Mipl_Start          :printf(" Mipl_Start...[%d,%d]",
                                      pLanMsg->para.data.d1, pLanMsg->para.data.d2 );
            CASE Mipl_Download       :printf(" Mipl_Download...[%u]", pLanMsg->para.ipl.noIPL);
            CASE Mipl_End            :printf(" Mipl_End...");
            CASE Mcnf_BandEnable     :printf(" Mcnf_BandEnable...B[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_NotchFilter    :printf(" Mcnf_NotchFilter...N[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_FmopThreshold  :printf(" Mcnf_FmopThreshold...F[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_PMOPThreshold  :printf(" Mcnf_PMOPThreshold...P[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_Dca            :printf(" Mcnf_Dca...D[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_RxThreshold    :printf(" Mcnf_RxThreshold...T[%d,%d]", pLanMsg->para.data.d1,
                                      pLanMsg->para.data.d2 );
            CASE Mcnf_RxAntOffset    :printf(" Mcnf_RxAntOffset...A[%d,%d]",pLanMsg->para.data.d1, pLanMsg->para.data.d2 );
            CASE Mcnf_EABlankingAttn:printf(" Mcnf_EABlankingAttn...E[%d]",pLanMsg->para.data.d1 );
            CASE Mcnf_Audio          :printf(" Mcnf_Audio...[%d]", pLanMsg->para.data.d1 );
            CASE Mcnf_AudioParam     :printf(" Mcnf_AudioParam...\n\t\t  B[%1d-%1d] F[%5d-%5d] A[%5d-%5d]" ,
                                      pLanMsg->para.cnfaud.LowerBC, pLanMsg->para.cnfaud.UpperBC,
                                      pLanMsg->para.cnfaud.LowerFrq, pLanMsg->para.cnfaud.UpperFrq,
                                      pLanMsg->para.cnfaud.FromAoa, pLanMsg->para.cnfaud.ToAoa );
            CASE Mcnf_ScanLevel      :printf(" Mcnf_ScanThreat...S[%d]", pLanMsg->para.data.d1 );
            CASE Mcnf_InhibitAoa     :printf(" Mcnf_InhibitAoa...\n\t\t  F[%1d]%7d%7d, F[%1d]%7d%7d, F[%1d]%7d%7d",
                                      pLanMsg->para.cnfaoa[0].flg,pLanMsg->para.cnfaoa[0].fr,
                                      pLanMsg->para.cnfaoa[0].to,
                                      pLanMsg->para.cnfaoa[1].flg,pLanMsg->para.cnfaoa[1].fr,
                                      pLanMsg->para.cnfaoa[1].to,
                                      pLanMsg->para.cnfaoa[2].flg,pLanMsg->para.cnfaoa[2].fr,
                                      pLanMsg->para.cnfaoa[2].to );
                                      printf("\n\t\t  F[%1d]%7d%7d, F[%1d]%7d%7d, F[%1d]%7d%7d",
                                      pLanMsg->para.cnfaoa[3].flg,pLanMsg->para.cnfaoa[3].fr,
                                      pLanMsg->para.cnfaoa[3].to,
                                      pLanMsg->para.cnfaoa[4].flg,pLanMsg->para.cnfaoa[4].fr,
                                      pLanMsg->para.cnfaoa[4].to,
                                      pLanMsg->para.cnfaoa[5].flg,pLanMsg->para.cnfaoa[5].fr,
                                      pLanMsg->para.cnfaoa[5].to );
                                      printf("\n\t\t  F[%1d]%7d%7d, F[%1d]%7d%7d, F[%1d]%7d%7d",
                                      pLanMsg->para.cnfaoa[6].flg,pLanMsg->para.cnfaoa[6].fr,
                                      pLanMsg->para.cnfaoa[6].to,
                                      pLanMsg->para.cnfaoa[7].flg,pLanMsg->para.cnfaoa[7].fr,
                                      pLanMsg->para.cnfaoa[7].to,
                                      pLanMsg->para.cnfaoa[8].flg,pLanMsg->para.cnfaoa[8].fr,
                                      pLanMsg->para.cnfaoa[8].to );
            CASE Mcnf_InhibitFreq    :printf(" Mcnf_InhibitFrq...\n\t\t  F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d]",
                                    pLanMsg->para.cnffrq[0].flg,pLanMsg->para.cnffrq[0].bnd,
                                    pLanMsg->para.cnffrq[0].low,pLanMsg->para.cnffrq[0].hgh,
                                    pLanMsg->para.cnffrq[1].flg,pLanMsg->para.cnffrq[1].bnd,
                                    pLanMsg->para.cnffrq[1].low,pLanMsg->para.cnffrq[1].hgh,
                                    pLanMsg->para.cnffrq[2].flg,pLanMsg->para.cnffrq[2].bnd,
                                    pLanMsg->para.cnffrq[2].low,pLanMsg->para.cnffrq[2].hgh );
                                    printf("\n\t\t  F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d]",
                                    pLanMsg->para.cnffrq[3].flg,pLanMsg->para.cnffrq[3].bnd,
                                    pLanMsg->para.cnffrq[3].low,pLanMsg->para.cnffrq[3].hgh,
                                    pLanMsg->para.cnffrq[4].flg,pLanMsg->para.cnffrq[4].bnd,
                                    pLanMsg->para.cnffrq[4].low,pLanMsg->para.cnffrq[4].hgh,
                                    pLanMsg->para.cnffrq[5].flg,pLanMsg->para.cnffrq[5].bnd,
                                    pLanMsg->para.cnffrq[5].low,pLanMsg->para.cnffrq[5].hgh );
                                    printf("\n\t\t  F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d, F[%1d]B[%1d]%7d%7d]",
                                    pLanMsg->para.cnffrq[6].flg,pLanMsg->para.cnffrq[6].bnd,
                                    pLanMsg->para.cnffrq[6].low,pLanMsg->para.cnffrq[6].hgh,
                                    pLanMsg->para.cnffrq[7].flg,pLanMsg->para.cnffrq[7].bnd,
                                    pLanMsg->para.cnffrq[7].low,pLanMsg->para.cnffrq[7].hgh,
                                    pLanMsg->para.cnffrq[8].flg,pLanMsg->para.cnffrq[8].bnd,
                                    pLanMsg->para.cnffrq[8].low,pLanMsg->para.cnffrq[8].hgh );
			CASE Mcnf_DelTime	   :printf(" Mcnf_DelTime...[%d]" , pLanMsg->para.data.d1 );
			CASE Mcnf_ReqSys	   :printf(" Mcnf_ReqSys..." );
			CASE Mcnf_SetSys	   :printf(" Mcnf_SetSys..." );
			case Ecnf_SetSys 	   :if( pLanMsg->code == Ecnf_SetSys )
									   printf(" Ecnf_SetSys..." );
									printf("AD[%d-%d-%d]" , pLanMsg->para.cnf.spaoadiff[0],
														    pLanMsg->para.cnf.spaoadiff[1],
															pLanMsg->para.cnf.spaoadiff[2]);
									printf("\n\t\tFD[%d-%d-%d]" , pLanMsg->para.cnf.spfrqdiff[0],
																  pLanMsg->para.cnf.spfrqdiff[1],
																  pLanMsg->para.cnf.spfrqdiff[2]);
									printf("\n\t\tTK[%d,%d,%d]" , pLanMsg->para.cnf.sptrkaoa,
																  pLanMsg->para.cnf.sptrkfixfrq,
																  pLanMsg->para.cnf.sptrkagifrq);
									printf("\n\t\tMG[%d,%d]" , pLanMsg->para.cnf.spmrgaoa,
															   pLanMsg->para.cnf.spmrgfrq);
									printf("\n\t\tMP[%d,%d,%d,%d]" , pLanMsg->para.cnf.spminstb,
																	 pLanMsg->para.cnf.spminjit,
																	 pLanMsg->para.cnf.spminrefpri,
																	 pLanMsg->para.cnf.spminagipri );
									printf("\n\t\tMP[%d,%d]" , pLanMsg->para.cnf.spshiftaoa,
															   pLanMsg->para.cnf.spshiftfrq );
			CASE Mcnf_EWMode	   :printf(" EW Mode[%d]" , pLanMsg->para.data.d1 );
			CASE Mcnf_AutoLevel	   :printf(" Auto Level[%d]" , pLanMsg->para.data.d1 );
      CASE Maet_ReqScan      :printf(" Maet_ReqScan...[%d]", pLanMsg->para.data.d1 );
      CASE Maet_Clear        :printf(" Maet_Clear...[%d]", pLanMsg->para.data.d1 );
			CASE Maet_AddJamming   :printf(" Add Jamming[%d]" , pLanMsg->para.data.d1 );
			CASE Maet_DelJamming   :printf(" Del Jamming[%d]" , pLanMsg->para.data.d1 );
      CASE Maet_SigHide			 :printf(" Maet_SigHide...[%d]" , pLanMsg->para.data.d1 );
      CASE Maet_SigShow			 :printf(" Maet_SigShow...[%d]" , pLanMsg->para.data.d1 );
      CASE Msys_Modify       :printf(" Msys_Modify..." );
			CASE Msys_Reboot       :printf(" Msys_Reboot..." );		// debug, 04-06-25
			CASE Mdebug_Get_Pdw	   :printf(" Mdebug_GetPdw...[%d]" , pLanMsg->para.data.d1 );
      DEFAULT: printf(" Unknown Msg..."); break;
        }
	}

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::InsertAetInfo
//!	\author  조철희
//!	\param	 pLanMsg	인자형태 STR_LAN_MSG *
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 15:43:23
//! \warning
//
void CCcuSimDlg::InsertAetInfo(STR_LAN_MSG *pLanMsg)
{
// 	int idx;
// 	int row=m_CListEsm.GetItemCount();
// 
// 	// 신호목록창에 추가할 열 추가
// 	if( row >= MAX_AET_LIST )
// 		LogOutput( "\n* 에미터 개수를 초과했습니다. 자체 버그가 발생했습니다." );
// 	else {
// 		if( IsExistEmitter( pLanMsg->para.aet.noEMT ) == FALSE ) {
// 			memmove( & m_nRowAetList[1], & m_nRowAetList[0], m_nTotalAet*sizeof(int) );
// 
// 			++ m_nTotalAet;
// 			m_nRowAetList[0] = pLanMsg->para.aet.noEMT;
// 
// 			idx = m_CListEsm.InsertItem(0, _T("") );
// 			if( idx == -1 )
// 				m_CListEsm.MoveTo( row-1, 0 );
// 			UpdateAetList( & pLanMsg->para.aet, 0 );
// 		}
// 		else {
// 			LogOutput( "\n*이미 %d 번의 에미터가 존재합니다. RSA의 자체 에러입니다." , pLanMsg->para.aet.noEMT );
// 		}
// 	}
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::IsExistEmitter
//!	\author  조철희
//!	\param	 \param	 noEMT	인자형태 int
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-05-17 11:54:42
//! \warning
//
BOOL CCcuSimDlg::IsExistEmitter( int noEMT )
{
// 	int i, count;
// 
// 	CString s;
// 
// 	count=m_CListEsm.GetItemCount();
// 	for( i=0 ; i < count ; ++i ) {
// 		if( m_nRowAetList[i] == noEMT ) {
// 			return TRUE;	
// 		}
// 	}

	return FALSE;

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::LostAetList
//!	\author  조철희
//! \param	 pAet	인자형태 STR_AET *
//! \param	 row	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 16:30:23
//! \warning
//
void CCcuSimDlg::LostAetList( STR_AET *pAet, int row )
{
// 	char buff[200];
// 
// 	sprintf( buff, "L%d", pAet->noEMT );
// 	m_CListEsm.SetItemText( row, LIST_NO, buff );
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::LostAetInfo
//!	\author  조철희
//!	\param	 pLanMsg	인자형태 STR_LAN_MSG *
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 15:54:52
//! \warning
//
void CCcuSimDlg::LostAetInfo(STR_LAN_MSG *pLanMsg)
{
// 	char buff[20];
// 	int i, count;
// 
// 	CString s;
// 
// 	if( IsExistEmitter( pLanMsg->para.aet.noEMT ) == TRUE ) {
// 		sprintf( buff, "%d" , pLanMsg->para.aet.noEMT );
// 		count=m_CListEsm.GetItemCount();
// 		for( i=0 ; i < count ; ++i ) {
// 			if( m_nRowAetList[i] == pLanMsg->para.aet.noEMT ) {
// 				LostAetList( & pLanMsg->para.aet, i );	
// 				return;	
// 			}
// 		}
// 	}
// 	else {
// 		LogOutput( "\n*%d 번의 에미터는 존재하지 않습니다. RSA 자체 에러입니다." , pLanMsg->para.aet.noEMT );
// 	}

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::DeleteAetInfo
//!	\author  조철희
//!	\param	 pLanMsg	인자형태 STR_LAN_MSG *
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 15:55:18
//! \warning
//
void CCcuSimDlg::DeleteAetInfo(STR_LAN_MSG *pLanMsg)
{
// 	char buff[20];
// 	int i, count;
// 
// 	CString s;
// 
// 	sprintf( buff, "%d" , pLanMsg->para.aet.noEMT );
// 	count=m_CListEsm.GetItemCount();
// 	for( i=0 ; i < count ; ++i ) {
// 		if( m_nRowAetList[i] == pLanMsg->para.aet.noEMT ) {
// 			memmove( & m_nRowAetList[i], & m_nRowAetList[i+1], sizeof(int) * (m_nTotalAet-1) );
// 			-- m_nTotalAet;
// 
// 			m_CListEsm.DeleteItem( i, FALSE );
// 
// 			return;
// 		}
// 	}
// 
// 	LogOutput( "\n*%d 번의 에미터는 존재하지 않습니다. RSA 자체 에러입니다." , pLanMsg->para.aet.noEMT );
// 	
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::UpdateAetInfo
//!	\author  조철희
//!	\param	 pLanMsg	인자형태 STR_LAN_MSG *
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 15:55:18
//! \warning
//
void CCcuSimDlg::UpdateAetInfo(STR_LAN_MSG *pLanMsg)
{
// 	char buff[20];
// 	int i, count;
// 
// 	CString s;
// 
// 	if( IsExistEmitter( pLanMsg->para.aet.noEMT ) == TRUE ) {
// 		sprintf( buff, "%d" , pLanMsg->para.aet.noEMT );
// 		count=m_CListEsm.GetItemCount();
// 		for( i=0 ; i < count ; ++i ) {
// 			if( m_nRowAetList[i] == pLanMsg->para.aet.noEMT ) {
// 				UpdateAetList( & pLanMsg->para.aet, i );	
// 				return;	
// 			}
// 		}
// 	}
// 	else {
// 		LogOutput( "\n*%d 번의 에미터는 존재하지 않습니다. RSA 자체 에러입니다." , pLanMsg->para.aet.noEMT );		
// 	}
}



//////////////////////////////////////////////////////////////////////
//
//!	\brief	 AET 정보를 목록창에 전시한다.
//!
//!					  상세 정보는 여기에...
//!	\author  조철희
//! \param	 pAet	인자형태 STR_AET *
//! \param	 row	인자형태 int
//!	\param	 row	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-10 16:26:53
//! \warning
//
void CCcuSimDlg::UpdateAetList( STR_AET *pAet, int row )
{
// 	struct tm *nowtime;
// 	char buff[200];
// 
// 	STR_MINMAX mm;
// 
// 	sprintf( buff, "%d", pAet->noEMT );
// 	m_CListEsm.SetItemText( row, LIST_NO, buff );
// 
// 	mm.mean = AOACNV( pAet->aoa );
// 	sprintf( buff, "%d", mm.mean ); 
// 	m_CListEsm.SetItemText( row, LIST_AOA, buff );
// 
// 	sprintf( buff, "%s" , aet_signal_type[pAet->sigType] );
// 	/*! \todo	*/
// 	m_CListEsm.SetItemText( row, LIST_SIGTYPE, buff );
// 	
// 	/*! \bug 한글이 되네 ?
// 					 어떻게 될까?
// 			\date 2006-05-12 11:01:55, 조철희
// 	*/
// 	mm.mean = FRQCNV( pAet->frq.band, pAet->frq.mean );
// 	mm.min  = F_FRQCNV( pAet->frq.band, pAet->frq.min );
// 	mm.max  = C_FRQCNV( pAet->frq.band, pAet->frq.max );
// 	/*! \bug 한글이 되네 ?
// 					 어떻게 될까?
// 			\date 2006-05-12 11:01:55, 조철희
// 	*/
// 	switch( pAet->frq.type ) {
// 		case _FIXED :
// 		case _RANDOM_AGILE :
// 		case _CHIRP_UP :
// 		case _CHIRP_DN :
// 		case _PMOP :
// 			sprintf( buff, "%s %d(%d,%d),%d", aet_freq_type[pAet->frq.type], mm.mean, mm.min, mm.max, mm.max-mm.min ); 
// 			break;
// 
// 		case _HOPPING :
// 			sprintf( buff, "%s %d(%d,%d) %d", aet_freq_type[pAet->frq.type], mm.mean, mm.min, mm.max, pAet->frq.swtLev ); 
// 			break;
// 
// 		case _PATTERN_AGILE :
// 			sprintf( buff, "%s %d(%d,%d) %d", aet_freq_type[pAet->frq.type], mm.mean, mm.min, mm.max, UDIV( pAet->frq.patPrd, ONE_MILLISEC) ); 
// 			break;
// 	}
// 	m_CListEsm.SetItemText( row, LIST_FREQ, buff );
// 
// 	mm.mean = UDIV( pAet->pri.mean, _spOneMicrosec );
// 	mm.min  = F_UDIV( pAet->pri.min, _spOneMicrosec );
// 	mm.max  = C_UDIV( pAet->pri.max, _spOneMicrosec );
// 	switch( pAet->pri.type ) {
// 		case _STABLE :
// 		case _STAGGER :
// 		case _JITTER :
// 		case _DWELL :
// 			sprintf( buff, "%s %d(%d,%d)", aet_pri_type[pAet->pri.type], mm.mean, mm.min, mm.max ); 
// 			break;
// 
// 		case _PATTERN :
// 			sprintf( buff, "%s %d(%d,%d) %d", aet_pri_type[pAet->pri.type], mm.mean, mm.min, mm.max, UDIV( pAet->pri.patPrd, ONE_MILLISEC) ); 
// 			break;
// 
// 	}
// 	m_CListEsm.SetItemText( row, LIST_PRI, buff );
// 
// 	if( pAet->pri.type == _JITTER || pAet->pri.type == _PATTERN )
// 		sprintf( buff, "%d", pAet->pri.jtrPer );
// 	else if( pAet->pri.type == _STAGGER || pAet->pri.type == _DWELL )
// 		sprintf( buff, "%d", pAet->pri.swtLev );
// 	else
// 		sprintf( buff, "0" );
// 	m_CListEsm.SetItemText( row, LIST_LEVEL, buff );
// 
// 	mm.mean = PWCNV( pAet->pw.mean );
// 	mm.min = F_PWCNV( pAet->pw.min );
// 	mm.max = C_PWCNV( pAet->pw.max );;
// 	sprintf( buff, "%d(%d,%d)", mm.mean, mm.min, mm.max ); 
// 	m_CListEsm.SetItemText( row, LIST_PW, buff );
// 
// 	mm.mean = PACNV( pAet->pa.mean );
// 	mm.min = F_PACNV( pAet->pa.min );
// 	mm.max = C_PACNV( pAet->pa.max );
// 	sprintf( buff, "%d(%d,%d)", mm.mean, mm.min, mm.max ); 
// 	m_CListEsm.SetItemText( row, LIST_PA, buff );
// 
// 	mm.mean =	UDIV( pAet->as.prd, _spOneMilli );
// 	if( pAet->as.stat == SELF_SUCCESS )
// 		sprintf( buff, "%s,%d", aet_asp_type_ch[pAet->as.type], mm.mean );
// 	else if( pAet->as.stat == NO_PROCESS )
// 		sprintf( buff, "분석중" );
// 	else
// 		sprintf( buff, "분석실패" );
// 	m_CListEsm.SetItemText( row, LIST_SCAN, buff );
// 
// 	nowtime = localtime( & pAet->seen.frst );
// 	sprintf( buff, "%02d:%02d:%02d" , nowtime->tm_hour, nowtime->tm_min, nowtime->tm_sec );
// 	m_CListEsm.SetItemText( row, LIST_FIRST_SEEN, buff );
// 
// 	nowtime = localtime( & pAet->seen.last );
// 	sprintf( buff, "%02d:%02d:%02d" , nowtime->tm_hour, nowtime->tm_min, nowtime->tm_sec );
// 	m_CListEsm.SetItemText( row, LIST_LAST_SEEN, buff );
// 
// 	if( pAet->id.coAmbi == 0 )
// 		sprintf( buff, "-" );
// 	else {
// 		int len;
// 
// 		len = 0;
// 		for( int i=0 ; i < pAet->id.coAmbi ; ++i ) {
// 			len += sprintf( buff+len, "%d,", pAet->id.noIPL[i] );
// 		}
// 	}
// 	m_CListEsm.SetItemText( row, LIST_ID, buff );
// 
// 	//sprintf( buff, "%s/%s" , gIpl[pAet->id.noIPL[0]].elintNot, gIpl[pAet->id.noIPL[0]].elintName );
// 	//m_CListEsm.SetItemText( row, LIST_EMITTER_NAME, buff );
// 
// 	// 기타 정보 표시
// 	if( pAet->frq.type == _HOPPING ) {
// 		int totcount=0;
// 		int count;
// 		for( int i=0 ; i < pAet->frq.swtLev ; ++i ) {
// 			count = sprintf( buff+totcount, "%d," , pAet->frq.swtVal[i] );
// 			totcount += count;
// 
// 		}
// 		m_CListEsm.SetItemText( row, LIST_ETC, buff );
// 	}
// 	else if( pAet->pri.type == _STAGGER || pAet->pri.type == _DWELL ) {
// 		int totcount=0;
// 		int count;
// 		for( int i=0 ; i < pAet->pri.swtLev ; ++i ) {
// 			count = sprintf( buff+totcount, "%d," , UDIV( pAet->pri.swtVal[i], ONE_MICROSEC ) );
// 			totcount += count;
// 
// 		}
// 		m_CListEsm.SetItemText( row, LIST_ETC, buff );
// 	}
}

void CCcuSimDlg::OnItemclickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CCcuSimDlg::OnColumnclickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::OnClickListEsm
//!	\author  조철희
//! \param	 pNMHDR	인자형태 NMHDR*
//! \param	 pResult	인자형태 LRESULT*
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-17 10:27:34
//! \warning
//
void CCcuSimDlg::OnClickListEsm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	int nRow = m_CListEsm.GetNextItem(-1, LVNI_SELECTED );
// 	if( nRow >= 0 ) {
// 		m_noEMT = m_nRowAetList[nRow];
// 
// 		char buff[100];
// 		sprintf( buff, "%d" , m_noEMT );
// 		m_CEditNoEmitter.SetWindowText( buff );
// 	}
// 
// 	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CCcuSimDlg::AudioEnable
//!	\author  조철희
//!	\param	 bSwitch	인자형태 BOOL
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-23 16:33:19
//! \warning
//
void CCcuSimDlg::AudioEnable(BOOL bSwitch)
{
	m_RadioAudioEnable = ! bSwitch;

	UpdateData( FALSE );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CCcuSimDlg::OnButtonReqCnSsys
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-11-09 15:49:38
//! \warning
//
void CCcuSimDlg::OnButtonReqCnSsys() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> 시스템 변수를 요구합니다." );

	m_lanmsg.code = Mcnf_ReqSys;
	m_lanmsg.size = 0;
	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );	
}


//////////////////////////////////////////////////////////////////////
//
//! \brief    CCcuSimDlg::OnButtonSetCnfSys
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-11-10 10:36:45
//! \warning
//
void CCcuSimDlg::OnButtonSetCnfSys() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> 시스템 변수를 설정합니다." );

	m_lanmsg.code = Mcnf_SetSys;
	m_lanmsg.size = sizeof( STR_CNFSYS );

	memcpy( & m_lanmsg.para.cnf, & theCnfSys.m_cnfsys, sizeof( STR_CNFSYS ) );
	// m_lanmsg.para. = m_noEMT;

	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CCcuSimDlg::OnButtonAudioRange
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2007-01-30 14:56:02
//! \warning
//
void CCcuSimDlg::OnButtonAudioRange() 
{
	// TODO: Add your control notification handler code here

	m_lanmsg.code = Mcnf_AudioParam;
	m_lanmsg.size = sizeof( LAN_AUDIO );

	m_lanmsg.para.cnfaud.LowerBC = _spBand1;
  m_lanmsg.para.cnfaud.UpperBC = _spBand3;
  m_lanmsg.para.cnfaud.LowerFrq = 0;
	m_lanmsg.para.cnfaud.UpperFrq = 0xffff;

  m_lanmsg.para.cnfaud.FromAoa  = 0;
  m_lanmsg.para.cnfaud.ToAoa  = 0xffff;	

  m_lanmsg.para.cnfaud.FromPa  = 0;
  m_lanmsg.para.cnfaud.ToPa  = 0xffff;	

	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );

}

void CCcuSimDlg::OnRadioAudioEnable() 
{
	// TODO: Add your control notification handler code here
	
}

void CCcuSimDlg::OnButtonSetAllCnfSys() 
{
	// TODO: Add your control notification handler code here
	LogOutput( "\n-> 시스템 변수를 요구합니다." );

	m_lanmsg.code = Msys_Modify;
	m_lanmsg.size = sizeof( STR_SYS );

	memcpy( & m_lanmsg.para.sp, & theCnfSys.m_sp, sizeof( STR_SYS ) );
	// m_lanmsg.para. = m_noEMT;

	if( 0 > CMyTcpIp::Send( ( char *) & m_lanmsg, m_lanmsg.size+_spSndSizeOffset ) )
		LogOutput( "\n*랜 소켓이 연결되지 않았습니다." );	
}
