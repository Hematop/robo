/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef POPCONVCEAGENTOBSERVER_H
#define POPCONVCEAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "PopConvce/include/PopConvceSharedData.h"

#include <iomanip>

class PopConvceAgentObserver : public AgentObserver
{
	public:
		PopConvceAgentObserver(RobotWorldModel *wm);
		~PopConvceAgentObserver();

		virtual void reset();
		virtual void step();

};

#endif

