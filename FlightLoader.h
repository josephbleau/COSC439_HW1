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
	private:
		std::map< std::string, FlightInfo > m_data;

	public: 
		FlightLoader( std::string filename );
		~FlightLoader();
};

#endif
