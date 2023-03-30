#ifndef SERVER_HPP
#define SERVER_HPP

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

class CServer
{
	// Constructor
	CServer();

	// Destructor
	~CServer();
};

#endif // SERVER_HPP
