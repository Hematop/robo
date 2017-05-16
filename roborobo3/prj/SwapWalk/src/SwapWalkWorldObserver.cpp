/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SwapWalk/include/SwapWalkWorldObserver.h"

#include "World/World.h"

#include "SwapWalk/include/SwapWalkController.h"

SwapWalkWorldObserver::SwapWalkWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
    std::string id = std::to_string(gRandomSeed % 10);
    gLogManager->write("count"+id+"\tsize"+id+
        "\tgroupA"+id+"\tradiusA"+id+
        "\tgroupB"+id+"\tradiusB"+id+
        "\tgroupC"+id+"\tradiusC"+id+
        "\tgroupD"+id+"\tradiusD"+id+
        "\tgroupE"+id+"\tradiusE"+id+
        "\tgroupF"+id+"\tradiusF"+id+
        "\tgroupG"+id+"\tradiusG"+id+
        "\tgroupH"+id+"\tradiusH"+id+
        "\tgroupI"+id+"\tradiusI"+id+
        "\tgroupJ"+id+"\tradiusJ"+id+"\n");
}

SwapWalkWorldObserver::~SwapWalkWorldObserver()
{
	// nothing to do.
}

void SwapWalkWorldObserver::reset()
{
	// nothing to do.
}

void SwapWalkWorldObserver::step()
{
    //periodize();
    if ( gWorld->getIterations() % 50 == 0 ){ //  
        monitorPopulation();


        // attracted mode is denoted by green LED, red otherwise.
        // to track phase, each robot's blue LED value is its distance to closest detected neighbor, and we return the average of that number on a first approximation
        // int _countAttracted = 0;
        // double phase = 0;
        // double x_avg = 0;//-gScreenWidth/2 * gNbOfRobots;
        // double y_avg = 0;//-gScreenHeight/2 * gNbOfRobots;
        // for ( int i = 0 ; i != gNbOfRobots ; i++ )
        // {
        //     SwapWalkController *cont = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
        //     x_avg += cont->getWorldModel()->_xReal;
        //     y_avg += cont->getWorldModel()->_yReal;
        //     if(cont->_isAttracted)
        //         _countAttracted++;
        //     phase += cont->getWorldModel()->getRobotLED_blueValue();
        // }
        // x_avg /= gNbOfRobots;
        // y_avg /= gNbOfRobots;
        // x_avg = (x_avg);
        // y_avg = (y_avg);
        // phase /= gNbOfRobots;
        // std::cout << "[INFO] phase: " << phase << ";\t" << _countAttracted << " in attracted mode;\tbarycenter moved to [" << x_avg << ", "<< y_avg <<"].\r";
       // std::cout << x_avg + y_avg << "\t" << _countAttracted << "\n";
        // std::string sLog = std::to_string(x_avg + y_avg) + "\t" + std::to_string( (_countAttracted>4)*100 ) + "\n";
        // gLogManager->write(sLog);
    }

}

void SwapWalkWorldObserver::periodize()
{ 
    for ( int i = 0 ; i != gNbOfRobots/9 ; i++ )
    {

        // put the robots from the middle in the middle
        Robot *rob = gWorld->getRobot(i);
        SwapWalkController *cont = (dynamic_cast<SwapWalkController*>(rob->getController()));
        double new_x = (cont->getWorldModel()->_xReal);
        double new_y = (cont->getWorldModel()->_yReal);
        new_x += (new_x >= gScreenWidth *0.65) ? -gScreenWidth *0.3 : (new_x < gScreenWidth *0.35) ? gScreenWidth *0.3 : 0;
        new_y += (new_y >= gScreenHeight*0.65) ? -gScreenHeight*0.3 : (new_y < gScreenHeight*0.35) ? gScreenHeight*0.3 : 0;
        cont->getWorldModel()->_xReal =  new_x;
        cont->getWorldModel()->_yReal =  new_y;


        // copy them 8 times
        RobotWorldModel *wmTL = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + gNbOfRobots/9)->getController()))->getWorldModel();
        wmTL->_xReal = new_x + 0.3 * gScreenWidth;
        wmTL->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmTM = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 2*gNbOfRobots/9)->getController()))->getWorldModel();
        wmTM->_xReal = new_x;
        wmTM->_yReal = new_y + 0.3 * gScreenHeight;
        RobotWorldModel *wmTR = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 3*gNbOfRobots/9)->getController()))->getWorldModel();
        wmTR->_xReal = new_x + 0.3 * gScreenWidth;
        wmTR->_yReal = new_y + 0.3 * gScreenHeight;
        RobotWorldModel *wmML = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 4*gNbOfRobots/9)->getController()))->getWorldModel();
        wmML->_xReal = new_x - 0.3 * gScreenWidth;
        wmML->_yReal = new_y;
        RobotWorldModel *wmMR = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 5*gNbOfRobots/9)->getController()))->getWorldModel();
        wmMR->_xReal = new_x + 0.3 * gScreenWidth;
        wmMR->_yReal = new_y;
        RobotWorldModel *wmBL = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 6*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBL->_xReal = new_x - 0.3 * gScreenWidth;
        wmBL->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmBM = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 7*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBM->_xReal = new_x;
        wmBM->_yReal = new_y - 0.3 * gScreenHeight;
        RobotWorldModel *wmBR = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i + 8*gNbOfRobots/9)->getController()))->getWorldModel();
        wmBR->_xReal = new_x - 0.3 * gScreenWidth;
        wmBR->_yReal = new_y + 0.3 * gScreenHeight;
    }
}

