#if defined PRJ_MOVESWAP || !defined MODULAR

#include "Config/MoveSwapConfigurationLoader.h"

#include "MoveSwap/include/MoveSwapWorldObserver.h"
#include "MoveSwap/include/MoveSwapAgentObserver.h"
#include "MoveSwap/include/MoveSwapController.h"

#include "WorldModels/RobotWorldModel.h"


MoveSwapConfigurationLoader::MoveSwapConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

MoveSwapConfigurationLoader::~MoveSwapConfigurationLoader()
{
	//nothing to do
}

WorldObserver* MoveSwapConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MoveSwapWorldObserver(wm);
}

RobotWorldModel* MoveSwapConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* MoveSwapConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new MoveSwapAgentObserver(wm);
}

Controller* MoveSwapConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new MoveSwapController(wm);
}


#endif
