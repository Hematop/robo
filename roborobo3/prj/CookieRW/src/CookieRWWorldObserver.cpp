/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "CookieRW/include/CookieRWWorldObserver.h"

#include "World/World.h"

#include "CookieRW/include/CookieRWController.h"

CookieRWWorldObserver::CookieRWWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

CookieRWWorldObserver::~CookieRWWorldObserver()
{
	// nothing to do.
}

void CookieRWWorldObserver::reset()
{
	// nothing to do.
}

void CookieRWWorldObserver::step()
{
    int _countAttracted = 0;
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        RobotWorldModel *_wd = (dynamic_cast<CookieRWController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
        if(_wd->getRobotLED_redValue()==0)
            _countAttracted++;
    }
    std::cout << _countAttracted << " in attracted mode\r";

}
