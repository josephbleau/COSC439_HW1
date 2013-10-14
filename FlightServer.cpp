#include "FlightServer.h"

#include "MiscUtils.h"

#include <algorithm> // for remove_if
#include <locale> // for isspace

FlightServer::FlightServer( const std::string& filename )
	: UDPServer()
	, FlightLoader( filename )
	, m_messageBuffer()
	, m_messageTruncated( false )
{
}

FlightServer::~FlightServer()
{
}


std::string FlightServer::GetAllFlightIDs() const
{
	std::string ret;

	for( auto i = m_data.begin(); 
             i != m_data.end();
	     ++i )
	{
		ret += i->first + ",";
	}
	
	// remove last unneeded ","
	ret.erase( ret.end()-1 );

	return ret;
}

bool FlightServer::RequestHandler( std::string request )
{
	// find the end of the message (messages end with |)
	// if no end is found assume the next message is
	// a continuation of this one.

	size_t endMarker = request.find("|");
	if( endMarker == std::string::npos )
	{
		m_messageBuffer.append( request );
		m_messageTruncated = true;
		return false;
	}

	// prepend previously truncated message
	if( m_messageTruncated ) 
		request.insert( 0, m_messageBuffer );

	m_messageBuffer.clear();

	request = request.substr(0, endMarker);

	// remove whitespace & tokenize
	std::remove_if( request.begin(), request.end(), isspace ); 
	std::vector<std::string> tokens = explode(request, ",");

	if( tokens.at(0).compare("FLIGHTINFO") == 0 )
	{
		m_messageTruncated = false;
		std::string flightList = GetAllFlightIDs();
		Respond( "FLIGHTINFO," + flightList );
	}
	else if( FlightIDExists( tokens.at(0) ) )
	{
		// request began with valid flight id
		m_messageTruncated = false;
	}

	return false;
}

void FlightServer::Run()
{
	// In order to successfully pass a member function pointer to
	// std::function (a glorified wrapped & overloaded fptr) 
	// we need to use bind in order to include our instance. 
	// C++11 witch-craftery.
	using namespace std::placeholders;
	ProcessMessages( std::bind(&FlightServer::RequestHandler, this, _1), 3 );	
}
