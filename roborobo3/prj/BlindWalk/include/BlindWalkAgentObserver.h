/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef BLINDWALKAGENTOBSERVER_H
#define BLINDWALKAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class BlindWalkAgentObserver : public AgentObserver
{
	public:
		BlindWalkAgentObserver( );
		BlindWalkAgentObserver( RobotWorldModel *__wm );
		~BlindWalkAgentObserver();
				
		void reset();
		void step();
		
};


#endif

