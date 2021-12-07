// MyTcpIp.h: interface for the CMyTcpIp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTCPIP_H__492EE6F0_FF4F_45FC_9636_54E5B9800190__INCLUDED_)
#define AFX_MYTCPIP_H__492EE6F0_FF4F_45FC_9636_54E5B9800190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock.h>

enum { SERVER=0, CLIENT };

class CMyTcpIp  
{
private:
	sockaddr_in m_SockaddrInternet;
	SOCKET m_Sock;
	SOCKET m_ConSock;
	int m_ServerType;
	char _buffer[1024];
	BOOL m_bClose;
	
protected:
	BOOL m_fLoop;
	CWinThread* m_pThread;
	
public:
	static UINT LanReceiveThread(LPVOID pParam);

public:
	void RequesetClose();
	void Connect();
	void BEModeChange(char *pTmp, int size);
	virtual void DisConnectMessaage()=0;
	virtual void ConnectMessage( sockaddr_in *pSockaddrInternet )=0;
	virtual void ReceiveMessage( char *pBuff, int length )=0;
	BOOL Receive();
	int Send( char *pBuff, int size);
	void Close(void);
	BOOL Create( UINT port );
	BOOL Create( char *pIPAddress, UINT port );
	CMyTcpIp();
	virtual ~CMyTcpIp();

};

#endif // !defined(AFX_MYTCPIP_H__492EE6F0_FF4F_45FC_9636_54E5B9800190__INCLUDED_)
