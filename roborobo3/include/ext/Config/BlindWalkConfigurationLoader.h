/*
 * BLINDWalkConfigurationLoader.h
 */

#ifndef BLINDWALKCONFIGURATIONLOADER_H
#define	BLINDWALKCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class BlindWalkConfigurationLoader : public ConfigurationLoader
{
	public:
		BlindWalkConfigurationLoader();
		~BlindWalkConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif