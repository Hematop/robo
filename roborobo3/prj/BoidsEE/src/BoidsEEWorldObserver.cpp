/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"
#include "BoidsEE/include/BoidsEEWorldObserver.h"
#include "BoidsEE/include/BoidsEEController.h"
#include "World/World.h"

BoidsEEWorldObserver::BoidsEEWorldObserver( World* world ) : WorldObserver( world )
{
    _world = world;
    
    // ==== loading project-specific properties
    
    gProperties.checkAndGetPropertyValue("gSigmaRef",&BoidsEESharedData::gSigmaRef,true);
    gProperties.checkAndGetPropertyValue("gSigmaMin",&BoidsEESharedData::gSigmaMin,true);
    gProperties.checkAndGetPropertyValue("gSigmaMax",&BoidsEESharedData::gSigmaMax,true);
    
    gProperties.checkAndGetPropertyValue("gProbaMutation",&BoidsEESharedData::gProbaMutation,true);
    gProperties.checkAndGetPropertyValue("gUpdateSigmaStep",&BoidsEESharedData::gUpdateSigmaStep,true);
    gProperties.checkAndGetPropertyValue("gEvaluationTime",&BoidsEESharedData::gEvaluationTime,true);
    gProperties.checkAndGetPropertyValue("gSynchronization",&BoidsEESharedData::gSynchronization,true);
    
    gProperties.checkAndGetPropertyValue("gEnergyRequestOutput",&BoidsEESharedData::gEnergyRequestOutput,false);
    
    gProperties.checkAndGetPropertyValue("gMonitorPositions",&BoidsEESharedData::gMonitorPositions,true);
    
    gProperties.checkAndGetPropertyValue("gNbHiddenLayers",&BoidsEESharedData::gNbHiddenLayers,true);
    gProperties.checkAndGetPropertyValue("gNbNeuronsPerHiddenLayer",&BoidsEESharedData::gNbNeuronsPerHiddenLayer,true);
    gProperties.checkAndGetPropertyValue("gNeuronWeightRange",&BoidsEESharedData::gNeuronWeightRange,true);
    
    gProperties.checkAndGetPropertyValue("gSnapshots",&BoidsEESharedData::gSnapshots,false);
    gProperties.checkAndGetPropertyValue("gSnapshotsFrequency",&BoidsEESharedData::gSnapshotsFrequency,false);
    
    gProperties.checkAndGetPropertyValue("gControllerType",&BoidsEESharedData::gControllerType,true);
    
    gProperties.checkAndGetPropertyValue("gMaxNbGenomeTransmission",&BoidsEESharedData::gMaxNbGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gLimitGenomeTransmission",&BoidsEESharedData::gLimitGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gSelectionMethod",&BoidsEESharedData::gSelectionMethod,true);
    
    gProperties.checkAndGetPropertyValue("gNotListeningStateDelay",&BoidsEESharedData::gNotListeningStateDelay,true);
    gProperties.checkAndGetPropertyValue("gListeningStateDelay",&BoidsEESharedData::gListeningStateDelay,true);
    
    gProperties.checkAndGetPropertyValue("gLogGenome",&BoidsEESharedData::gLogGenome,false);
    gProperties.checkAndGetPropertyValue("gLogGenomeSnapshot",&BoidsEESharedData::gLogGenomeSnapshot,false);
    
    gProperties.checkAndGetPropertyValue("gIndividualMutationRate",&BoidsEESharedData::gIndividualMutationRate,false);

    gProperties.checkAndGetPropertyValue("gMutationOperator",&BoidsEESharedData::gMutationOperator,false);
    
    gProperties.checkAndGetPropertyValue("gSigma",&BoidsEESharedData::gSigma,false);
    
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

BoidsEEWorldObserver::~BoidsEEWorldObserver()
{
    // nothing to do.
}

void BoidsEEWorldObserver::reset()
{
}

void BoidsEEWorldObserver::step()
{
    _generationItCount++;
    
    if( _generationItCount == BoidsEESharedData::gEvaluationTime+1 ) // switch to next generation.
    {
        // update iterations and generations counters
        _generationItCount = 0;
        _generationCount++;
    }
    
    updateMonitoring();
    
    updateEnvironment();
    
}


void BoidsEEWorldObserver::updateEnvironment()
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

void BoidsEEWorldObserver::updateMonitoring()
{
    // * Log at end of each generation

    //if( gWorld->getIterations() % BoidsEESharedData::gEvaluationTime == 1 || gWorld->getIterations() % BoidsEESharedData::gEvaluationTime == BoidsEESharedData::gEvaluationTime-1 ) // beginning(+1) *and* end of generation. ("==1" is required to monitor the outcome of the first iteration)
    // log at end of generation.
    if( gWorld->getIterations() % BoidsEESharedData::gEvaluationTime == BoidsEESharedData::gEvaluationTime-1 )
    {
        monitorPopulation();
    }
    
    // * Every N generations, take a video (duration: one generation time)
    
    if ( BoidsEESharedData::gSnapshots )
    {
        if ( ( gWorld->getIterations() ) % ( BoidsEESharedData::gEvaluationTime * BoidsEESharedData::gSnapshotsFrequency ) == 0 )
        {
            if ( gVerbose )
                std::cout << "[START] Video recording: generation #" << (gWorld->getIterations() / BoidsEESharedData::gEvaluationTime ) << ".\n";
            gTrajectoryMonitorMode = 0;
            initTrajectoriesMonitor();
        }
        else
            if ( ( gWorld->getIterations() ) % ( BoidsEESharedData::gEvaluationTime * BoidsEESharedData::gSnapshotsFrequency ) == BoidsEESharedData::gEvaluationTime - 1 )
            {
                if ( gVerbose )
                    std::cout << "[STOP]  Video recording: generation #" << (gWorld->getIterations() / BoidsEESharedData::gEvaluationTime ) << ".\n";
                saveTrajectoryImage();
            }
    }    
}

void BoidsEEWorldObserver::monitorPopulation( bool localVerbose )
{
    // reading average fitness and monitoring: count number of active agents.
    
    int activeCount = 0;
    double avgFitness = 0;
    // double varFitness = 0;
    double threshold = 0; // todo make it decile
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        RobotWorldModel* wm = (dynamic_cast<BoidsEEController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
        if(wm->isAlive()){
            double fv = wm->_fitnessValue;
            avgFitness += fv;
            // varFitness += fv * fv;
            activeCount++;
          //  std::cout << "[var:" << varFitness << ";fit:" << avgFitness * avgFitness << ";pop:" << activeCount << ";fv:" << fv << "]\n";
        }
    }
    // std::cout << "[var:" << varFitness << ";fit:" << avgFitness << ";pop:" << activeCount << "]\n";
    
    avgFitness /= activeCount;
    // varFitness /= activeCount;
    // varFitness -= avgFitness * avgFitness;
    // double sigma = sqrt(varFitness);
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        RobotWorldModel* wm = (dynamic_cast<BoidsEEController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
        if(wm->isAlive()){
            double fv = wm->_fitnessValue;
            if(fv<avgFitness)
                threshold += fv;
        }
    }
    threshold /= (activeCount/1.7);
    
    if ( gVerbose && localVerbose )
    {
        std::cout << "[gen:" << (gWorld->getIterations()/BoidsEESharedData::gEvaluationTime) << ";itn:" << gWorld->getIterations() << ";pop:" << activeCount << "]\n";
    }
    
    // Logging, population-level: alive
    std::string sLog = std::string("") + std::to_string(gWorld->getIterations()) + ",pop,alive," + std::to_string(activeCount) + "\n";
    
    gLogManager->write(sLog);
    gLogManager->flush();

    // culling unfit agents
    // int desactivatedCount = 0;
    // for ( int i = 0 ; i != gNbOfRobots ; i++ )
    // {
    //     RobotWorldModel* wm = (dynamic_cast<BoidsEEController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
    //     if(wm->_fitnessValue < threshold){
    //         wm->setAlive(false);
    //         desactivatedCount++;
    //     }
    // }
    // if ( gVerbose && localVerbose )
    // {
    //     std::cout << "[kld:" << desactivatedCount << ";fts:" << avgFitness << ";thd:" << threshold << "]\n";
    // }
}
