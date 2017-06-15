#if defined PRJ_BLINDWALK || !defined MODULAR

#include "Config/BlindWalkConfigurationLoader.h"

#include "BlindWalk/include/BlindWalkWorldObserver.h"
#include "BlindWalk/include/BlindWalkAgentObserver.h"
#include "BlindWalk/include/BlindWalkController.h"

#include "WorldModels/RobotWorldModel.h"


BlindWalkConfigurationLoader::BlindWalkConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

BlindWalkConfigurationLoader::~BlindWalkConfigurationLoader()
{
	//nothing to do
}

WorldObserver* BlindWalkConfigurationLoader::make_WorldObserver(World* wm)
{
	return new BlindWalkWorldObserver(wm);
}

RobotWorldModel* BlindWalkConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* BlindWalkConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new BlindWalkAgentObserver(wm);
}

Controller* BlindWalkConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new BlindWalkController(wm);
}


#endif
