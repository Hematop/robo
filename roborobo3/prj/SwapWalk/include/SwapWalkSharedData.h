/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#ifndef SWAPWALKSHAREDDATA_H
#define SWAPWALKSHAREDDATA_H

class SwapWalkSharedData {
    
public:
    
    // -----
    static int gEvaluationTime; //! theoretical duration of a generation -- used for logging purpose
    
    static double gSwapRate; // probability at each step that a node chooses random behavior
	static double gBalance; // bias towards attraction if >1. analoguous to 1/T
    static double gErrorRate; // probability at each step that a node doesn't act according to behavior
    static double gAcceptance; //.5 * (1+_isAttracted); // probability to take a neighbor into account
    static double gBiasSpeedDelta;
    static bool gListeningState;
    static bool gSnapshots; // do we take snapshots?
    static int gSnapshotFrequency; // at what frequency?
    static int gCenterX, gCenterY; // position of energy-giving center
    static int gAngleFuzziness;
    static int gEnergyRadius; //200
    static int gKeptGroups;

    // -----
    
    
    
};


#endif
