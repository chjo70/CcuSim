// MyTcpIp.cpp: implementation of the CMyTcpIp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CcuSim.h"

#include "MyTcpIp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// 초기화 값을 여기에 삽입
CMyTcpIp::CMyTcpIp()
{
	m_pThread = NULL;				// 랜 수신 쓰레드의 초기화
}

///////////////////////////////////////////////////////////////////////
// 본 클래스가 삭게할 때의 처리 부분
CMyTcpIp::~CMyTcpIp()
{
	m_fLoop = FALSE;
}

///////////////////////////////////////////////////////////////////////
// 서버로 호출하였을 때의 처리
BOOL CMyTcpIp::Create( UINT port )
{
	int one = 1;
	int	sizeOfLanBuf;
	struct linger	LINGER;

	m_ServerType = SERVER;

	// IP 와 PORT 설정
	m_SockaddrInternet.sin_addr.s_addr=htonl(INADDR_ANY);
	m_SockaddrInternet.sin_family=AF_INET;
	m_SockaddrInternet.sin_port=htons( port );

	// 소켓 생성
	m_Sock=socket(AF_INET,SOCK_STREAM,0);	

 	setsockopt(m_Sock, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(one));
	LINGER.l_onoff = TRUE;
	LINGER.l_linger = 0;		
	setsockopt(m_Sock, SOL_SOCKET, SO_LINGER, (char *)&LINGER, sizeof(LINGER));
	sizeOfLanBuf = 1;
	setsockopt(m_Sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));			// 98.10.22
	setsockopt(m_Sock, SOL_SOCKET, SO_SNDBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));
	setsockopt(m_Sock, SOL_SOCKET, SO_RCVBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));

	// 서버로서의 bind -> listen -> accept 처리
	if( ! bind( m_Sock, ( struct sockaddr*)& m_SockaddrInternet,sizeof(m_SockaddrInternet) ) ) {
		if( m_pThread == NULL ) {
			listen(m_Sock,5);
			// 랜 쓰레드 생성
			m_pThread = AfxBeginThread(LanReceiveThread, this);
		}
	}

	return TRUE;

}

///////////////////////////////////////////////////////////////////////
// 클라이언트로 호출하였을 때의 처리
BOOL CMyTcpIp::Create(char *pIPAddress, UINT port)
{
	int one = 1;
	int	sizeOfLanBuf;
	struct linger	LINGER;

	m_ServerType = CLIENT;

	// IP 와 PORT 설정
	m_SockaddrInternet.sin_addr.s_addr=inet_addr( pIPAddress );
	m_SockaddrInternet.sin_family=AF_INET;
	m_SockaddrInternet.sin_port=htons( port );

	// 소켓 생성
	m_Sock=socket(AF_INET,SOCK_STREAM,0);	
	LINGER.l_onoff = TRUE;
	LINGER.l_linger = 0;
	setsockopt(m_Sock, SOL_SOCKET, SO_LINGER, (char *)&LINGER, sizeof(LINGER));
	sizeOfLanBuf = 1;
	setsockopt(m_Sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));
	setsockopt(m_Sock, SOL_SOCKET, SO_SNDBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));
	setsockopt(m_Sock, SOL_SOCKET, SO_RCVBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf));

	// 랜 쓰레드 생성
	//if( m_pThread == NULL )
		m_pThread = AfxBeginThread(LanReceiveThread, this);

	return TRUE;

}

