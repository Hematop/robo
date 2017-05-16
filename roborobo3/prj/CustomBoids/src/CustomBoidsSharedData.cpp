/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "CustomBoids/include/CustomBoidsSharedData.h"


int CustomBoidsSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

double CustomBoidsSharedData::gMonitorPositions;

bool CustomBoidsSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

bool CustomBoidsSharedData::gSnapshots = true; // take snapshots
int CustomBoidsSharedData::gSnapshotsFrequency = 50; // every N generations

