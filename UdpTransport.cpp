//@file:UdpTransport.cpp 
//@brief: 实现UDP传输的接口方法。
//@author: zhangmiao@oristartech.com
//date: 2012-08-02
#ifndef _UDPTRANSPORT_H_
#include "UdpTransport.h"
#endif

#include <errno.h>

using namespace std;

namespace udp
{

	const int BUFFERSIZE = 1024;

	// Class UdpTransport
	UdpTransport::UdpTransport():fd(-1) 
	{
		memset(&addr,0,sizeof(addr));
		memset(&addr_Recv,0,sizeof(addr_Recv));
		Init();
	}

	UdpTransport::~UdpTransport()
	{
		if(BeConnected())
		{
			net_close(fd);
			fd = -1;
		}

#if defined(_WIN32)
		WSACleanup();
#endif
	}

	int UdpTransport::SetAddr(const char *ip, const unsigned short port)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);
		return 0;
	}

	int UdpTransport::Create()
	{
		if(fd != -1)
		{
			net_close(fd);
			fd = -1;
		}

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		timeval timeo;
		timeo.tv_sec = MAXWAITTIME;
		timeo.tv_usec = 0;
		setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, SETSOCKOPT_OPTVAL_TYPE &timeo, sizeof(timeo));
		return 0;
	}

	int UdpTransport::Create(const char *ip, unsigned short port)
	{
		if(ip == NULL || port == 0)
			return -1;

		if(fd != -1)
		{
			net_close(fd);
			fd = -1;
		}

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		timeval timeo;
		timeo.tv_sec = MAXWAITTIME;
		timeo.tv_usec = 0;
		setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, SETSOCKOPT_OPTVAL_TYPE &timeo, sizeof(timeo));
		return 0;
	}

	bool UdpTransport::BeConnected()const
	{
		return (fd == -1) ? false : true;
	}

	int UdpTransport::Close()
	{
		if(BeConnected())
		{
			if( net_close(fd) == -1 ) 
			{
				fd = -1;
				return -1;
			}
			fd = -1;
		}
		return 0;
	}
	void UdpTransport::Init(void)
	{
#if defined(_WIN32)
		WORD wVersionRequested;
		WSADATA wsadata;
		int err;
		wVersionRequested = MAKEWORD(1,1);
		if ((err = WSAStartup(wVersionRequested,&wsadata)) != 0)
			fprintf(stderr,"Network failed to start: %d\n",err);
		/* Confirm that the Windows Sockets DLL supports 1.1.*/
		/* Note that if the DLL supports versions greater */
		/* than 1.1 in addition to 1.1, it will still return */
		/* 1.1 in wVersion since that is the version we */
		/* requested. */
		if ( LOBYTE( wsadata.wVersion ) != 1 ||
			HIBYTE( wsadata.wVersion ) != 1 ) 
		{
			/* Tell the user that we couldn't find a useable */
			/* winsock.dll. */
			WSACleanup( );
		} 
#endif
	}

	int UdpTransport::UdpRecv(char *buffer, int nSize, const int nSecs )
	{
		return ReceiveDatagram(buffer, nSize,(sockaddr*)&addr_Recv, nSecs);
	}
	int UdpTransport::ReceiveDatagram(char* buffer, const int nSize, LPSOCKADDR psa, const int nSecs)
	{
		//assert(buffer != NULL);
		//assert(fd != 0);
		if(buffer == NULL || fd == 0)
			return 0;

		timeval timeOut = {nSecs, 0};

		fd_set fdSet;
		FD_ZERO(&fdSet);
		FD_SET(fd, &fdSet);

		int result = select(fd+1, &fdSet, NULL, NULL, &timeOut);
		if(result < 0)
		{
			net_close(fd);
			fd = -1;
			return -1;
		}
		//"接收超时(Receive timeout)"
		if(result == 0)
		{
			//return 0;
			return -1;
		}

		/*int*/ socklen_t  nFromSize = sizeof(SOCKADDR);
		int nBytesReceived = recvfrom( fd, buffer, nSize, 0, psa, &nFromSize );
		if( nBytesReceived < 0 ) 
		{
			net_close(fd);
			fd = -1;
			return -1;
		}
		return nBytesReceived;
	}

	int UdpTransport::UdpSend(const char *buffer, const int nSize, const int nSecs )
	{
		return SendDatagram(buffer, nSize,(sockaddr*)&addr, nSecs);
	}
	int UdpTransport::SendDatagram(const char* buffer, const int nSize, LPCSOCKADDR psa, const int nSecs)
	{
		//assert(buffer != NULL);
		//assert(fd != 0);
		if(buffer == NULL || fd == 0)
			return 0;

		if(fd == -1)
			return -1;

		timeval timeOut = {nSecs, 0};

		fd_set fdSet;
		FD_ZERO(&fdSet);
		FD_SET(fd, &fdSet);

		int result = select(fd+1, NULL, &fdSet, NULL, &timeOut);
		if(result < 0)
		{
			net_close(fd);
			fd = -1;
			return -1;
		}
		//"接收超时(Receive timeout)"
		if(result == 0)
		{
			//return 0;
			return -1;
		}

		int nBytesSent = sendto(fd, buffer, nSize, 0, psa, sizeof(SOCKADDR));
		if( nBytesSent < 0 ) 
		{
			net_close(fd);
			fd = -1;
			return -1;
		}

		return nBytesSent;
	}

	int UdpTransport::Write(const char* buffer, const int nSize, const int nSecs)
	{
		int nBytesSent = 0;
		int nBytesThisTime;
		const char* pch1 = buffer;
		do {
			nBytesThisTime = UdpSend(pch1, nSize - nBytesSent, nSecs);
			nBytesSent += nBytesThisTime;
			pch1 += nBytesThisTime;
		} while(nBytesSent < nSize);
		return nBytesSent;
	}

};

