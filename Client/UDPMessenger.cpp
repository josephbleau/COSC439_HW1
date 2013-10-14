#include "UDPMessenger.h"

UDPMessenger::UDPMessenger()
	: m_socket( -1 )
{
	m_sockServerInfo.sin_family = AF_INET;
	m_sockClientInfo.sin_family = AF_INET;
	inet_pton( AF_INET, "127.0.0.1", &m_sockClientInfo.sin_addr );
}
	

UDPMessenger::~UDPMessenger()
{
	if( m_socket != -1 )
	{
		close( m_socket );
	}
}

void UDPMessenger::SetupDestination( const std::string& ipaddr, int port )
{
	m_sockServerInfo.sin_port = htons(port);
	int result = inet_pton( AF_INET, ipaddr.c_str(),
                                &m_sockServerInfo.sin_addr );

	switch( result )
	{
		case 0: 
		{
			std::cerr << "Cannot setup destination, " 
                                  << "invalid address provided."
                                  << std::endl;
			break;
		}
		case -1:
		{
			std::cerr << "Cannot setup destination, "
			          << "invalid family address. "
				  << std::endl;

			break;
		}
		case 1:
		{
			std::cout << "Destination setup success. "
				  << std::endl;
		} 
	}
}

bool UDPMessenger::Initialize()
{
	m_socket = socket( PF_INET, SOCK_DGRAM, 0 );
	if( m_socket == -1 )
	{
		std::cerr << "Creating socket failed: " << errno << std::endl;
		return false;
	}

	socklen_t sockLen = sizeof(m_sockClientInfo);
	int result = bind( m_socket, (sockaddr*) &m_sockClientInfo, sockLen );
	
	return true;
}

std::string UDPMessenger::RecvMessage()
{
	char buffer[1024];
	int bufferLen = 1024;
	socklen_t sockLen = sizeof(m_sockServerInfo);		
	recvfrom( m_socket, buffer, bufferLen, 0, 
                  (sockaddr*) &m_sockServerInfo, &sockLen );

	return std::string(buffer);
}

void UDPMessenger::SendMessage( const std::string& message )
{
	if( m_socket == -1 )
	{
		std::cerr << "Cannot send message on an invalid socket" 
                          << std::endl;
	} 
	else
	{
		socklen_t sockLen = sizeof(m_sockServerInfo);
		sendto( m_socket, message.c_str(), message.size(), 0,
                        (sockaddr*) &m_sockServerInfo, sockLen );
	}
}


