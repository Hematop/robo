/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef BLINDWALKCONTROLLER_H
#define BLINDWALKCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"
#include "BlindWalk/include/BlindWalkSharedData.h"

#include "Agents/Agent.h"
#include "Agents/Robot.h"

class BlindWalkController : public Controller
{
	public:
		//Initializes the variables
		BlindWalkController( RobotWorldModel *__wm );
		~BlindWalkController();
    
        bool _isAttracted;
        void moveTowards(double, double);

		void reset();
		void step();
    
        void monitorSensoryInformation();
};


#endif

