/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef TESTBOIDSAGENTOBSERVER_H
#define TESTBOIDSAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "TestBoids/include/TestBoidsSharedData.h"

#include <iomanip>

class TestBoidsAgentObserver : public AgentObserver
{
	public:
		TestBoidsAgentObserver(RobotWorldModel *wm);
		~TestBoidsAgentObserver();

		void reset();
		void step();

};

#endif

