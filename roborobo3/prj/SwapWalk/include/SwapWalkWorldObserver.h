/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef SWAPWALKWORLDOBSERVER_H
#define SWAPWALKWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include <list>  
#include "Observers/WorldObserver.h"

class World;

class SwapWalkWorldObserver : public WorldObserver
{
	protected:
		
	public:
		SwapWalkWorldObserver( World *__world );
		~SwapWalkWorldObserver();
				
		void reset();
		void step();
		void periodize();
		void monitorPopulation();
};

#endif

