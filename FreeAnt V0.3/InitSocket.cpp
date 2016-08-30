///////////////////////////////////////////////////
// InitSocket.cpp : implementation file

#include "Stdafx.h"
#include "InitSocket.h"

inline CInitSocket::CInitSocket()
{
	// ≥ı ºªØWS2_32.dll
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = ::WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		exit(0);
	}
		
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 )
	{
		::WSACleanup( );
		exit(0); 
	}
}

inline CInitSocket::~CInitSocket()
{
	::WSACleanup();
}

void InitSocket()
{
	CInitSocket *initsock=new CInitSocket;
}