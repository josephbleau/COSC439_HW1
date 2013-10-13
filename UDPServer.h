#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <iostream>
#include <functional>
#include <string>
#include <WinSock2.h>

class UDPServer
{
private:
	SOCKET m_socket;
	sockaddr_in m_sockServerInfo;
	sockaddr_in m_sockClientInfo; // Only the last client to message us so we can respond
	int m_lastError;

public:
	UDPServer();
	~UDPServer();

	bool Initialize();
	int GetLastError();

	// ProcessMessages will block until nMessages are recieved (or if -1 is passed,
	// it will run indefinitely.) It's first parameter is a function which will be
	// called for each message received, and passed to it will be the message 
	// in the form of an std::string. It's simple to think of std::function as 
	// a simple c-function pointer, but with some more capabilities (can handle lambdas,
	// and pointer to member functions.)
	//
	// The recieve loop will also end early if the processing function returns true.
	// This applies to both indefinite and definite calls.
	void ProcessMessages( std::function<bool(std::string)> func, int nMessages = -1 );
};

#endif