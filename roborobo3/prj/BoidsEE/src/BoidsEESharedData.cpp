/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "BoidsEE/include/BoidsEESharedData.h"

double BoidsEESharedData::gSigmaMin = 0.0;
double BoidsEESharedData::gProbaMutation = 0.0;
double BoidsEESharedData::gUpdateSigmaStep = 0.0;
double BoidsEESharedData::gSigmaRef = 0.0; // reference value of sigma
double BoidsEESharedData::gSigmaMax = 0.0; // maximal value of sigma
int BoidsEESharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

bool BoidsEESharedData::gSynchronization = true;

bool BoidsEESharedData::gEnergyRequestOutput = 1;

double BoidsEESharedData::gMonitorPositions;

bool BoidsEESharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

int BoidsEESharedData::gNbHiddenLayers = 1;
int BoidsEESharedData::gNbNeuronsPerHiddenLayer = 5;
int BoidsEESharedData::gNeuronWeightRange = 800;

bool BoidsEESharedData::gSnapshots = true; // take snapshots
int BoidsEESharedData::gSnapshotsFrequency = 50; // every N generations

int BoidsEESharedData::gControllerType = -1; // cf. header for description

bool BoidsEESharedData::gLimitGenomeTransmission = false; // default: do not limit.
int BoidsEESharedData::gMaxNbGenomeTransmission = 65535; // default: arbitrarily set to 65535.

int BoidsEESharedData::gSelectionMethod = 0; // default: random selection

int BoidsEESharedData::gNotListeningStateDelay = 0;    // -1: infinite ; 0: no delay ; >0: delay
int BoidsEESharedData::gListeningStateDelay = -1;      // -1: infinite ; 0: no delay ; >0: delay (ignored if gNotListeningStateDelay=-1)

bool BoidsEESharedData::gLogGenome = false;
bool BoidsEESharedData::gLogGenomeSnapshot = false;

double BoidsEESharedData::gIndividualMutationRate = 1.0;

int BoidsEESharedData::gMutationOperator = 1; // 0: uniform, 1: gaussian

double BoidsEESharedData::gSigma = 0.01; // 0.01 is just some random value.
