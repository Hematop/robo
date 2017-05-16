/*
 * PopConvceConfigurationLoader.h
 */

#ifndef POPCONVCECONFIGURATIONLOADER_H
#define POPCONVCECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class PopConvceConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		PopConvceConfigurationLoader();
		~PopConvceConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
