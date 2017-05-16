#if defined PRJ_CUSTOMBOIDS || !defined MODULAR

#include "Config/CustomBoidsConfigurationLoader.h"

#include "CustomBoids/include/CustomBoidsWorldObserver.h"
#include "CustomBoids/include/CustomBoidsAgentObserver.h"
#include "CustomBoids/include/CustomBoidsController.h"

#include "WorldModels/RobotWorldModel.h"

CustomBoidsConfigurationLoader::CustomBoidsConfigurationLoader()
{
}

CustomBoidsConfigurationLoader::~CustomBoidsConfigurationLoader()
{
	//nothing to do
}

WorldObserver* CustomBoidsConfigurationLoader::make_WorldObserver(World* wm)
{
	return new CustomBoidsWorldObserver(wm);
}

RobotWorldModel* CustomBoidsConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* CustomBoidsConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new CustomBoidsAgentObserver(wm);
}

Controller* CustomBoidsConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new CustomBoidsController(wm);
}

#endif
