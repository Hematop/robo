#if defined PRJ_COMPASSWALK || !defined MODULAR

#include "Config/CompassWalkConfigurationLoader.h"

#include "CompassWalk/include/CompassWalkWorldObserver.h"
#include "CompassWalk/include/CompassWalkAgentObserver.h"
#include "CompassWalk/include/CompassWalkController.h"

#include "WorldModels/RobotWorldModel.h"


CompassWalkConfigurationLoader::CompassWalkConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

CompassWalkConfigurationLoader::~CompassWalkConfigurationLoader()
{
	//nothing to do
}

WorldObserver* CompassWalkConfigurationLoader::make_WorldObserver(World* wm)
{
	return new CompassWalkWorldObserver(wm);
}

RobotWorldModel* CompassWalkConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* CompassWalkConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new CompassWalkAgentObserver(wm);
}

Controller* CompassWalkConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new CompassWalkController(wm);
}


#endif
