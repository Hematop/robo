#if defined PRJ_COOKIERW || !defined MODULAR

#include "Config/CookieRWConfigurationLoader.h"

#include "CookieRW/include/CookieRWWorldObserver.h"
#include "CookieRW/include/CookieRWAgentObserver.h"
#include "CookieRW/include/CookieRWController.h"

#include "WorldModels/RobotWorldModel.h"


CookieRWConfigurationLoader::CookieRWConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

CookieRWConfigurationLoader::~CookieRWConfigurationLoader()
{
	//nothing to do
}

WorldObserver* CookieRWConfigurationLoader::make_WorldObserver(World* wm)
{
	return new CookieRWWorldObserver(wm);
}

RobotWorldModel* CookieRWConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* CookieRWConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new CookieRWAgentObserver(wm);
}

Controller* CookieRWConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new CookieRWController(wm);
}


#endif
