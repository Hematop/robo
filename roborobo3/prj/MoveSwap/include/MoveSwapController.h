/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef MOVESWAPCONTROLLER_H
#define MOVESWAPCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"
#include "MoveSwap/include/MoveSwapSharedData.h"

#include "Agents/Agent.h"
#include "Agents/Robot.h"

class MoveSwapController : public Controller
{
	public:
		//Initializes the variables
		MoveSwapController( RobotWorldModel *__wm );
		~MoveSwapController();
    
        bool _isAttracted;
        void moveTowards(double, double);

		void reset();
		void step();
    
        void monitorSensoryInformation();
};


#endif

