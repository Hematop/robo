/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef COMPASSWALKAGENTOBSERVER_H
#define COMPASSWALKAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class CompassWalkAgentObserver : public AgentObserver
{
	public:
		CompassWalkAgentObserver( );
		CompassWalkAgentObserver( RobotWorldModel *__wm );
		~CompassWalkAgentObserver();
				
		void reset();
		void step();
		
};


#endif

