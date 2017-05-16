/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef BOIDSEEAGENTOBSERVER_H
#define BOIDSEEAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "BoidsEE/include/BoidsEESharedData.h"

#include <iomanip>

class BoidsEEAgentObserver : public AgentObserver
{
	public:
		BoidsEEAgentObserver(RobotWorldModel *wm);
		~BoidsEEAgentObserver();

		virtual void reset();
		virtual void step();

};

#endif

