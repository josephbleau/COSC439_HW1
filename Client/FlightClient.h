#ifndef FLIGHTCLIENT_H
#define FLIGHTCLIENT_H

#include <algorithm>
#include <map>
#include <sstream>
#include <string>

#include "../Shared/FlightInfo.h"

#include "UDPMessenger.h"

enum MenuState{ MAIN, PURCHASING, EXITING };

/* FlightClient is the main driver in our application. It extends
 * UDPMessenger to enable UDP send/receieving capabilities as well
 * as implements the fundamental functions our client needs to have.
 */

class FlightClient : public UDPMessenger
{	
private:
	std::map<std::string, FlightInfo> m_flightData;
	MenuState m_menuState;
	std::string m_lastInput;

public:
	FlightClient();
	~FlightClient();

	/* Parsing commands for main menu. */
	void doMainMenu();

	/* Parsing commands for our purchasing menu. */
	void doPurchasingMenu();

	/* Displays interpreted response from server for purchasing responses. */
	void doPrintParsePurchaseResponse(std::string& response) const;

	/* Override existing UDPMessenger's RecvMessage in order to provide
	 * a simple layer of packet parsing */
	std::string RecvMessage(); //override to provide some simple packet interpretation

	/* To be called from main, begins our programs main loop. */
	void Run(); 
};

#endif
