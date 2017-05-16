/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef CUSTOMBOIDSAGENTOBSERVER_H
#define CUSTOMBOIDSAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "CustomBoids/include/CustomBoidsSharedData.h"

#include <iomanip>

class CustomBoidsAgentObserver : public AgentObserver
{
	public:
		CustomBoidsAgentObserver(RobotWorldModel *wm);
		~CustomBoidsAgentObserver();

		void reset();
		void step();

};

#endif

