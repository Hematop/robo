/*
 * MedeaConfigurationLoader.h
 */

#ifndef TESTBOIDSCONFIGURATIONLOADER_H
#define TESTBOIDSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class TestBoidsConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		TestBoidsConfigurationLoader();
		~TestBoidsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
