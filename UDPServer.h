#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <iostream>
#include <functional>
#include <string>
#include <string.h> // for memset

#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class UDPServer
{
private:
	int m_socket;
	sockaddr_in m_sockServerInfo;
	sockaddr_in m_sockClientInfo; // Only the last client to message us so we can respond
	int m_lastError;

public:
	UDPServer();
	~UDPServer();

	bool Initialize();
	int GetLastError();

	void ProcessMessages( std::function< bool(std::string) > func, int nMessages = -1 );
	void Respond( const std::string& response );
};

#endif
