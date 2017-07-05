/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef MOVESWAPWORLDOBSERVER_H
#define MOVESWAPWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include <list>  
#include "Observers/WorldObserver.h"
#include "MoveSwap/include/MoveSwapSharedData.h"

class World;

class MoveSwapWorldObserver : public WorldObserver
{
	protected:
		
	public:
		MoveSwapWorldObserver( World *__world );
		~MoveSwapWorldObserver();
				
		void reset();
		void step();
		void periodize();
		void monitorPopulation();
};

#endif

