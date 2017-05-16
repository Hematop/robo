/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "PopConvce/include/PopConvceSharedData.h"

double PopConvceSharedData::gSigmaMin = 0.0;
double PopConvceSharedData::gProbaMutation = 0.0;
double PopConvceSharedData::gUpdateSigmaStep = 0.0;
double PopConvceSharedData::gSigmaRef = 0.0; // reference value of sigma
double PopConvceSharedData::gSigmaMax = 0.0; // maximal value of sigma
int PopConvceSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

bool PopConvceSharedData::gSynchronization = true;

bool PopConvceSharedData::gEnergyRequestOutput = 1;

double PopConvceSharedData::gMonitorPositions;

bool PopConvceSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

int PopConvceSharedData::gNbHiddenLayers = 1;
int PopConvceSharedData::gNbNeuronsPerHiddenLayer = 5;
int PopConvceSharedData::gNeuronWeightRange = 800;

bool PopConvceSharedData::gSnapshots = true; // take snapshots
int PopConvceSharedData::gSnapshotsFrequency = 50; // every N generations

int PopConvceSharedData::gControllerType = -1; // cf. header for description

bool PopConvceSharedData::gLimitGenomeTransmission = false; // default: do not limit.
int PopConvceSharedData::gMaxNbGenomeTransmission = 65535; // default: arbitrarily set to 65535.

int PopConvceSharedData::gSelectionMethod = 1; // 0 default: random selection

int PopConvceSharedData::gNotListeningStateDelay = 0;    // -1: infinite ; 0: no delay ; >0: delay
int PopConvceSharedData::gListeningStateDelay = -1;      // -1: infinite ; 0: no delay ; >0: delay (ignored if gNotListeningStateDelay=-1)

bool PopConvceSharedData::gLogGenome = false;
bool PopConvceSharedData::gLogGenomeSnapshot = false;

double PopConvceSharedData::gIndividualMutationRate = 1.0;

int PopConvceSharedData::gMutationOperator = 1; // 0: uniform, 1: individual gaussian, 2: global gaussian

double PopConvceSharedData::gSigma = 0.01; // 0.01 is just some random value.
