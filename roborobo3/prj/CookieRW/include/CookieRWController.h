/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef COOKIERWCONTROLLER_H
#define COOKIERWCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Controllers/Controller.h"

#include "WorldModels/RobotWorldModel.h"

#include "Agents/Agent.h"
#include "Agents/Robot.h"

class CookieRWController : public Controller
{
	public:
		//Initializes the variables
		CookieRWController( RobotWorldModel *__wm );
		~CookieRWController();
    
        bool _isAttracted;
        void moveTowards(double, double);

		void reset();
		void step();
    
        void monitorSensoryInformation();
};


#endif

