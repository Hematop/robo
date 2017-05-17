/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef SWAPWALKCONTROLLER_H
#define SWAPWALKCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"
#include "SwapWalk/include/SwapWalkSharedData.h"

#include "Agents/Agent.h"
#include "Agents/Robot.h"

class SwapWalkController : public Controller
{
	public:
		//Initializes the variables
		SwapWalkController( RobotWorldModel *__wm );
		~SwapWalkController();
    
        bool _isAttracted;
        void moveTowards(double, double);

		void reset();
		void step();
    
        void monitorSensoryInformation();
};


#endif

