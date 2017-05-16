/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef COMPASSWALKCONTROLLER_H
#define COMPASSWALKCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"

#include "Agents/Agent.h"
#include "Agents/Robot.h"

class CompassWalkController : public Controller
{
	public:
		//Initializes the variables
		CompassWalkController( RobotWorldModel *__wm );
		~CompassWalkController();
    
        bool _isAttracted;
        bool _opinion;
        void moveTowards(double, double);

		void reset();
		void step();
    
        void monitorSensoryInformation();
};


#endif

