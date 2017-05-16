#if defined PRJ_BOIDSEE || !defined MODULAR

#include "Config/BoidsEEConfigurationLoader.h"

#include "BoidsEE/include/BoidsEEWorldObserver.h"
#include "BoidsEE/include/BoidsEEAgentObserver.h"
#include "BoidsEE/include/BoidsEEController.h"

#include "WorldModels/RobotWorldModel.h"

BoidsEEConfigurationLoader::BoidsEEConfigurationLoader()
{
}

BoidsEEConfigurationLoader::~BoidsEEConfigurationLoader()
{
	//nothing to do
}

WorldObserver* BoidsEEConfigurationLoader::make_WorldObserver(World* wm)
{
	return new BoidsEEWorldObserver(wm);
}

RobotWorldModel* BoidsEEConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* BoidsEEConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new BoidsEEAgentObserver(wm);
}

Controller* BoidsEEConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new BoidsEEController(wm);
}

#endif
