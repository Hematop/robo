#if defined PRJ_TESTBOIDS || !defined MODULAR

#include "Config/TestBoidsConfigurationLoader.h"

#include "TestBoids/include/TestBoidsWorldObserver.h"
#include "TestBoids/include/TestBoidsAgentObserver.h"
#include "TestBoids/include/TestBoidsController.h"

#include "WorldModels/RobotWorldModel.h"

TestBoidsConfigurationLoader::TestBoidsConfigurationLoader()
{
}

TestBoidsConfigurationLoader::~TestBoidsConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TestBoidsConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TestBoidsWorldObserver(wm);
}

RobotWorldModel* TestBoidsConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TestBoidsConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TestBoidsAgentObserver(wm);
}

Controller* TestBoidsConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TestBoidsController(wm);
}

#endif
