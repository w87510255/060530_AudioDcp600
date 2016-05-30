//@file:UdpTransport.h  
//@brief: 实现UDP传输的接口方法。
//@author: zhangmiao@oristartech.com
//date: 2012-08-02
#ifndef _UDPTRANSPORT_H_
#define _UDPTRANSPORT_H_

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <assert.h>

#if defined(_WIN32)
#include <winsock2.h>
typedef int socklen_t;
#define net_close closesocket
#define MSG_NOSIGNAL 0
#else
#define net_close close
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#if defined(_WIN32)
#define SETSOCKOPT_OPTVAL_TYPE (const char *)
#else
#define SETSOCKOPT_OPTVAL_TYPE (void *)
#endif

typedef struct sockaddr* LPSOCKADDR;
typedef const struct sockaddr* LPCSOCKADDR;
typedef struct sockaddr SOCKADDR;

namespace udp
{
	const int MAXWAITTIME = 10;

	class UdpTransport
	{
		void Init();

	public:
		UdpTransport();
		~UdpTransport();

		int Create(const char *ip, unsigned short port);
		int Create();

		int SetAddr(const char *ip, const unsigned short port);

		bool BeConnected()const;

		int Close();

		int Write(const char* buffer, const int nSize, const int nSecs = MAXWAITTIME );
		int UdpRecv(char *buffer, int nSize, const int nSecs = MAXWAITTIME);

		int UdpSend(const char *buffer, const int nSize, const int nSecs = MAXWAITTIME);

		int SendDatagram(const char* buffer, const int nSize, LPCSOCKADDR psa, 
			const int nSecs);
		int ReceiveDatagram(char* buffer, const int nSize, LPSOCKADDR psa, 
			const int nSecs);

	private:
		int fd;
		sockaddr_in addr;
		sockaddr_in addr_Recv;
	};

};

#endif//_UDPTRANSPORT_H_
