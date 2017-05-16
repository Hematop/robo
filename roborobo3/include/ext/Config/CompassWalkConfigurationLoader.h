/*
 * CompassWalkConfigurationLoader.h
 */

#ifndef COMPASSWALKCONFIGURATIONLOADER_H
#define	COMPASSWALKCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class CompassWalkConfigurationLoader : public ConfigurationLoader
{
	public:
		CompassWalkConfigurationLoader();
		~CompassWalkConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
