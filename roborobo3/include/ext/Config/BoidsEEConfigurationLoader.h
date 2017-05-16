/*
 * BoidsEEConfigurationLoader.h
 */

#ifndef BOIDSEECONFIGURATIONLOADER_H
#define BOIDSEECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class BoidsEEConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		BoidsEEConfigurationLoader();
		~BoidsEEConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
