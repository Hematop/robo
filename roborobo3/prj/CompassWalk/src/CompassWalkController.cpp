/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "CompassWalk/include/CompassWalkController.h"

// Sensor Id
// (L)eft, (R)ight, (B)ack, (F)ront
// FFFL is a front sensor, pointing very slightly to the left (15°).
#define SENSOR_L 0
#define SENSOR_FL 1
#define SENSOR_FFL 2
#define SENSOR_FFFL 3
#define SENSOR_F 4
#define SENSOR_FFFR 5
#define SENSOR_FFR 6
#define SENSOR_FR 7
#define SENSOR_R 8
#define SENSOR_BR 9
#define SENSOR_B 10
#define SENSOR_BL 11

CompassWalkController::CompassWalkController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    // if ( _wm->_cameraSensorsNb != 12 )
    // {
    //     std::cerr << "[CRITICAL] This project assumes robot specifications with 12 sensors (current specs: " << _wm->_cameraSensorsNb << "). STOP.\n";
    //     exit(-1);
    // }
    
    _isAttracted = rand()%2;
    _opinion = rand()%2;

}

CompassWalkController::~CompassWalkController()
{
	// nothing to do.
}

void CompassWalkController::reset()
{
	// nothing to do.
}

void CompassWalkController::step()
{
    if(gWorld->getIterations() < 2){
    _isAttracted = _wm->_yReal > 500;
    _opinion = _wm->_yReal > 500;  
    }   
    if( true ) // ( _wm->getId() < gNbOfRobots/9 ) // the others are just replicas of the ones in the center
    {

        // SOME PARAMETERS:
        double balance = 1; // bias towards attraction if >1. analoguous to 1/T
        double swapRate = 0.01; // probability at each step that a node chooses random behavior
        double errorRate = 0; // probability at each step that a node doesn't act according to behavior
        double acceptance = 1; //.5 * (1+_isAttracted); // probability to take a neighbor into account
        // int center_x = gScreenWidth / 2, center_y = gScreenHeight / 2; // position of energy-giving center
        // int energyRadius = 200;
            
        int north_x = 500, north_y = 200, south_x = 500, south_y = 300;
        double invBal = 1/balance;
        double total = balance + invBal;

        _wm->_desiredTranslationalValue = 1;
            
        // UPDATE BEHAVIOR:

        // // listen to neighbors with weight 2, to oneself with weight 4, and add a noise of weight 1
        double consensus = total * 4 * _isAttracted + rand()%2 - (5 * invBal);
        for(int i = 0; i < _wm->_cameraSensorsNb; i++)
        {
            int targetIndex = _wm->getObjectIdFromCameraSensor(i);
            
            if ( targetIndex >= gRobotIndexStartOffset && targetIndex < gRobotIndexStartOffset+gNbOfRobots )   // sensor ray bumped into a robot : communication is possible
            {
                targetIndex = targetIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
                
                CompassWalkController* targetRobotController = dynamic_cast<CompassWalkController*>(gWorld->getRobot(targetIndex)->getController());
                
                if ( ! targetRobotController )
                {
                    std::cerr << "Error from robot " << _wm->getId() << " : the observer of robot " << targetIndex << " is not compatible." << std::endl;
                    exit(-1);
                }
                if ( ( (double)(rand()%100))/100.0 < acceptance )
                    consensus += total * 2 * targetRobotController->_isAttracted - 2 * invBal;
            }
        }
        _isAttracted = ( consensus >= 0 );

        // // same deal for opinion
        consensus = total * 4 * _opinion + rand()%2 - (5 * invBal);
        for(int i = 0; i < _wm->_cameraSensorsNb; i++)
        {
            int targetIndex = _wm->getObjectIdFromCameraSensor(i);
            
            if ( targetIndex >= gRobotIndexStartOffset && targetIndex < gRobotIndexStartOffset+gNbOfRobots )   // sensor ray bumped into a robot : communication is possible
            {
                targetIndex = targetIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
                
                CompassWalkController* targetRobotController = dynamic_cast<CompassWalkController*>(gWorld->getRobot(targetIndex)->getController());
                
                if ( ! targetRobotController )
                {
                    std::cerr << "Error from robot " << _wm->getId() << " : the observer of robot " << targetIndex << " is not compatible." << std::endl;
                    exit(-1);
                }
                if ( ( (double)(rand()%100))/100.0 < acceptance )
                    consensus += total * 2 * targetRobotController->_opinion - 2 * invBal;
            }
        }
        _opinion = ( consensus >= 0 );

        // pure random mutation
        if ( ( (double)(rand()%1000))/1000.0 < swapRate ) {
            _opinion = rand()%2;
            _isAttracted = rand()%2;
        }
        bool __isAttracted = _isAttracted;
        bool __opinion = _opinion;
        if ( ( (double)(rand()%100))/100.0 < errorRate ){
            __opinion = !_opinion;
            __isAttracted = !_isAttracted;
        }

        // TAKE DECISION ACCORDING TO BEHAVIOR
        if(__isAttracted){

            double minDist = 1;
            int nbNeighbours = 1;
            int nbAttNeighbours = 1;
            double avgCenterOfMass_X = 0;
            double avgCenterOfMass_Y = 0;


            // if(__opinion)
            // {
            //     avgCenterOfMass_X = (north_x - _wm->_xReal)/10  + _wm->_xReal;
            //     avgCenterOfMass_Y = (north_y - _wm->_yReal)/10  + _wm->_yReal;
            // } else {
            //     avgCenterOfMass_Y = (south_x - _wm->_xReal)/10  + _wm->_xReal;
            //     avgCenterOfMass_X = (south_y - _wm->_yReal)/10  + _wm->_yReal;
            // }
            avgCenterOfMass_X = _wm->_xReal;
            avgCenterOfMass_Y = _wm->_yReal;

           // std::cout<<"beg "<<_wm->getId()<<"\n";
            // compute local center of mass and min distance to detected neighbors in attractive mode
            for( int i = 0 ; i < _wm->_cameraSensorsNb ; i++)
            {
                int targetRawIndex = _wm->getObjectIdFromCameraSensor(i);
                
                if ( targetRawIndex >= gRobotIndexStartOffset )   // sensor ray bumped into a robot -- WARNING: one (very close) neighbor can be seen by more than one sensor (in the following, we dont care if this happen, though it is not correct to do so)
                {

                    int targetRobotIndex = targetRawIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
                 //   std::cout<<"ping "<<targetRobotIndex<<"\n";
                    nbNeighbours++;
                    
                    // update distance to closest neighbour TODO replace with average distance or sum(inv(dists))
                    double dist = _wm->getNormalizedDistanceValueFromCameraSensor( i );
                    if(minDist > dist)
                        minDist = dist;

                    // only listen to energetic or close neighbors
                    if( dynamic_cast<CompassWalkController*>(gWorld->getRobot(targetRobotIndex)->getController())->_isAttracted){//} && dist * gEnergyMax < gWorld->getRobot(targetRobotIndex)->getWorldModel()->getEnergyLevel() ){
                        nbAttNeighbours ++;
                        // update average center of mass
                        avgCenterOfMass_X = avgCenterOfMass_X + gWorld->getRobot(targetRobotIndex)->getWorldModel()->_xReal;
                        avgCenterOfMass_Y = avgCenterOfMass_Y + gWorld->getRobot(targetRobotIndex)->getWorldModel()->_yReal;   
                    }
                }
                // else => for wall avoidance, not used here
                // {
                //     if ( targetRawIndex == 0 && _wm->getCameraSensorValue(i,SENSOR_DISTANCEVALUE) < minDistToWall ) // closest wall
                //         minDistToWall = _wm->getCameraSensorValue(i,SENSOR_DISTANCEVALUE);
                // }
            }
         //   std::cout<<"end "<<nbAttNeighbours<<"\n";
            avgCenterOfMass_X = avgCenterOfMass_X / nbAttNeighbours;
            avgCenterOfMass_Y = avgCenterOfMass_Y / nbAttNeighbours;
            double y = avgCenterOfMass_Y - _wm->_yReal;// coordinates of center of mass wtr. to robot
            double x = avgCenterOfMass_X - _wm->_xReal;
            int phase = floor(minDist * 255);

            //_wm->updateLandmarkSensor( 0 );
            if(nbAttNeighbours == 0)
            {
                _wm->_desiredRotationalVelocity = (double)(((rand()%(int)(2 * gMaxRotationalSpeed)))-gMaxRotationalSpeed);
            }
            else
            {
                moveTowards(x,y);
                // _wm->_desiredTranslationalValue = sqrt(y*y + x*x) * elasticity + 1; // doesn't change global behavior for small noise
                _wm->_desiredTranslationalValue = 3;//nbAttNeighbours;
            }
            

        }
        else{
            // _wm->_desiredRotationalVelocity = (double)(((rand()%(int)(2 * gMaxRotationalSpeed)))-gMaxRotationalSpeed);

            if(__opinion)
                moveTowards(north_x - _wm->_xReal, north_y - _wm->_yReal);
            else moveTowards(south_x - _wm->_xReal, south_y - _wm->_yReal);
        }
        // std::cout << "[DEBUG] Robot #" << _wm->getId() << " : behavior is " << _isAttracted << " and direction " << _wm->_desiredRotationalVelocity << ".\n";

        
        

        // UPDATE ENERGY
        // _wm->setEnergyLevel( _wm->getEnergyLevel() + 2 * ( pow(_wm->_xReal - center_x, 2) + pow(_wm->_yReal - center_y, 2) < pow(energyRadius,2) ) - 1 );
        


        // UPDATE LED VALUES
        // (_wm->getLandmarkDistanceValue()<1)*255 // (_wm->getEnergyLevel())*255/gEnergyMax
        _wm->setRobotLED_colorValues(!_opinion*255,_opinion*255,_isAttracted*255);

      //  monitorSensoryInformation();
    }
    else{
        RobotWorldModel* __wm = gWorld->getRobot( _wm->getId() % (gNbOfRobots/9) )->getWorldModel();
        _wm->_desiredRotationalVelocity = __wm->_desiredRotationalVelocity;
        _wm->_desiredTranslationalValue = __wm->_desiredTranslationalValue;
        
        _isAttracted = (dynamic_cast<CompassWalkController*>(gWorld->getRobot( _wm->getId() % (gNbOfRobots/9) )->getController()))->_isAttracted;
        // _wm->setEnergyLevel(__wm->getEnergyLevel());
        int attractedness = 100 * (2-_isAttracted);
        // int energy = 200 * (gEnergyMax - _wm->getEnergyLevel()) / gEnergyMax;
        // _wm->setRobotLED_colorValues( energy, energy, energy );
    }
}

