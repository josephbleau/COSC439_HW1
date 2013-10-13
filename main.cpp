#include <iostream>

#include "UDPServer.h"

bool echo(std::string s)
{
	std::cout << s << std::endl;

	return false; // Don't quit early.
}

int main( int argc, char* argv[] )
{
	UDPServer server;
	if( server.Initialize() == false )
	{
		std::cerr << "Server failed to initialize: " << server.GetLastError() << std::endl;
		return 1;
	}

	// Demonstrate power of ProcessMessages, echo two messages and exit.
	server.ProcessMessages( &echo, 2 );

	return 0;
}
