#ifndef FLIGHTLOADER_H
#define FLIGHTLOADER_H

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

	public: 
		FlightLoader( const std::string& filename );
		~FlightLoader();

		// returns true if this flight exists, else false
		bool FlightIDExists( const std::string& id ) const;
};

#endif
