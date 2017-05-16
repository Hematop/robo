/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "CompassWalk/include/CompassWalkWorldObserver.h"

#include "World/World.h"

#include "CompassWalk/include/CompassWalkController.h"

CompassWalkWorldObserver::CompassWalkWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
    gLogManager->write("angle\tcollision\n");
}

CompassWalkWorldObserver::~CompassWalkWorldObserver()
{
	// nothing to do.
}

void CompassWalkWorldObserver::reset()
{
	// nothing to do.
}

void CompassWalkWorldObserver::step()
{
    //periodize();

    // std::cout<<gWorld->getIterations() << "\n";

    if ( gWorld->getIterations() % 100 == 0 ){
        monitorPopulation();


        // attracted mode is denoted by green LED, red otherwise.
        // to track phase, each robot's blue LED value is its distance to closest detected neighbor, and we return the average of that number on a first approximation
        int _countAttracted = 0;
        double phase = 0;
        double x_avg = -gScreenWidth/2 * gNbOfRobots;
        double y_avg = -gScreenHeight/2 * gNbOfRobots;
        for ( int i = 0 ; i != gNbOfRobots ; i++ )
        {
            CompassWalkController *cont = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i)->getController()));
            x_avg += cont->getWorldModel()->_xReal;
            y_avg += cont->getWorldModel()->_yReal;
            if(cont->_isAttracted)
                _countAttracted++;
            phase += cont->getWorldModel()->getRobotLED_blueValue();
        }
        x_avg /= gNbOfRobots;
        y_avg /= gNbOfRobots;
        x_avg = floor(x_avg);
        y_avg = floor(y_avg);
        phase /= gNbOfRobots;
        // std::cout << "[INFO] phase: " << phase << ";\t" << _countAttracted << " in attracted mode;\tbarycenter moved to [" << x_avg << ", "<< y_avg <<"].\r";
        
    }


}

void CompassWalkWorldObserver::periodize()
{ 
    for ( int i = 0 ; i != gNbOfRobots/9 ; i++ )
    {

        // put the robots from the middle in the middle
        Robot *rob = gWorld->getRobot(i);
        CompassWalkController *cont = (dynamic_cast<CompassWalkController*>(rob->getController()));
        double new_x = (cont->getWorldModel()->_xReal);
        double new_y = (cont->getWorldModel()->_yReal);
        new_x += (new_x >= gScreenWidth *0.65) ? -gScreenWidth *0.3 : (new_x < gScreenWidth *0.35) ? gScreenWidth *0.3 : 0;
        new_y += (new_y >= gScreenHeight*0.65) ? -gScreenHeight*0.3 : (new_y < gScreenHeight*0.35) ? gScreenHeight*0.3 : 0;
        cont->getWorldModel()->_xReal =  new_x;
        cont->getWorldModel()->_yReal =  new_y;


        // copy them 8 times
        RobotWorldModel *wmTL = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + gNbOfRobots/9)->getController()))->getWorldModel();
        wmTL->_xReal = new_x + 0.3 * gScreenWidth;
        wmTL->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmTM = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 2*gNbOfRobots/9)->getController()))->getWorldModel();
        wmTM->_xReal = new_x;
        wmTM->_yReal = new_y + 0.3 * gScreenHeight;
        RobotWorldModel *wmTR = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 3*gNbOfRobots/9)->getController()))->getWorldModel();
        wmTR->_xReal = new_x + 0.3 * gScreenWidth;
        wmTR->_yReal = new_y + 0.3 * gScreenHeight;
        RobotWorldModel *wmML = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 4*gNbOfRobots/9)->getController()))->getWorldModel();
        wmML->_xReal = new_x - 0.3 * gScreenWidth;
        wmML->_yReal = new_y;
        RobotWorldModel *wmMR = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 5*gNbOfRobots/9)->getController()))->getWorldModel();
        wmMR->_xReal = new_x + 0.3 * gScreenWidth;
        wmMR->_yReal = new_y;
        RobotWorldModel *wmBL = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 6*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBL->_xReal = new_x - 0.3 * gScreenWidth;
        wmBL->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmBM = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 7*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBM->_xReal = new_x;
        wmBM->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmBR = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i + 8*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBR->_xReal = new_x - 0.3 * gScreenWidth;
        wmBR->_yReal = new_y + 0.3 * gScreenHeight;
    }
}

