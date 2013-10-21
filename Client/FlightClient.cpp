#include "FlightClient.h"

#include "../Shared/MiscUtils.h"

FlightClient::FlightClient()
  : m_flightData()
  , m_menuState( MAIN )
  , m_lastInput()
{
	// setup destination info
	SetupDestination("127.0.0.1", 50398);

	std::cout << "Welcome to the Flight Booking Server...\n"
                  << "Written by Joseph Bleau" << std::endl;
}

FlightClient::~FlightClient()
{}

void FlightClient::doMainMenu()
{
	std::cout << "\nMAIN MENU\n\t[1]: View available flights.\n\t"
		  << "[2]: Purchase tickets.\n\t[3]: Exit" << std::endl;
	std::cout << "Select: ";
	std::getline( std::cin, m_lastInput );

	if( m_lastInput.compare("3") == 0 )
		m_menuState = EXITING;
	else if( m_lastInput.compare("1") == 0 )
	{
		std::string message = "FLIGHTINFO|";
		SendMessage(message);
		std::string response = RecvMessage();
		std::vector<std::string> flights = explode(response,",");

		if(flights.size() > 1 )
		{
			std::cout << "\nServer has responded, here are the current flight's."
					  << std::endl;
			flights.erase(flights.begin());

			for( auto& flight : flights )
			{
				std::cout << "\t" << flight << std::endl;
			}
		}
		else if(flights.size() == 1)
		{
			std::cout << "There are no available flights." << std::endl;
		}
		else
		{
			std::cout << "There was a communication error, please try again." << std::endl;
		}
	}
	else if( m_lastInput.compare("2") == 0 )
	{
		m_menuState = PURCHASING;
	}
	else
	{
		std::cout << "Invalid menu selection." << std::endl;
	}
}

void FlightClient::doPurchasingMenu()
{
	std::cout << "\nPURCHASING MENU\n\t[1]: Purchase a ticket "
                  << "in economy class.\n\t[2]: Purchase a ticket in "
                  << "premium class.\n\t[3]: Return to previous menu."
                  << std::endl;
	std::cout << "Select: ";
	std::getline( std::cin, m_lastInput );

	if( m_lastInput.compare("3") == 0 )
	{
		m_menuState = MAIN;
	}
	else if( m_lastInput.compare("2") == 0 ||
			 m_lastInput.compare("1") == 0 )
	{
		std::string howMuchInput;
		std::string flightInput;
		int numTickets = -1;

		std::cout << "Which flight? ";
		std::getline( std::cin, flightInput );

		std::cout << "How many tickets? ";
		std::getline( std::cin, howMuchInput );

		std::stringstream ss(howMuchInput);
		ss >> numTickets;

		if(numTickets < 1)
		{
			std::cout << "Invalid input for number of tickets." << std::endl;
			return;
		}

		std::string flightType = "";
		if( m_lastInput.compare("2") == 0 )
			flightType = "PURCHASEPREM";
		else
			flightType = "PURCHASEECON";

		SendMessage(flightInput + "," + flightType + "," + ss.str() + "|" );
		std::string response = RecvMessage();

		if(response.compare("MALFORMED_REQUEST") != 0)
			doPrintParsePurchaseResponse(response);
		else
			std::cout << "The flight you have selected does not exist." << std::endl;
	}
	else
	{
		std::cout << "Invalid selection. " << std::endl;
	}
}

void FlightClient::doPrintParsePurchaseResponse( std::string& response ) const
{
	std::vector<std::string> components = explode(response,",");
	if(components.at(1).compare("PURCHASERESPONSE") == 0)
	{
		if(components.at(2).compare("SUCCESS") == 0)
			std::cout << "Purchase was successful." << std::endl;
		else if(components.at(2).compare("FAILURE") == 0)
		{
			std::cout << "Purchase was a failure there are only " << components.at(3)
					  << " available for that flight." << std::endl;
		}
	}
}

std::string FlightClient::RecvMessage()
{
	std::string response = UDPMessenger::RecvMessage();

	size_t endMarker = response.find("|");
	response = response.substr(0, endMarker);

	// remove whitespace & tokenize
	std::remove_if( response.begin(), response.end(), isspace );

	return response;
}

void FlightClient::Run()
{
	bool running = true;

	while( running)
	{
		switch( m_menuState )
		{
			case MAIN: { doMainMenu(); break; }
			case PURCHASING: { doPurchasingMenu(); break; }
			case EXITING:{ running = false; break; }
		};
	}
}
