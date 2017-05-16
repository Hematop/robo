/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef COMPASSWALKWORLDOBSERVER_H
#define COMPASSWALKWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include <list>  
#include "Observers/WorldObserver.h"

class World;

class CompassWalkWorldObserver : public WorldObserver
{
	protected:
		
	public:
		CompassWalkWorldObserver( World *__world );
		~CompassWalkWorldObserver();
				
		void reset();
		void step();
		void periodize();
		void monitorPopulation();
};

#endif