void CompassWalkController::moveTowards(double x, double y){
    double angle;

    // if no privilegied direction : randomWalk
    if ( y==0 && x==0 )
        angle = (double)(((rand()%(int)(2*gMaxRotationalSpeed)))-gMaxRotationalSpeed);
    // move according to the quadrant it is in

    else
    {
        double slack = ((double)(((rand()%360))-180))/2;
        angle = atan(y/x) * 45 / atan(1) + slack;
        if (x<0) angle += 180;
        if (angle>=180) angle -= 360;
        if (angle<-180) angle += 360;
        // std::cout << _wm->_agentAbsoluteOrientation << "\n";


        // std::cout << " [ " << x << " : " << y << " ] want: " << _wm->_desiredRotationalVelocity <<" curr: " << _wm->_agentAbsoluteOrientation << "\n";
    }




    // re-bound it
    angle -= _wm->_agentAbsoluteOrientation;
    if (angle>=180) angle -= 360;
    if (angle<-180) angle += 360;
    _wm->_desiredRotationalVelocity = angle;

}

void CompassWalkController::monitorSensoryInformation()
{
    // Note that this code is executed only for the agent which is "on focus". By default, this means agent #0.
    // When window mode:
    //      To show which agent has the focus, press 'F'
    //      To cycle through agents, press <tab> (or shift+<tab>)
    
    
    if ( gVerbose && gDisplayMode == 0 && gRobotIndexFocus == _wm->getId() )
    {
        
        std::cout << "=-= Robot #" << _wm->getId() << " : STARTING monitoring sensory information at iteration #" << gWorld->getIterations() << ".\n";
        
        // Rotational and translational speed, agent orientation wrt. upwards
        //      - *actual* and *desired* translational/rotational values are very different
        //          - actual values is what the robot is actually doing (this is measured)
        //          - desired values are set by the controller (this is set and the hardware controller tries to match it)
        //          - rational: you may ask for something (e.g. max speed) but physics and electronics may be limited
        //          - typical example: when going for max speed, the robot cannot instantaneously go at max speed.
        //      - agent orientation acts as a compass with respect the y-axis, similar to a magnetic compass where north is upward
        
        double srcOrientation = _wm->_agentAbsoluteOrientation;
        
        std::cout << "Agent orientation: " << std::setw(4) << srcOrientation << "° wrt North (ie. upwards).\n";
        
        std::cout << "Agent desired translational speed: " << _wm->_desiredTranslationalValue << std::endl;
        std::cout << "Agent desired rotational speed: " << std::setw(4) << _wm->_desiredRotationalVelocity << std::endl;
        
        std::cout << "Agent actual translational speed: " << _wm->_actualTranslationalValue << std::endl;
        std::cout << "Agent actual rotational speed: " << std::setw(4) << _wm->_actualRotationalVelocity << std::endl;

        // Landmarks
        //      - landmarks are invisible and intangible object that can act as magnetic point of interest.
        //      - usually used by providing direction and orientation wrt. the robot
        //      - example of use: magnetic compass, detection of direction to specific zone, etc.
        //      - closest landmark can be computed automatically (see below, last part)
        
        if ( gNbOfLandmarks > 0 )
        {
            // All landmarks (if any)
            
            for ( size_t i = 0 ; i != gNbOfLandmarks ; i++ )
            {
                Point2d posRobot(_wm->getXReal(),_wm->getYReal());
                Point2d closestPoint;
                
                double distanceToLandmark = getEuclidianDistance (posRobot,gLandmarks[0]->getPosition());
                double diffAngleToClosestLandmark = getAngleToTarget(posRobot,_wm->_agentAbsoluteOrientation,gLandmarks[i]->getPosition());
                
                std::cout << "Landmark " << i << " is at distance " << distanceToLandmark << ", angle = " << diffAngleToClosestLandmark << "\n";
            }
            
            // Closest landmark (in any)
            
            _wm->updateLandmarkSensor();
            std::cout << "Closest landmark is at distance " << std::setw(6) << _wm->getLandmarkDistanceValue() << ", angle = " << std::setw(6) << _wm->getLandmarkDistanceValue() << "\n";
        }
        else
            std::cout << "No landmark.\n";
        
        // Energy (unused)
        //      - in this code: energy is ignored.
        //      - battery level can be used in some experiment. Impact of battery level is to be managed locally.
        //      - EnergyRequest can be used in some experiment with specific energy point where only part of energy can harvest.
        
        std::cout << "Battery-level  : " << std::setw(6) << _wm->getEnergyLevel() << "\n"; // useless here
        std::cout << "Energy Requested (if asked) : " << std::setw(4) << _wm->getEnergyRequestValue() << "" << std::endl;
        
        // Floor sensor
        //      - read from gFootprintImage (see gFootprintImageFilename file)
        //      - typical use: gradient written on the floor, region marker. Could also be used for pheronome.
        
        double floorSensor_redValue = (double)_wm->getGroundSensor_redValue()/255.0;
        double floorSensor_greenValue = (double)_wm->getGroundSensor_greenValue()/255.0;
        double floorSensor_blueValue = (double)_wm->getGroundSensor_blueValue()/255.0;
        
        std::cout << "Floor sensor values: red=" << std::setw(4) << floorSensor_redValue << " ; green=" << std::setw(4) << floorSensor_greenValue << " ; blue=" << std::setw(4) << floorSensor_blueValue << ".\n";
        
        // LED sensor (on the robot)
        //      -
        
        double LED_redValue = (double)_wm->getRobotLED_redValue()/255.0;
        double LED_greenValue = (double)_wm->getRobotLED_greenValue()/255.0;
        double LED_blueValue = (double)_wm->getRobotLED_blueValue()/255.0;
        
        std::cout << "LED values: red=" << std::setw(4) << LED_redValue << " ; green=" << std::setw(4) << LED_greenValue << " ; blue=" << std::setw(4) << LED_blueValue << ".\n";
        
        // Camera/distance sensors -- provide: distance to obstacle, obstacle type, orientation (if robot)
        // REMARKS:
        //      - distance sensors are actually camera rays, and provides extended information:
        //          - distance to contact
        //          - type of contact (walls, objects, or robots)
        //          - if robot: group number, LED values, absolute orientation (from which one can compute relative orientation)
        //      - Objects and walls are different.
        //          - Walls are fixed, and loaded from gEnvironmentImage (see gEnvironmentImageFilename file)
        //          - There are several types of objects. Check children of object PhysicalObject.
        //          - Note that PhysicalObjects can have a tangible part (see gEnvironmentImage) and an intangible part (see gFootprintImage. The intangible part can be spotted with the floorSensor.
        //          - Some PhysicalObject are active and react to the robot actions (e.g. disappear, give energy, ...)
        //          - examples of use of a PhysicalObject:
        //              - a tangible object onto which the robot can crash. It is seen through distance sensors.
        //              - an intangible object onto which the robot can walk upon. It is seen through the floor sensor.
        //              - a mix of the two.
        
        for(int i  = 0; i < _wm->_cameraSensorsNb; i++)
        {
            double distance = _wm->getDistanceValueFromCameraSensor(i);
            // double distanceNormalized = _wm->getDistanceValueFromCameraSensor(i) / _wm->getCameraSensorMaximumDistanceValue(i); // Similar to _wm->getNormalizedDistanceValueFromCameraSensor(i); -- unused here

            int objectId = _wm->getObjectIdFromCameraSensor(i);
            
            std::cout << "Sensor #" << i << ":";
            
            if ( PhysicalObject::isInstanceOf(objectId) ) // sensor touched an object. What type? (could be GateObject, SwitchObject, RoundObject, ... -- check descendants of PhysicalObject class)
            {
                int nbOfTypes = PhysicalObjectFactory::getNbOfTypes();
                for ( int i = 0 ; i != nbOfTypes ; i++ )
                {
                    if ( i == gPhysicalObjects[objectId - gPhysicalObjectIndexStartOffset]->getType() )
                    {
                        std::cout << "object of type " << i << " detected\n";
                        break;
                    }
                }
            }
            else
            {
                if ( Agent::isInstanceOf(objectId) )
                {
                    int targetRobotId = objectId-gRobotIndexStartOffset;

                    std::cout << " touched robot #" << gWorld->getRobot(targetRobotId) << ", at distance " << std::setw(4) << distance << ".\n";
                    
                    // Distance to target , orientation wrt target, target absolute orientation, target LED values
                    // Distance to target is approximated through sensor ray length before contact.
                    
                    double tgtOrientation = gWorld->getRobot(targetRobotId)->getWorldModel()->_agentAbsoluteOrientation;
                    double delta_orientation = - ( srcOrientation - tgtOrientation );
                    if ( delta_orientation >= 180.0 )
                        delta_orientation = - ( 360.0 - delta_orientation );
                    else
                        if ( delta_orientation <= -180.0 )
                            delta_orientation = - ( - 360.0 - delta_orientation );
                    
                    std::cout << "\trelative orientation wrt target robot is " <<std::setw(4) << delta_orientation/180.0 << "\n";
                    std::cout << "\tabsolute orientation of target robot is  " <<std::setw(4) << tgtOrientation << "\n";
                    
                    // same group? -- unusued as of Oct. 2015
                    
                    if ( gWorld->getRobot(targetRobotId)->getWorldModel()->getGroupId() == _wm->getGroupId() )
                        std::cout << "\trobots are from the same group.\n";
                    else
                        std::cout << "\trobots are from different group.\n";
                    
                    // LED values of other robot (can be used for communication)
                    
                    double tgt_LED_redValue = (double)_wm->getRobotLED_redValue()/255.0;
                    double tgt_LED_greenValue = (double)_wm->getRobotLED_greenValue()/255.0;
                    double tgt_LED_blueValue = (double)_wm->getRobotLED_blueValue()/255.0;
                    
                    std::cout << "\tLED values: R=" << tgt_LED_redValue << ", G=" << tgt_LED_greenValue << ", B=" << tgt_LED_blueValue << "\n";
                    
                }
                else
                {
                    // input: wall or empty?
                    if ( objectId >= 0 && objectId < gPhysicalObjectIndexStartOffset ) // not empty, but cannot be identified: this is a wall.
                    {
                        std::cout << " touched an unindentified obstacle (probably a wall, id=" << objectId << "), at distance " << std::setw(4) << distance << ".\n";
                    }
                    else
                        std::cout << " nothing (id="<< objectId << "). Returns maximum value (" << std::setw(4) << distance << ")\n";
                }
            }
        }
        std::cout << "=-= Robot #" << _wm->getId() << " : STOPPING monitoring sensory information\n";
    }
    
}
