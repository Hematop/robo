/*
 * MedeaConfigurationLoader.h
 */

#ifndef CUSTOMBOIDSCONFIGURATIONLOADER_H
#define CUSTOMBOIDSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class CustomBoidsConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		CustomBoidsConfigurationLoader();
		~CustomBoidsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
