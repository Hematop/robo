/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "SwapWalk/include/SwapWalkSharedData.h"


int SwapWalkSharedData::gEvaluationTime = 50; // how long a controller will be evaluated on a robot
double SwapWalkSharedData::gBalance = 1; // bias towards attraction if >1. analoguous to 1/T
double SwapWalkSharedData::gSwapRate = .05; // probability at each step that a node chooses random behavior
double SwapWalkSharedData::gErrorRate = 0; // probability at each step that a node doesn't act according to behavior
double SwapWalkSharedData::gAcceptance = 1; //.5 * (1+_isAttracted); // probability to take a neighbor into account
double SwapWalkSharedData::gBiasSpeedDelta = 1; // ratio speedWhenDiffusive/speedWhenSocial
bool SwapWalkSharedData::gSnapshots = true;
bool SwapWalkSharedData::gListeningState = false; // true: listens only to energetic neighbors
int SwapWalkSharedData::gSnapshotFrequency = 10000;
int SwapWalkSharedData::gCenterX = 200, SwapWalkSharedData::gCenterY = 200; // position of energy-giving center
int SwapWalkSharedData::gAngleFuzziness = 20; // width of possible angle error in SW-C::moveTowards
int SwapWalkSharedData::gEnergyRadius = 50; //200
int SwapWalkSharedData::gKeptGroups = 10; 