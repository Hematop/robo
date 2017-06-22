/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */

#include "BlindWalk/include/BlindWalkAgentObserver.h"



BlindWalkAgentObserver::BlindWalkAgentObserver( )
{
}

BlindWalkAgentObserver::BlindWalkAgentObserver( RobotWorldModel *__wm )
{
	_wm = __wm;
}

BlindWalkAgentObserver::~BlindWalkAgentObserver()
{
	// nothing to do.
}

void BlindWalkAgentObserver::reset()
{
	// nothing to do.
}

void BlindWalkAgentObserver::step()
{
    // * send callback messages to objects touched or walked upon.
    // through distance sensors
    for( int i = 0 ; i < _wm->_cameraSensorsNb; i++)
    {
        int targetIndex = _wm->getObjectIdFromCameraSensor(i);
        
        if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gRobotIndexStartOffset )   // sensor ray bumped into a physical object
        {
            targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
            //std::cout << "[DEBUG] Robot #" << _wm->getId() << " touched " << targetIndex << "\n";
            gPhysicalObjects[targetIndex]->isTouched(_wm->getId());

            //_wm->setEnergyLevel(_wm->getEnergyLevel()+2);
        }
    }
    
    // through floor sensor
    int targetIndex = _wm->getGroundSensorValue();
    if ( targetIndex >= gPhysicalObjectIndexStartOffset && targetIndex < gPhysicalObjectIndexStartOffset + (int)gPhysicalObjects.size() )   // ground sensor is upon a physical object (OR: on a place marked with this physical object footprint, cf. groundsensorvalues image)
    {
        targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
        //std::cout << "[DEBUG] #" << _wm->getId() << " walked upon " << targetIndex << "\n";
        gPhysicalObjects[targetIndex]->isWalked(_wm->getId());

        _wm->setEnergyLevel(gEnergyInit);
    }

    // gLogManager->write(std::to_string(_wm->_agentAbsoluteOrientation)+"\n");
   
}

