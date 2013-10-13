#include "UDPServer.h"

UDPServer::UDPServer()
	: m_socket( INVALID_SOCKET )
{
#ifdef _WIN32
	m_sockServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
	m_sockServerInfo.sin_addr = inet_aton("127.0.0.1");
#endif
	m_sockServerInfo.sin_family = AF_INET;
	m_sockServerInfo.sin_port = htons(50398);
	ZeroMemory( &m_sockServerInfo.sin_zero, sizeof(m_sockServerInfo.sin_zero) );
}

UDPServer::~UDPServer()
{
	closesocket( m_socket );
}

bool UDPServer::Initialize()
{
	// Attempt to create reate an UDP socket
	m_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	if( m_socket == INVALID_SOCKET )
	{
		m_lastError = WSAGetLastError();
		return false;
	}
	
	// Attempt to bind a port
	int result = bind( m_socket, (SOCKADDR*) &m_sockServerInfo, sizeof(m_sockServerInfo) ); 
	if( result == SOCKET_ERROR )
	{
		m_lastError = WSAGetLastError();
		return false;
	}

	return true;
}

int UDPServer::GetLastError(){ return m_lastError; }

void UDPServer::ProcessMessages( std::function<bool(std::string)> fun, int nMessages )
{
	char buffer[1024];
	int bufferLen = 1024;
	int clientSockInfoSize = sizeof(m_sockClientInfo);
	bool quitEarly = false;

	while( !quitEarly && (nMessages < 0 || nMessages--) )
	{
		recvfrom( m_socket, buffer, bufferLen, 0, (SOCKADDR*) &m_sockClientInfo, &clientSockInfoSize ); 
		quitEarly = fun( buffer );
	}
}