/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"
#include "CustomBoids/include/CustomBoidsWorldObserver.h"
#include "CustomBoids/include/CustomBoidsController.h"
#include "World/World.h"


CustomBoidsWorldObserver::CustomBoidsWorldObserver( World* world ) : WorldObserver( world )
{
    _world = world;
    
    // ==== loading project-specific properties

    gProperties.checkAndGetPropertyValue("gEvaluationTime",&CustomBoidsSharedData::gEvaluationTime,true);

    gProperties.checkAndGetPropertyValue("gMonitorPositions",&CustomBoidsSharedData::gMonitorPositions,true);
    
    gProperties.checkAndGetPropertyValue("gSnapshots",&CustomBoidsSharedData::gSnapshots,false);
    gProperties.checkAndGetPropertyValue("gSnapshotsFrequency",&CustomBoidsSharedData::gSnapshotsFrequency,false);

    
    // ====
    
    if ( !gRadioNetwork)
    {
        std::cout << "Error : gRadioNetwork must be true." << std::endl;
        exit(-1);
    }
    
    // * iteration and generation counters
    
    _generationItCount = -1;
    _generationCount = -1;

    gLogManager->write("angle\titeration\n");
    
}

CustomBoidsWorldObserver::~CustomBoidsWorldObserver()
{
    // nothing to do.
}

void CustomBoidsWorldObserver::reset()
{
    // nothing to do.
}

void CustomBoidsWorldObserver::step()
{
    _generationItCount++;
    
    if( _generationItCount == CustomBoidsSharedData::gEvaluationTime+1 ) // switch to next generation.
    {
        // update iterations and generations counters
        _generationItCount = 0;
        _generationCount++;
    }
    
    updateMonitoring();
    
    updateEnvironment();
    
    if(false && (_generationItCount % 5 == 0)){ // torus-like frame or not
        double x_avg = 0, y_avg = 0;
        std::cout << "[INFO] RP  . \r";
        if(true){ // move frame or not
            x_avg = -gScreenWidth/2 * gNbOfRobots;
            y_avg = -gScreenHeight/2 * gNbOfRobots;
            for ( int i = 0 ; i != gNbOfRobots ; i++ )
            {
                CustomBoidsController *cont = (dynamic_cast<CustomBoidsController*>(gWorld->getRobot(i)->getController()));
                x_avg += cont->getWorldModel()->_xReal;
                y_avg += cont->getWorldModel()->_yReal;
            }
            x_avg /= gNbOfRobots;
            y_avg /= gNbOfRobots;
            x_avg = floor(x_avg);
            y_avg = floor(y_avg);
        }
        for ( int i = 0 ; i != gNbOfRobots ; i++ )
        {
            CustomBoidsController *cont = (dynamic_cast<CustomBoidsController*>(gWorld->getRobot(i)->getController()));
            double delta_x = (cont->getWorldModel()->_xReal -  x_avg);
            double delta_y = (cont->getWorldModel()->_yReal -  y_avg);
            delta_x += (delta_x >= gScreenWidth*0.9) ? -gScreenWidth*0.8 : (delta_x < gScreenWidth*0.1) ? gScreenWidth*0.8 : 0;
            delta_y += (delta_y >= gScreenHeight*0.9) ? -gScreenHeight*0.8 : (delta_y < gScreenHeight*0.1) ? gScreenHeight*0.8 : 0;
            cont->getWorldModel()->_xReal =  delta_x;
            cont->getWorldModel()->_yReal =  delta_y;
        }
    }
}


void CustomBoidsWorldObserver::updateEnvironment()
{
    // ...
}

void CustomBoidsWorldObserver::updateMonitoring()
{
    // * Log at end of each generation

    if( gWorld->getIterations() % CustomBoidsSharedData::gEvaluationTime == 1 || gWorld->getIterations() % CustomBoidsSharedData::gEvaluationTime == CustomBoidsSharedData::gEvaluationTime-1 ) // beginning(+1) *and* end of generation. ("==1" is required to monitor the outcome of the first iteration)
    {
        monitorPopulation();
    }
    
    // * Every N generations, take a video (duration: one generation time)
    
    if ( CustomBoidsSharedData::gSnapshots )
    {
        if ( ( gWorld->getIterations() ) % ( CustomBoidsSharedData::gEvaluationTime * CustomBoidsSharedData::gSnapshotsFrequency ) == 0 )
        {
            if ( gVerbose )
                std::cout << "[START] Video recording: generation #" << (gWorld->getIterations() / CustomBoidsSharedData::gEvaluationTime ) << ".\n";
            gTrajectoryMonitorMode = 0;
            initTrajectoriesMonitor();
        }
        else
            if ( ( gWorld->getIterations() ) % ( CustomBoidsSharedData::gEvaluationTime * CustomBoidsSharedData::gSnapshotsFrequency ) == CustomBoidsSharedData::gEvaluationTime - 1 )
            {
                if ( gVerbose )
                    std::cout << "[STOP]  Video recording: generation #" << (gWorld->getIterations() / CustomBoidsSharedData::gEvaluationTime ) << ".\n";
                saveTrajectoryImage();
            }
    }    
}

void CustomBoidsWorldObserver::monitorPopulation( bool localVerbose )
{
    // * monitoring: count number of active agents.
    
    int activeCount = 0;
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        if ( (dynamic_cast<CustomBoidsController*>(gWorld->getRobot(i)->getController()))->getWorldModel()->isAlive() == true )
            activeCount++;
    }
    
    if ( gVerbose && localVerbose )
    {
        std::cout << "[gen:" << (gWorld->getIterations()/CustomBoidsSharedData::gEvaluationTime) << ";it:" << gWorld->getIterations() << ";pop:" << activeCount << "]\n";
    }
    
    // Logging, population-level: alive
   // std::string sLog = std::string("") + std::to_string(gWorld->getIterations()) + ",pop,alive," + std::to_string(activeCount) + "\n";
    //gLogManager->write(sLog);
    gLogManager->flush();
}
