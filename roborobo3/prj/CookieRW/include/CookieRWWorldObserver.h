/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef COOKIERWWORLDOBSERVER_H
#define COOKIERWWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

class World;

class CookieRWWorldObserver : public WorldObserver
{
	protected:
		
	public:
		CookieRWWorldObserver( World *__world );
		~CookieRWWorldObserver();
				
		void reset();
		void step();
		
};

#endif

