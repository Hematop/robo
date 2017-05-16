/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef BOIDSEEWORLDOBSERVER_H
#define BOIDSEEWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "BoidsEE/include/BoidsEESharedData.h"

//class World;

class BoidsEEWorldObserver : public WorldObserver
{
protected:
    virtual void updateEnvironment();
    virtual void updateMonitoring();
    virtual void monitorPopulation( bool localVerbose = true );
    
    int _generationCount;
    int _generationItCount;
    
public:
    BoidsEEWorldObserver(World *world);
    ~BoidsEEWorldObserver();
    
    virtual void reset();
    virtual void step();
    
    virtual  int getGenerationItCount() { return _generationItCount; }

};

#endif
