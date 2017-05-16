#if defined PRJ_SWAPWALK || !defined MODULAR

#include "Config/SwapWalkConfigurationLoader.h"

#include "SwapWalk/include/SwapWalkWorldObserver.h"
#include "SwapWalk/include/SwapWalkAgentObserver.h"
#include "SwapWalk/include/SwapWalkController.h"

#include "WorldModels/RobotWorldModel.h"


SwapWalkConfigurationLoader::SwapWalkConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

SwapWalkConfigurationLoader::~SwapWalkConfigurationLoader()
{
	//nothing to do
}

WorldObserver* SwapWalkConfigurationLoader::make_WorldObserver(World* wm)
{
	return new SwapWalkWorldObserver(wm);
}

RobotWorldModel* SwapWalkConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* SwapWalkConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new SwapWalkAgentObserver(wm);
}

Controller* SwapWalkConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new SwapWalkController(wm);
}


#endif
