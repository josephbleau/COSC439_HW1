#include "FlightClient.h"

FlightClient::FlightClient()
{
	// setup destination info
	SetupDestination("127.0.0.1", 50398);
}

FlightClient::~FlightClient()
{}

void FlightClient::PrintHello() const
{
	std::cout << "Welcome to the Flight Booking Server...\n"
                  << "Written by Joseph Bleau" << std::endl;
}

void FlightClient::PrintMainMenu() const
{
	std::cout << "\n\nMAIN MENU\n\n\t[1]: View available flights.\n\t"
		  << "[2]: Purchase tickets.\n\t[3]: Exit" << std::endl;
}

void FlightClient::PrintPurchasingMenu() const
{
	std::cout << "\n\nPURCHASING MENU\n\n\t[1]: Purchase a ticket "
                  << "in economy class.\n\t[2]: Purchase a ticket in "
                  << "premium class.\n\t[3]: Return to previous menu."
                  << std::endl;
}

void FlightClient::Run()
{
	// program input loop
	std::string input;
	bool running = true;	
	while( running && std::getline( std::cin, input ) )
	{
		// exit
		if(input.compare("3") == 0)
			running = false;
		else
		{
			SendMessage( input );
			std::cout << RecvMessage() << std::endl;
		}
	}
}
