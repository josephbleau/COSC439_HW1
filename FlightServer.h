#ifndef FLIGHTSERVER_H
#define FLIGHTSERVER_H

#include "UDPServer.h"
#include "FlightLoader.h"

class FlightServer : public UDPServer, public FlightLoader
{
private:
	std::string m_messageBuffer;
	bool m_messageTruncated;

public:
	FlightServer( const std::string& filename );
	~FlightServer();	

	// returns comma-delimted list of flights
	std::string GetAllFlightIDs() const; 

	bool RequestHandler( std::string request );
	void Run();
};

#endif
