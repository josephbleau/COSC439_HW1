#include "FlightServer.h"

FlightServer::FlightServer( std::string filename )
	: UDPServer()
	, FlightLoader(filename)
{
}

FlightServer::~FlightServer()
{
}
