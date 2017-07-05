/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef MOVESWAPAGENTOBSERVER_H
#define MOVESWAPAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "Observers/AgentObserver.h"

class MoveSwapAgentObserver : public AgentObserver
{
	public:
		MoveSwapAgentObserver( );
		MoveSwapAgentObserver( RobotWorldModel *__wm );
		~MoveSwapAgentObserver();
				
		void reset();
		void step();
		
};


#endif

