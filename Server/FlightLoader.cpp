#include "FlightLoader.h"

#include "../Shared/MiscUtils.h"

FlightLoader::FlightLoader( const std::string& filename )
	: m_data()
	, m_filename( filename )
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
	// write changes out
	std::ofstream outfile;
	outfile.open( m_filename );
	
	if( outfile.is_open() )
	{
		// write helper comment at top
		outfile << "#, Flight ID, Prem Capacity, Avail Prem Seats, "
                        << "Econ Capacity, Avail Econ Seats" << std::endl;

		// write out rows
		for( auto i = m_data.begin(); 
		     i != m_data.end();
		     ++i )
		{
			std::string row = RowAsString( i->first );
			outfile << row << std::endl;
			std::cout << row << " written." << std::endl;
		}

		outfile.close();
	}
	else
	{
		std::cerr << "Couldn't open " << m_filename << " for writing. Changes not saved.";
	}
}

bool FlightLoader::FlightIDExists( const std::string& id ) const
{
	for( auto i = m_data.begin(); 
             i != m_data.end();
	     ++i )
	{
		if( i->first.compare( id ) == 0 )
			return true;
	}	

	return false;
}

std::string FlightLoader::GetAllFlightIDs() const
{
	std::string ret;

	for( auto i = m_data.begin(); 
             i != m_data.end();
	     ++i )
	{
		ret += i->first + ",";
	}
	
	// remove last unneeded ","
	ret.erase( ret.end()-1 );

	return ret;
}

std::string FlightLoader::RowAsString( const std::string& id )
{
	if( !FlightIDExists( id ) )
		return "";

	std::stringstream ss;
	FlightInfo& info = m_data[id];

	ss << id << "," << info.premiumCapacity << "," << info.availPremSeats 
           << "," << info.econCapacity << "," << info.availEconSeats;

	return ss.str();
}

