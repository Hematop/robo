/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */





#ifndef TESTBOIDSWORLDOBSERVER_H
#define TESTBOIDSWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "TestBoids/include/TestBoidsSharedData.h"
#include "TestBoids/include/TestBoidsSharedData.h"

//class World;

class TestBoidsWorldObserver : public WorldObserver
{
private:
    void updateEnvironment();
    void updateMonitoring();
    void monitorPopulation( bool localVerbose = true );
    
protected:
    int _generationCount;
    int _generationItCount;
    
public:
    TestBoidsWorldObserver(World *world);
    ~TestBoidsWorldObserver();
    
    void reset();
    void step();
    
    int getGenerationItCount() { return _generationItCount; }

};

#endif
