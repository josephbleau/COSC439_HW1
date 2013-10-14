#ifndef FLIGHTLOADER_H
#define FLIGHTLOADER_H

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct FlightInfo
{
	int premiumCapacity;
	int availPremSeats;
	int econCapacity;
	int availEconSeats;
};

class FlightLoader
{
protected:
	std::map< std::string, FlightInfo > m_data;
	std::string m_filename;

public: 
	FlightLoader( const std::string& filename );
	~FlightLoader();

	// returns true if this flight exists, else false
	bool FlightIDExists( const std::string& id ) const;

	// returns comma-delimted list of flights
	std::string GetAllFlightIDs() const; 

	// return a flight entry as a string
	std::string RowAsString( const std::string& id );
};

#endif
