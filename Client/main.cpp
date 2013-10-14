#include "FlightClient.h"

int main( int argc, char* argv[] )
{
	FlightClient client;
	if( !client.Initialize() )
	{
		return 1;
	}

	client.PrintHello();
	client.PrintMainMenu();

	client.Run();

	return 0;
}
