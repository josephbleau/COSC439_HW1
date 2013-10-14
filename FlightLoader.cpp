#include "FlightLoader.h"

#include "MiscUtils.h"

FlightLoader::FlightLoader( std::string filename )
	: m_data()
{
	std::ifstream flightDB( filename );

	if( !flightDB.good())
	{
		std::cerr << "Unable to load flight database: " << filename << std::endl;
	}

	std::string line;
	while( !flightDB.eof() )
	{
		std::getline( flightDB, line );
		std::vector< std::string > tokens = explode( line, "," );

		if(line.length() == 0 || tokens.at(0) == "#" ) continue;
		else if( tokens.size() != 5 ) 
		{
			std::cerr << "Error in " << filename << " malformed line: " 
                                  << line << std::endl;
		}
		else
		{
			std::stringstream ss; // stringstream for conversions
			std::string key = tokens.at(0);
			tokens.erase( tokens.begin() ); // Erase first element (the key)
			
			m_data[key]; // default initialize a new FlightInfo

			ss << tokens[1];
			ss >> m_data[key].premiumCapacity;
			ss.clear();

			ss << tokens[2];
			ss >> m_data[key].availPremSeats;
			ss.clear();
	
			ss << tokens[3];
			ss >> m_data[key].econCapacity;
			ss.clear();

			ss << tokens[4];
			ss >> m_data[key].availEconSeats;
			
			std::cout << "Flight " << key << " loaded." << std::endl;
		}
	}
}

FlightLoader::~FlightLoader()
{
}
