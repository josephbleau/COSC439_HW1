#ifndef FLIGHTSERVER_H
#define FLIGHTSERVER_H

#include "UDPServer.h"
#include "FlightLoader.h"

class FlightServer : public UDPServer, public FlightLoader
{
public:
	FlightServer( const std::string& filename );
	~FlightServer();	

	bool RequestHandler( std::string request );
	void Run();
};

#endif
