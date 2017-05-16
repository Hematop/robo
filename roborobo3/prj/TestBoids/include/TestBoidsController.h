/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#ifndef TESTBOIDSCONTROLLER_H
#define TESTBOIDSCONTROLLER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/Graphics.h"
#include "Controllers/Controller.h"
#include "WorldModels/RobotWorldModel.h"
#include "TestBoids/include/TestBoidsAgentObserver.h"
#include <neuralnetworks/NeuralNetwork.h>

#include <iomanip>

using namespace Neural;


class TestBoidsController : public Controller
{
private:
    int _iteration;
    void resetRobot();
    
public:
    
    TestBoidsController(RobotWorldModel *wm);
    ~TestBoidsController();
    
    void reset();
    void step();
};


#endif

