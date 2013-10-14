#ifndef UDPMESSENGER_H
#define UDPMESSENGER_H

#include <iostream>
#include <string>

#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

class UDPMessenger 
{
private:
	int m_socket;

	sockaddr_in m_sockClientInfo;
	sockaddr_in m_sockServerInfo;

public:
	UDPMessenger();
	~UDPMessenger();

	bool Initialize(); 
	std::string RecvMessage();
	void SendMessage( const std::string& message );
	void SetupDestination( const std::string& ipaddr, int port );
};

#endif
