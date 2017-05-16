/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef POPCONVCEWORLDOBSERVER_H
#define POPCONVCEWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "PopConvce/include/PopConvceSharedData.h"

//class World;

class PopConvceWorldObserver : public WorldObserver
{
protected:
    virtual void updateEnvironment();
    virtual void updateMonitoring();
    virtual void monitorPopulation( bool localVerbose = true );
    
    int _generationCount;
    int _generationItCount;
    
public:
    PopConvceWorldObserver(World *world);
    ~PopConvceWorldObserver();
    
    virtual void reset();
    virtual void step();
    
    virtual  int getGenerationItCount() { return _generationItCount; }

};

#endif
