/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef SWAPWALKAGENTOBSERVER_H
#define SWAPWALKAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class SwapWalkAgentObserver : public AgentObserver
{
	public:
		SwapWalkAgentObserver( );
		SwapWalkAgentObserver( RobotWorldModel *__wm );
		~SwapWalkAgentObserver();
				
		void reset();
		void step();
		
};


#endif

