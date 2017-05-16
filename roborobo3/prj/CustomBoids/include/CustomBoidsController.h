/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#ifndef CUSTOMBOIDSCONTROLLER_H
#define CUSTOMBOIDSCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/Graphics.h"
#include "Controllers/Controller.h"
#include "WorldModels/RobotWorldModel.h"
#include "CustomBoids/include/CustomBoidsAgentObserver.h"
#include <neuralnetworks/NeuralNetwork.h>

#include <iomanip>

using namespace Neural;


class CustomBoidsController : public Controller
{
private:
    int _iteration;
    void resetRobot();
    
public:
    
    CustomBoidsController(RobotWorldModel *wm);
    ~CustomBoidsController();
    
    void reset();
    void step();
};


#endif