void CompassWalkWorldObserver::monitorPopulation()
{
    
    std::map< int,std::list<int> > cc;
    int e = 0; // # of robots in landmark 0
    double clusterSquaredDist = pow(0.2*gSensorRange, 2);
    for(int i = 0; i<gNbOfRobots; i++){
        RobotWorldModel *Ri = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
    //    Ri->setRobotLED_colorValues(100,100,100);
        // Ri->setRobotLED_colorValues(rand()%255,rand()%255,rand()%255);
        e += (Ri->getLandmarkDistanceValue()<1);
        cc[i] = std::list<int>(1,i);
        for(int j = 0; j<gNbOfRobots; j++)
            if(j!=i)
            {
                RobotWorldModel *Rj = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
                if( pow(Ri->_xReal - Rj->_xReal, 2) + pow(Ri->_yReal - Rj->_yReal, 2) < clusterSquaredDist ){
                    // Rj->setRobotLED_colorValues(Ri->getRobotLED_redValue(), Ri->getRobotLED_greenValue(), Ri->getRobotLED_blueValue());
                    int ccOfJ = j;
                    
                    while( !cc[ccOfJ].empty() && cc[ccOfJ].front() != ccOfJ ){
                        // std::cout<<" "<<ccOfJ<<" "<< (  cc[ccOfJ].front() ) <<"\n";
                        int buf = ccOfJ;
                        ccOfJ = cc[ccOfJ].front();
                        cc[buf] = std::list<int> (1,i);
                    }
                    // std::cout<<"cc "<<ccOfJ<<" of "<<j<<" for "<<i<<"   ";
                    if(ccOfJ != i){
                        if(cc[ccOfJ].empty())
                            cc[i].push_back(ccOfJ);
                        else{
                            // std::cout<<"size "<<cc[ccOfJ].size();
                            for( int k : cc[ccOfJ] )
                                cc[i].push_back(k);
                        }
                        
                        // std::cout<<"n\n";
                        cc[ccOfJ] = std::list<int> (1,i);
                    }
                }
            }
    }

    // std::vector<int> cc (gNbOfRobots, -1);
    // std::list<int> notseen ;
    // std::list<int> sizes;

    // for(int i = 0; i<gNbOfRobots; i++){
    //     notseen.push_back(i);
    //     e += ((dynamic_cast<CompassWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel()->getLandmarkDistanceValue()<1);
    // }
    // while(!notseen.empty()){
    //     int i = notseen.front();
    //     cc[i] = i;
    //     int ct = 1;
    //     notseen.pop_front();
    //     RobotWorldModel *Ri = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel();
    //     std::list<int> toConsider;
    //     toConsider.push_back(i);
    //     while(!toConsider.empty()){
    //         int j = toConsider.front();
    //         toConsider.pop_front();
    //         for(int k : notseen){
    //             RobotWorldModel *Rk = (dynamic_cast<CompassWalkController*>(gWorld->getRobot(k)->getController()))->getWorldModel();
    //             if( pow(Ri->_xReal - Rk->_xReal, 2) + pow(Ri->_yReal - Rk->_yReal, 2) < clusterSquaredDist ){
    //                 notseen.remove(k);
    //                 toConsider.push_back(k);
    //                 cc[k] = i;
    //                 ct++;
    //             }
    //         }
    //     }  
    //     sizes.push_back(ct);      
    // }
    

    // std::list<int> sizes;
    // for(int i = 0; i<gNbOfRobots; i++)
        // if(cc[i].size()>10){
        //     bool isCopy = true;
        //     int r = rand()%255;
        //     int g = rand()%255;
        //     int b = rand()%255;
        //     for(int a : cc[i]){
        //         if( a<gNbOfRobots/9 )
        //             isCopy = false;
        //  //       (dynamic_cast<CompassWalkController*>(gWorld->getRobot(a)->getController()))->getWorldModel()->setRobotLED_colorValues(r,g,b);
        //     }
        //     if(!isCopy)
        //         sizes.push_back(cc[i].size());
        // }
    std::cout << e << ", ";
    for(int i = 0; i<gNbOfRobots; i++){
        if(cc[i].size() > 9)
            std::cout<<cc[i].size()<<" ";
    }
    std::cout<<"\n";
    std::string sLog = std::string("") + std::to_string(e) + "\t";
    for(int i = 0; i<gNbOfRobots; i++){
            if(cc[i].size() > 9)
                sLog += std::to_string(cc[i].size()) + " ";
        }
    gLogManager->write(sLog + "\n");

    // for( int i = 0; i<gNbOfRobots; i++ ){
    //     std::cout<<"\n\t"<<i<<": [";
    //     for(int j : cc[i])
    //         std::cout<<"\t"<<j;
    //     std::cout<<"   ]";
    // }

}