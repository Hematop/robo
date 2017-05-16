/*
 * SocialWalkConfigurationLoader.h
 */

#ifndef SOCIALWALKCONFIGURATIONLOADER_H
#define	SOCIALWALKCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class SocialWalkConfigurationLoader : public ConfigurationLoader
{
	public:
		SocialWalkConfigurationLoader();
		~SocialWalkConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
