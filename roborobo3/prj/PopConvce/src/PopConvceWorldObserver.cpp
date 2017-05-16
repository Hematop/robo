/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"
#include "PopConvce/include/PopConvceWorldObserver.h"
#include "PopConvce/include/PopConvceController.h"
#include "World/World.h"

PopConvceWorldObserver::PopConvceWorldObserver( World* world ) : WorldObserver( world )
{
    _world = world;
    
    // ==== loading project-specific properties
    
    gProperties.checkAndGetPropertyValue("gSigmaRef",&PopConvceSharedData::gSigmaRef,true);
    gProperties.checkAndGetPropertyValue("gSigmaMin",&PopConvceSharedData::gSigmaMin,true);
    gProperties.checkAndGetPropertyValue("gSigmaMax",&PopConvceSharedData::gSigmaMax,true);
    
    gProperties.checkAndGetPropertyValue("gProbaMutation",&PopConvceSharedData::gProbaMutation,true);
    gProperties.checkAndGetPropertyValue("gUpdateSigmaStep",&PopConvceSharedData::gUpdateSigmaStep,true);
    gProperties.checkAndGetPropertyValue("gEvaluationTime",&PopConvceSharedData::gEvaluationTime,true);
    gProperties.checkAndGetPropertyValue("gSynchronization",&PopConvceSharedData::gSynchronization,true);
    
    gProperties.checkAndGetPropertyValue("gEnergyRequestOutput",&PopConvceSharedData::gEnergyRequestOutput,false);
    
    gProperties.checkAndGetPropertyValue("gMonitorPositions",&PopConvceSharedData::gMonitorPositions,true);
    
    gProperties.checkAndGetPropertyValue("gNbHiddenLayers",&PopConvceSharedData::gNbHiddenLayers,true);
    gProperties.checkAndGetPropertyValue("gNbNeuronsPerHiddenLayer",&PopConvceSharedData::gNbNeuronsPerHiddenLayer,true);
    gProperties.checkAndGetPropertyValue("gNeuronWeightRange",&PopConvceSharedData::gNeuronWeightRange,true);
    
    gProperties.checkAndGetPropertyValue("gSnapshots",&PopConvceSharedData::gSnapshots,false);
    gProperties.checkAndGetPropertyValue("gSnapshotsFrequency",&PopConvceSharedData::gSnapshotsFrequency,false);
    
    gProperties.checkAndGetPropertyValue("gControllerType",&PopConvceSharedData::gControllerType,true);
    
    gProperties.checkAndGetPropertyValue("gMaxNbGenomeTransmission",&PopConvceSharedData::gMaxNbGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gLimitGenomeTransmission",&PopConvceSharedData::gLimitGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gSelectionMethod",&PopConvceSharedData::gSelectionMethod,true);
    
    gProperties.checkAndGetPropertyValue("gNotListeningStateDelay",&PopConvceSharedData::gNotListeningStateDelay,true);
    gProperties.checkAndGetPropertyValue("gListeningStateDelay",&PopConvceSharedData::gListeningStateDelay,true);
    
    gProperties.checkAndGetPropertyValue("gLogGenome",&PopConvceSharedData::gLogGenome,false);
    gProperties.checkAndGetPropertyValue("gLogGenomeSnapshot",&PopConvceSharedData::gLogGenomeSnapshot,false);
    
    gProperties.checkAndGetPropertyValue("gIndividualMutationRate",&PopConvceSharedData::gIndividualMutationRate,false);

    gProperties.checkAndGetPropertyValue("gMutationOperator",&PopConvceSharedData::gMutationOperator,false);
    
    gProperties.checkAndGetPropertyValue("gSigma",&PopConvceSharedData::gSigma,false);
    
    // ====
    
    if ( !gRadioNetwork)
    {
        std::cout << "Error : gRadioNetwork must be true." << std::endl;
        exit(-1);
    }
    
    // * iteration and generation counters
    
    _generationItCount = -1;
    _generationCount = -1;
}

PopConvceWorldObserver::~PopConvceWorldObserver()
{
    // nothing to do.
}

void PopConvceWorldObserver::reset()
{
}

void PopConvceWorldObserver::step()
{
    _generationItCount++;
    
    if( _generationItCount == PopConvceSharedData::gEvaluationTime+1 ) // switch to next generation.
    {
        // update iterations and generations counters
        _generationItCount = 0;
        _generationCount++;
    }
    
    updateMonitoring();
    
    updateEnvironment();
    
}


void PopConvceWorldObserver::updateEnvironment()
{
    // example: moving landmarks
    /*
    if ( gWorld->getIterations() % 2000 == 0 )
        for ( int i = 0 ; i != gNbOfLandmarks ; i++ )
        {
            Point2d* position = new Point2d( 200+rand()%(gAreaWidth-400) , 200+rand()%(gAreaHeight-400) );
            gLandmarks[i]->setPosition(*position);
        }
    */
}

void PopConvceWorldObserver::updateMonitoring()
{
    // * Log at end of each generation

    //if( gWorld->getIterations() % PopConvceSharedData::gEvaluationTime == 1 || gWorld->getIterations() % PopConvceSharedData::gEvaluationTime == PopConvceSharedData::gEvaluationTime-1 ) // beginning(+1) *and* end of generation. ("==1" is required to monitor the outcome of the first iteration)
    // log at end of generation.
    if( gWorld->getIterations() % PopConvceSharedData::gEvaluationTime == PopConvceSharedData::gEvaluationTime-1 )
    {
        monitorPopulation();
    }
    
    // * Every N generations, take a video (duration: one generation time)
    
    if ( PopConvceSharedData::gSnapshots )
    {
        if ( ( gWorld->getIterations() ) % ( PopConvceSharedData::gEvaluationTime * PopConvceSharedData::gSnapshotsFrequency ) == 0 )
        {
            if ( gVerbose )
                std::cout << "[START] Video recording: generation #" << (gWorld->getIterations() / PopConvceSharedData::gEvaluationTime ) << ".\n";
            gTrajectoryMonitorMode = 0;
            initTrajectoriesMonitor();
        }
        else
            if ( ( gWorld->getIterations() ) % ( PopConvceSharedData::gEvaluationTime * PopConvceSharedData::gSnapshotsFrequency ) == PopConvceSharedData::gEvaluationTime - 1 )
            {
                if ( gVerbose )
                    std::cout << "[STOP]  Video recording: generation #" << (gWorld->getIterations() / PopConvceSharedData::gEvaluationTime ) << ".\n";
                saveTrajectoryImage();
            }
    }    
}

void PopConvceWorldObserver::monitorPopulation( bool localVerbose )
{
    // * monitoring: count number of active agents.
    int activeCount = 0;
    double avgFitness = 0;
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        RobotWorldModel* wm = (dynamic_cast<PopConvceController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
        if(wm->isAlive()){
            double fv = wm->_fitnessValue;
            avgFitness += fv;
            activeCount++;
        }
    }
    avgFitness /= activeCount;
    
    if ( gVerbose && localVerbose )
    {
        std::cout << "[gen:" << (gWorld->getIterations()/PopConvceSharedData::gEvaluationTime) << ";itn:" << gWorld->getIterations() << ";pop:" << activeCount << ";fit:" << avgFitness << "]\n";
    }
    
    // Logging, population-level: alive
    std::string sLog = std::string("") + std::to_string(gWorld->getIterations()) + ",pop,alive," + std::to_string(activeCount) + "\n";
    
    gLogManager->write(sLog);
    gLogManager->flush();
    
}
