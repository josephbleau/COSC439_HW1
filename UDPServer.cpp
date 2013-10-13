#include "UDPServer.h"

UDPServer::UDPServer()
	: m_socket( -1 )
{
	m_sockServerInfo.sin_family = AF_INET;
	m_sockServerInfo.sin_port = htons( 50398 );
	inet_pton( AF_INET, "127.0.0.1", &m_sockServerInfo.sin_addr );

	memset( &m_sockServerInfo.sin_zero, 0, sizeof(m_sockServerInfo.sin_zero) );
}

UDPServer::~UDPServer()
{
	close( m_socket );
}

bool UDPServer::Initialize()
{
	// Attempt to create reate an UDP socket
	m_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	if( m_socket == -1 )
	{
		m_lastError = errno;
		return false;
	}
	
	// Attempt to bind a port
	int result = bind( m_socket, (sockaddr*) &m_sockServerInfo, sizeof(m_sockServerInfo) ); 
	if( result == -1 )
	{
		m_lastError = errno;
		return false;
	}

	return true;
}

int UDPServer::GetLastError(){ return m_lastError; }

void UDPServer::ProcessMessages( std::function< bool(std::string) > fun, int nMessages )
{
	char buffer[1024];
	int bufferLen = 1024;
	socklen_t clientSockInfoSize = sizeof(m_sockClientInfo);
	bool quitEarly = false;

	while( !quitEarly && (nMessages < 0 || nMessages--) )
	{
		recvfrom( m_socket, buffer, bufferLen, 0, (sockaddr*) &m_sockClientInfo, &clientSockInfoSize ); 
		quitEarly = fun( buffer );
	}
}
