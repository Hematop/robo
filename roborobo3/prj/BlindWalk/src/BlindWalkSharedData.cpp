/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "BlindWalk/include/BlindWalkSharedData.h"


int BlindWalkSharedData::gEvaluationTime = 50; // how long a controller will be evaluated on a robot

double BlindWalkSharedData::gBalance = 1; // bias towards attraction if >1. analoguous to 1/T
double BlindWalkSharedData::gSwapRate = .05; // probability at each step that a node chooses random behavior
double BlindWalkSharedData::gErrorRate = 0; // probability at each step that a node doesn't act according to behavior
double BlindWalkSharedData::gAcceptance = 1; //.5 * (1+_isAttracted); // probability to take a neighbor into account
double BlindWalkSharedData::gBiasSpeedDelta = 1; // ratio speedWhenDiffusive/speedWhenSocial
bool BlindWalkSharedData::gSnapshots = true;
bool BlindWalkSharedData::gListeningState = false; // true: listens only to energetic neighbors
int BlindWalkSharedData::gSnapshotFrequency = 10000;
int BlindWalkSharedData::gCenterX = 200, BlindWalkSharedData::gCenterY = 200; // position of energy-giving center
int BlindWalkSharedData::gAngleFuzziness = 20; // width of possible angle error in SW-C::moveTowards
int BlindWalkSharedData::gEnergyRadius = 50; //200
int BlindWalkSharedData::gKeptGroups = 10; 
int BlindWalkSharedData::gVoteFrequency = 1;