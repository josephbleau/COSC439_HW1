#include "FlightServer.h"

#include "../Shared/MiscUtils.h"

#include <algorithm> // for remove_if
#include <locale> // for isspace

FlightServer::FlightServer( const std::string& filename )
	: UDPServer()
	, FlightLoader( filename )
{}

FlightServer::~FlightServer()
{}

bool FlightServer::RequestHandler( std::string request )
{
	size_t endMarker = request.find("|");
	request = request.substr(0, endMarker);

	// remove whitespace & tokenize
	std::remove_if( request.begin(), request.end(), isspace ); 
	std::vector<std::string> tokens = explode(request, ",");

	bool validFlight = FlightIDExists( tokens.at(0) );

	if( tokens.size() == 1 )
	{
		if( tokens.at(0).compare("FLIGHTINFO") == 0 )
		{
			std::string flightList = GetAllFlightIDs();
			Respond( "FLIGHTINFO," + flightList + "|" );
			return false;
		}
	}
	else if( tokens.size() == 2)
	{
		if( validFlight && tokens.at(1).compare("DETAILS") == 0 )
		{
			std::string row = RowAsString( tokens.at(0) );
			Respond( row + "|" );
			return false;
		}
	}
	else if( validFlight && tokens.size() == 3 )
	{
		std::stringstream ss;
		ss << tokens.at(2);
		int nTickets = 0;
		ss >> nTickets;

		int availSeats = 0;
		int prevAvailSeats = 0;

		std::stringstream response;

		if( tokens.at(1).compare("PURCHASEECON") == 0 )
		{	
			availSeats = m_data[tokens.at(0)].availEconSeats;
			prevAvailSeats = availSeats;

			if( availSeats >= nTickets )
				availSeats = m_data[tokens.at(0)].availEconSeats -= nTickets;
		}
		else if( tokens.at(1).compare("PURCHASEPREM") == 0 )
		{
			availSeats = m_data[tokens.at(0)].availPremSeats;
			prevAvailSeats = availSeats;

			if( availSeats >= nTickets )
				availSeats = m_data[tokens.at(0)].availPremSeats -= nTickets;
		}

		if( prevAvailSeats == availSeats  )
			response << tokens.at(0) << ",PURCHASERESPONSE,FAILURE,"
			 	 << availSeats << "|";
		else
			response << tokens.at(0) << ",PURCHASERESPONSE,SUCCESS|";

		Respond( response.str() );
		return false;
	}

	// if we haven't handled the request by now
	// it must have been an invalid request
	Respond( "MALFORMED_REQUEST|" );

	return false;
}

void FlightServer::Run()
{
	// In order to successfully pass a member function pointer to
	// std::function (a glorified wrapped & overloaded fptr) 
	// we need to use bind in order to include our instance. 
	// C++11 witch-craftery.
	using namespace std::placeholders;
	ProcessMessages( std::bind(&FlightServer::RequestHandler, this, _1), -1 );
}
