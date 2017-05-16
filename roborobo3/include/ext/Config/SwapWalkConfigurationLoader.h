/*
 * SwapWalkConfigurationLoader.h
 */

#ifndef SWAPWALKCONFIGURATIONLOADER_H
#define	SWAPWALKCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class SwapWalkConfigurationLoader : public ConfigurationLoader
{
	public:
		SwapWalkConfigurationLoader();
		~SwapWalkConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
