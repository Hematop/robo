/*
 * CookieRWConfigurationLoader.h
 */

#ifndef COOKIERWCONFIGURATIONLOADER_H
#define	COOKIERWCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class CookieRWConfigurationLoader : public ConfigurationLoader
{
	public:
		CookieRWConfigurationLoader();
		~CookieRWConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
