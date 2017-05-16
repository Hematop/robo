/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */





#ifndef CUSTOMBOIDSWORLDOBSERVER_H
#define CUSTOMBOIDSWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "CustomBoids/include/CustomBoidsSharedData.h"
#include "CustomBoids/include/CustomBoidsSharedData.h"

//class World;

class CustomBoidsWorldObserver : public WorldObserver
{
private:
    void updateEnvironment();
    void updateMonitoring();
    void monitorPopulation( bool localVerbose = true );
    
protected:
    int _generationCount;
    int _generationItCount;
    
public:
    CustomBoidsWorldObserver(World *world);
    ~CustomBoidsWorldObserver();
    
    void reset();
    void step();
    
    int getGenerationItCount() { return _generationItCount; }

};

#endif
