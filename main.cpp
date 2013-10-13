#ifdef _WIN32
	#include <WinSock2.h>
#endif

#include <iostream>

#include "UDPServer.h"

bool echo(std::string s)
{
	std::cout << s << std::endl;

	return false; // Don't quit early.
}

int main( int argc, char* argv )
{

#ifdef _WIN32
	// Initialize winsock
	WSADATA wsaData;
	int result = WSAStartup( MAKEWORD(2,2), &wsaData );

	if( result != 0 )
	{
		std::cerr << "WSAStartup failed: " << result << std::endl;
		return 1;
	}

#endif

	UDPServer server;
	if( server.Initialize() == false )
	{
		std::cerr << "Server failed to initialize: " << server.GetLastError() << std::endl;
		return 1;
	}

	// Demonstrate power of ProcessMessages, echo two messages and exit.
	server.ProcessMessages( &echo, 2 );

	WSACleanup();
	return 0;
}