///////////////////////////////////////////////////////////////////////
// 랜 쓰레드
UINT CMyTcpIp::LanReceiveThread(LPVOID pParam) {
	int s;
	int addlen;
	CMyTcpIp *pThis = ( CMyTcpIp * ) pParam;
	fd_set writefd, readfd, exceptfd;
	struct timeval t;

	do {
		pThis->m_ConSock = -1;

		if( pThis->m_ServerType == CLIENT ) {
			// 소켓 생성
			pThis->m_ConSock = socket(AF_INET,SOCK_STREAM,0);

			// 랜 연결 시도
			while( SOCKET_ERROR == connect(pThis->m_ConSock,(sockaddr *) & pThis->m_SockaddrInternet, sizeof(pThis->m_SockaddrInternet) ) ) {
				Sleep( 100 );
			}
		}
		else {
			addlen = sizeof( pThis->m_SockaddrInternet );
			// 랜 소켓 인증
			pThis->m_ConSock = accept(pThis->m_Sock,(sockaddr *) & pThis->m_SockaddrInternet, & addlen );
		}

		pThis->Connect();

		t.tv_sec = 1L;
		t.tv_usec = 0L;

		do {
			FD_ZERO( & readfd );
			FD_ZERO( & writefd );
			FD_ZERO( & exceptfd );

			FD_SET( pThis->m_ConSock, & readfd );
			FD_SET( pThis->m_ConSock, & writefd );
			FD_SET( pThis->m_ConSock, & exceptfd );

			s = select( 0, & writefd, NULL, & exceptfd, NULL );
			if( s > 0 ) {
				// 소켓에서 수신되었는지를 검사 ? 이상이 있으면 쓰레드를 빠져나옴.
				if( FALSE == pThis->Receive() ) {
					break;
				}
				else {
					printf( "\n Pasue..." );
				}
			}

			if( pThis->m_bClose == TRUE ) {
				break;
			}

		}
		while( s != SOCKET_ERROR );

		pThis->Close();

	}
	while( true );

	pThis->m_pThread = NULL;

	// pThis->Create( 13030 );

	ExitThread( 0 );

	// AfxEndThread(0);

	return 0;
}

///////////////////////////////////////////////////////////////////////
// 랜 수신했을 때의 처리
BOOL CMyTcpIp::Receive(void)
{
	// 데이터 수신시의 처리
	int r, size=1024;

	r = recv( m_ConSock, (char *) _buffer, size, 0 );
	if( r > 0 ) {
		ReceiveMessage( _buffer, r );

	}
	else {
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMyTcpIp::Connect
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA-TFT, 2006-04-12 17:03:42
//
void CMyTcpIp::Connect()
{
	ConnectMessage( & m_SockaddrInternet );
	m_bClose = FALSE;
}

///////////////////////////////////////////////////////////////////////
// 랜이 닫았을 때의 처리
void CMyTcpIp::Close(void)
{

	closesocket(m_ConSock);
	DisConnectMessaage();
	m_ConSock = -1;
}

///////////////////////////////////////////////////////////////////////
// 랜으로 전송했을 떄의 처리
int CMyTcpIp::Send( char *pBuff, int size)
{
	int s;

	if( m_ConSock != -1 ) {
		BEModeChange( pBuff, size );
		if( m_bClose == 0 ) {
			s =send( m_ConSock, pBuff, size, 0 );
		}
		return s;
	}
	else {
		return -1;
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMyTcpIp::BEModeChange
// 반환되는 형  : void
// 함 수 인 자  : char *pTmp
// 함 수 인 자  : int size
// 함 수 설 명  : 
// 최 종 변 경  : SONATA-TFT, 2006-04-12 12:11:58
//
void CMyTcpIp::BEModeChange(char *pTmp, int size)
{
	int i;
	char swap;

	for( i=0 ; i < size / (int) sizeof(UINT) ; ++i ) {
		swap = *(pTmp+0);
		*(pTmp+0) = *(pTmp+3);
		*(pTmp+3) = swap;

		swap = *(pTmp+1);
		*(pTmp+1) = *(pTmp+2);
		*(pTmp+2) = swap;

		pTmp += sizeof(UINT);
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMyTcpIp::RequesetClose
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA-TFT, 2006-04-19 15:36:34
//
void CMyTcpIp::RequesetClose()
{
	m_bClose = TRUE;
}