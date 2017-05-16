/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef COOKIERWAGENTOBSERVER_H
#define COOKIERWAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class CookieRWAgentObserver : public AgentObserver
{
	public:
		CookieRWAgentObserver( );
		CookieRWAgentObserver( RobotWorldModel *__wm );
		~CookieRWAgentObserver();
				
		void reset();
		void step();
		
};


#endif

