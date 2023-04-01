#include "tcpserver.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CTCPServer::CTCPServer(int port)
{
#if defined(WIN32) && !defined(UNIX)
	// --
#endif
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CTCPServer::~CTCPServer()
{
	// RAII
	// --
}
