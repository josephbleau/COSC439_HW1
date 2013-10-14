#ifndef FLIGHTSERVER_H
#define FLIGHTSERVER_H

#include "UDPServer.h"
#include "FlightLoader.h"

class FlightServer : public UDPServer, public FlightLoader
{
public:
	FlightServer(std::string filename);
	~FlightServer();	
};

#endif