void SwapWalkWorldObserver::monitorPopulation()
{
    std::list<int> availibleGID;
    for(int i = 1; i<gNumberOfRobotGroups; i++)
        availibleGID.push_back(i);
    std::map< int,std::list<int> > cc;
    std::map< int, double > radii;

    int e = 0; // # of robots in landmark 0
    double clusterSquaredDist = 25;
    for(int i = 0; i<gNbOfRobots; i++){
        SwapWalkController *Ci = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
        RobotWorldModel *Ri = Ci->getWorldModel();
        Ri->setRobotLED_colorValues((!Ci->_isAttracted) * 255,(Ci->_isAttracted) * 255,0);
        availibleGID.remove(Ri->getGroupId());
        // Ri->setRobotLED_colorValues(rand()%255,rand()%255,rand()%255);
        // e += (Ri->getLandmarkDistanceValue()<1);
        if(Ci->_isAttracted){
            cc[i] = std::list<int>(1,i);
            for(int j = 0; j<gNbOfRobots; j++)
                if( j!=i && (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->_isAttracted )
                {
                    RobotWorldModel *Rj = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
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
                       
    }
    
    int heapSize = 0;
    int heapCount = 0;

    for(int i = 0; i<gNbOfRobots; i++){
        if(cc[i].size() > 3){
            double radius = 0;
            double cx = 0;
            double cy = 0;
            cc[i].sort();
            cc[i].unique();
            heapCount ++;
            heapSize += (cc[i].size());

            // find corresponding cc
            int gid = -1;
            for (int j : cc[i]){
                RobotWorldModel* temp = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
                if(temp->getGroupId() != 0 && temp->getGroupId()<11)
                    gid = temp->getGroupId();
                cx += temp->_xReal;
                cy += temp->_yReal;
            }
            cx /= cc[i].size();
            cy /= cc[i].size();

            if(gid==-1 || (gid>10 && cc[i].size() > 19)){
                // try to find it among empty spaces
                if(!availibleGID.empty()){
                    gid = availibleGID.front();
                    availibleGID.pop_front();
                }else{
                    gid = gNumberOfRobotGroups;
                    gNumberOfRobotGroups++;
                }
            }

            //SwapWalkController *Ci = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
            //Ci->getWorldModel()->setRobotLED_colorValues((!Ci->_isAttracted) * 255,100+rand()%155,100+rand()%155);
            for (int j : cc[i]){
                SwapWalkController *Cj = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()));
                Cj->getWorldModel()->setGroupId(gid);
                if(j!=i)
                    cc[j] = std::list<int>(1,i);
                radius += getSquaredEuclidianDistance(cx,cy,Cj->getWorldModel()->_xReal,Cj->getWorldModel()->_yReal);
             //   Cj->getWorldModel()->setRobotLED_colorValues((!Cj->_isAttracted) * 255, Ci->getWorldModel()->getRobotLED_greenValue(), Ci->getWorldModel()->getRobotLED_blueValue());
            }
            radii[gid] = radius / cc[i].size();
        }
    }
    for(int i = 0; i<gNbOfRobots; i++)
        if(cc[cc[i].front()].size() < 5)
            (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel()->setGroupId(0);


    std::string sLog = std::to_string(heapCount) + std::string("\t") + std::to_string(heapSize);

    std::map< int,int > gs;
    for(int i = 0; i<gNbOfRobots; i++){
        gs[(dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel()->getGroupId()]++;
    }

    int curr = 0;
    while (!gs.empty())
    {
        if(gs.begin()->first != 0 && gs.begin()->second>=20 && gs.begin()->first<=10){//
            for(int i = curr+1; i<gs.begin()->first; i++)
                sLog += "\t0\t0";
            curr = gs.begin()->first;
            sLog += "\t"+std::to_string(gs.begin()->second)+"\t"+std::to_string(radii[gs.begin()->first]);
        }
        // std::cout << gs.begin()->first << " => " << gs.begin()->second << '\n';
        gs.erase(gs.begin());
    }


    // for(int i = 0; i<gNbOfRobots; i++){
    //     if(cc[i].size() > 3){
    //         sizes.push_back(cc[i].size());
    //     }
    // }
    // sizes.sort(std::greater<int>());
    // for(int i : sizes){
    //     std::cout<<" "<<i;
    // }

    // std::cout<<"\n";

    // int i = 0;
    // for(std::list<int>::iterator it = sizes.begin(); it!=sizes.end() && i<5 ; it++){
    //     i++;
    //     sLog += "\t" + std::to_string(*it);
    // }
    gLogManager->write(sLog + "\n");

    // for( int i = 0; i<gNbOfRobots; i++ ){
    //     std::cout<<"\n\t"<<i<<": [";
    //     for(int j : cc[i])
    //         std::cout<<"\t"<<j;
    //     std::cout<<"   ]";
    // }

// gNumberOfRobotGroups
}