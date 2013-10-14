#ifndef FLIGHTCLIENT_H
#define FLIGHTCLIENT_H

#include "UDPMessenger.h"

class FlightClient : public UDPMessenger
{	
public:
	FlightClient();
	~FlightClient();

	void PrintHello() const;
	void PrintMainMenu() const;
	void PrintPurchasingMenu() const;

	void Run(); 
};

#endif