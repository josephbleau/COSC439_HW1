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
	virtual ~UDPMessenger();

	bool Initialize();

	/* Basically a recvfrom wrapper that checks for packets
	 * against who we have stored in m_sockServerInfo and
	 * returns it as a string instead of a char[] buffer. */
	virtual std::string RecvMessage();

	/* Enables us to send messages to our destination in the
	 * form of an std::string. */
	void SendMessage( const std::string& message );

	/* Allows us to specify the servers address and port. */
	void SetupDestination( const std::string& ipaddr, int port );
};

#endif
