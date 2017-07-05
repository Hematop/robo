/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "MoveSwap/include/MoveSwapSharedData.h"


int MoveSwapSharedData::gEvaluationTime = 50; // how long a controller will be evaluated on a robot

int MoveSwapSharedData::gSourceSpeed = 1; // speed of sr-altering perturbation
double MoveSwapSharedData::gBalance = 1; // bias towards attraction if >1. analoguous to 1/T
double MoveSwapSharedData::gErrorRate = 0; // probability at each step that a node doesn't act according to behavior
double MoveSwapSharedData::gAcceptance = 1; //.5 * (1+_isAttracted); // probability to take a neighbor into account
double MoveSwapSharedData::gDefSwapRate = .05; // default SR
double MoveSwapSharedData::gSpecSwapRate = .05; // special SR in the HL zone
double MoveSwapSharedData::gBiasSpeedDelta = 1; // ratio speedWhenDiffusive/speedWhenSocial
bool MoveSwapSharedData::gSnapshots = true;
bool MoveSwapSharedData::gListeningState = false; // true: listens only to energetic neighbors
int MoveSwapSharedData::gCenterX = 300, MoveSwapSharedData::gCenterY = 300; // position of energy-giving center
int MoveSwapSharedData::gSnapshotFrequency = 10000;
int MoveSwapSharedData::gAngleFuzziness = 20; // width of possible angle error in SW-C::moveTowards
int MoveSwapSharedData::gEnergyRadius = 300; //200
int MoveSwapSharedData::gKeptGroups = 10; 