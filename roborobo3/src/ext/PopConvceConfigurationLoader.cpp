#if defined PRJ_POPCONVCE || !defined MODULAR

#include "Config/PopConvceConfigurationLoader.h"

#include "PopConvce/include/PopConvceWorldObserver.h"
#include "PopConvce/include/PopConvceAgentObserver.h"
#include "PopConvce/include/PopConvceController.h"

#include "WorldModels/RobotWorldModel.h"

PopConvceConfigurationLoader::PopConvceConfigurationLoader()
{
}

PopConvceConfigurationLoader::~PopConvceConfigurationLoader()
{
	//nothing to do
}

WorldObserver* PopConvceConfigurationLoader::make_WorldObserver(World* wm)
{
	return new PopConvceWorldObserver(wm);
}

RobotWorldModel* PopConvceConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* PopConvceConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new PopConvceAgentObserver(wm);
}

Controller* PopConvceConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new PopConvceController(wm);
}

#endif
