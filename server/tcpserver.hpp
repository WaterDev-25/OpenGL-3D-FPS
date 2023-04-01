#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
#else
/* Error, both can't be defined or undefined same time */
#endif

#include <iostream>

class CTCPServer
{
public:
	// Constructor
	CTCPServer(int port);

	// Destructor
	~CTCPServer();
};

#endif // TCPSERVER_HPP
