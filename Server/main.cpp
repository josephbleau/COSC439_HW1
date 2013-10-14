#include <iostream>

#include "FlightServer.h"

int main( int argc, char* argv[] )
{
	FlightServer flightServer("flightdb.txt");
	if( flightServer.Initialize() == false )
	{
		std::cerr << "Error initializing flight server: " 
                          << flightServer.GetLastError();

		return 1;
	}

	flightServer.Run();

	return 0;
}
