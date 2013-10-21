#ifndef FLIGHTSERVER_H
#define FLIGHTSERVER_H

#include "UDPServer.h"
#include "FlightLoader.h"

/* FlightServer is the core driver of our program. It extends FlightLoader
 * in order to inherit it's Flight DB parsing and it extends UDPServer
 * in order to inherit it's server capabilities (recieve message loop.)
 * It's primary contribution is the implementation of the request handler
 * which is passed every string that comes in via our UDPServer and parses it.
 */
class FlightServer : public UDPServer, public FlightLoader
{
public:
	FlightServer( const std::string& filename );
	~FlightServer();	

	/* Main processing method for our server. Is called by
	 * UDPServer's recieving loop for every packet that is
	 * recieved.
	 */
	bool RequestHandler( std::string request );

	/* To be called by main, starts our server. */
	void Run();
};

#endif
