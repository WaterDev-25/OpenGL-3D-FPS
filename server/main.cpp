#include "config.hpp"
#include "tcpserver.hpp"

int main(int argc, char** argv)
{
	// Initialize config
	CConfig config("server/config.json");

	// Initialize game server
	CTCPServer server(config.GetPort());

	return 0;
}
