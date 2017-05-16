/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "TestBoids/include/TestBoidsSharedData.h"


int TestBoidsSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

double TestBoidsSharedData::gMonitorPositions;

bool TestBoidsSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

bool TestBoidsSharedData::gSnapshots = true; // take snapshots
int TestBoidsSharedData::gSnapshotsFrequency = 50; // every N generations

