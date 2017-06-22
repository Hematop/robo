/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef BLINDWALKWORLDOBSERVER_H
#define BLINDWALKWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include <list>  
#include "Observers/WorldObserver.h"
#include "BlindWalk/include/BlindWalkSharedData.h"

class World;

class BlindWalkWorldObserver : public WorldObserver
{
	protected:
		
	public:
		BlindWalkWorldObserver( World *__world );
		~BlindWalkWorldObserver();
				
		void reset();
		void step();
		void periodize();
		void monitorPopulation();
};

#endif

