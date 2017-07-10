/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "SwapWalk/include/SwapWalkWorldObserver.h"

#include "World/World.h"

#include "SwapWalk/include/SwapWalkController.h"

SwapWalkWorldObserver::SwapWalkWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;

    // ==== loading project-specific properties

    gProperties.checkAndGetPropertyValue("gCenterX",&SwapWalkSharedData::gCenterX,true);
    gProperties.checkAndGetPropertyValue("gCenterY",&SwapWalkSharedData::gCenterY,true);
    gProperties.checkAndGetPropertyValue("gBalance",&SwapWalkSharedData::gBalance,true);
    gProperties.checkAndGetPropertyValue("gSwapRate",&SwapWalkSharedData::gSwapRate,true);
    gProperties.checkAndGetPropertyValue("gSnapshots",&SwapWalkSharedData::gSnapshots,true);
    gProperties.checkAndGetPropertyValue("gErrorRate",&SwapWalkSharedData::gErrorRate,true);
    gProperties.checkAndGetPropertyValue("gAcceptance",&SwapWalkSharedData::gAcceptance,true);
    gProperties.checkAndGetPropertyValue("gKeptGroups",&SwapWalkSharedData::gKeptGroups,true);
    gProperties.checkAndGetPropertyValue("gEnergyRadius",&SwapWalkSharedData::gEnergyRadius,true);
    gProperties.checkAndGetPropertyValue("gListeningState",&SwapWalkSharedData::gListeningState,true);
    gProperties.checkAndGetPropertyValue("gEvaluationTime",&SwapWalkSharedData::gEvaluationTime,true);
    gProperties.checkAndGetPropertyValue("gAngleFuzziness",&SwapWalkSharedData::gAngleFuzziness,true);
    gProperties.checkAndGetPropertyValue("gBiasSpeedDelta",&SwapWalkSharedData::gBiasSpeedDelta,true);
    gProperties.checkAndGetPropertyValue("gSnapshotFrequency",&SwapWalkSharedData::gSnapshotFrequency,true);

    std::string id = std::to_string(gRandomSeed % 10);
    std::string title = std::to_string(gInitialNumberOfRobots)+" bots, swapRate:"+std::to_string(SwapWalkSharedData::gSwapRate)
        + " #"+id;
    SDL_SetWindowTitle(gScreenWindow, title.c_str());
    gLogManager->write("#\t"+title+"\n");

    std::string header = "inGroup"+ id +"\tperGroup"+ id +"\tattracted"+ id +"\tgAttracted"+ id +"\tmeanSquaredRadius"+ id;
    // for(int i = 0; i<SwapWalkSharedData::gKeptGroups; i++)
        // header += "\tgroup"+std::to_string(i)+'_'+id+"\tradius"+std::to_string(i)+'_'+id;
    gLogManager->write(header+"\n");
    

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
    // if ( SwapWalkSharedData::gEvaluationTime>0 && gWorld->getIterations() % SwapWalkSharedData::gEvaluationTime == 0 ){ //  
    //     monitorPopulation();
    // }

    if ( SwapWalkSharedData::gSnapshots ){
        if( gWorld->getIterations() % SwapWalkSharedData::gSnapshotFrequency == 0 ){
            std::cout << "[INFO] Starting video recording #" << gWorld->getIterations() / SwapWalkSharedData::gSnapshotFrequency << "\n";
            gDisplayMode = 0;
            gVideoRecording = true;
        }
        if( gWorld->getIterations() % SwapWalkSharedData::gSnapshotFrequency == 1 ){ // SwapWalkSharedData::gEvaluationTime
            gVideoRecording = false;
            gDisplayMode = 2;
            std::cout << "[INFO] Ended video recording #" << gWorld->getIterations() / SwapWalkSharedData::gSnapshotFrequency << "\n";
        }
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
    int inGroup = 0;
    int perGroup = 0;
    int attracted = 0;
    int gAttracted = 0;
    double meanSquaredRadius = 0;

    // int heapSize = 0;
    // int heapCount = 0;

    std::list<int> availibleGID;
    for(int i = 1; i<gNumberOfRobotGroups; i++)
        availibleGID.push_back(i);
    std::map< int,std::list<int> > cc;

    // int tilesize = gSensorRange;
    // int ntiles = gScreenWidth / tilesize + 1;
    // std::vector< int > tile (ntiles*ntiles, 0);
    // std::vector<int> ld(gInitialNumberOfRobots,1);
    // std::map< int, double > radii;
    std::vector<double> avg_dist (gInitialNumberOfRobots, 0.);
    // std::vector<double> ring_dist (gScreenWidth / 20, 0.);
    // std::vector<int> ninr (gScreenWidth / 20, 0);

    //double clusterSquaredDist = 400;
    unsigned int groupMinSize = 20;

    for(int i = 0; i<gNbOfRobots; i++){ 
        SwapWalkController *Ci = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
        RobotWorldModel *Ri = Ci->getWorldModel();
        // Ri->setRobotLED_colorValues((!Ci->_isAttracted) * 255,(Ci->_isAttracted) * 255,0);
        availibleGID.remove(Ri->getGroupId());
        if(Ci->_isAttracted)
            attracted ++;
       // if(Ci->_isAttracted){
        cc[i] = std::list<int>(1,i);

        // put it in local tile
        // int x = Ri->_xReal;
        // int y = Ri->_yReal;
        // tile[ntiles*(x/tilesize)+(y/tilesize)]++;

        // O(n) version
        
        unsigned int ct = 0;
        for(int k = 0; k < Ri->_cameraSensorsNb; k++)
        {
            int j = Ri->getObjectIdFromCameraSensor(k);
            if ( j >= gRobotIndexStartOffset && j < gRobotIndexStartOffset+gNbOfRobots )
            {
                j -= gRobotIndexStartOffset; // convert image registering index into robot id.
                RobotWorldModel *Rj = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
                double dist = pow(Ri->_xReal - Rj->_xReal, 2) + pow(Ri->_yReal - Rj->_yReal, 2);
            //    if( dist < clusterSquaredDist ){
                    avg_dist[i] += dist;
                    ct ++;

                    int ccOfJ = j;
                    
                    while( !cc[ccOfJ].empty() && cc[ccOfJ].front() != ccOfJ ){
                        int buf = ccOfJ;
                        ccOfJ = cc[ccOfJ].front();
                        cc[buf] = std::list<int> (1,i);
                    }
                    if(ccOfJ != i){
                        if(cc[ccOfJ].empty())
                            cc[i].push_back(ccOfJ);
                        else{
                            for( int k : cc[ccOfJ] )
                                cc[i].push_back(k);
                        }
                        cc[ccOfJ] = std::list<int> (1,i);
                    }
            //    }
            }
        }
        if(ct != 0)
            avg_dist[i] /= ct;

        // // O(n²) version, approx. 10% slower w/ 1800 bots on 1:50 evals
        // for(int j = 0; j<gNbOfRobots; j++)
        //     if( j!=i /*&& (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->_isAttracted*/ )
        //     {
        //         RobotWorldModel *Rj = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
        //         if( pow(Ri->_xReal - Rj->_xReal, 2) + pow(Ri->_yReal - Rj->_yReal, 2) < clusterSquaredDist ){
        //             int ccOfJ = j;
                    
        //             while( !cc[ccOfJ].empty() && cc[ccOfJ].front() != ccOfJ ){
        //                 int buf = ccOfJ;
        //                 ccOfJ = cc[ccOfJ].front();
        //                 cc[buf] = std::list<int> (1,i);
        //             }
        //             if(ccOfJ != i){
        //                 if(cc[ccOfJ].empty())
        //                     cc[i].push_back(ccOfJ);
        //                 else{
        //                     for( int k : cc[ccOfJ] )
        //                         cc[i].push_back(k);
        //                 }
        //                 cc[ccOfJ] = std::list<int> (1,i);
        //             }
        //         }
        //     }
        //                  
    }

    for(int i = 0; i<gNbOfRobots; i++){
        cc[i].sort();
        cc[i].unique();
        if(cc[i].size() >= groupMinSize){
            inGroup += cc[i].size();
            // SwapWalkController *Ci = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
            // Ci->getWorldModel()->setRobotLED_colorValues((!Ci->_isAttracted) * 255,100+rand()%155,100+rand()%155);
            for (int j : cc[i]){
                SwapWalkController *Cj = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()));
                //RobotWorldModel* _wm = Cj->getWorldModel();
                // Cj->getWorldModel()->setRobotLED_colorValues(
                //     (!Cj->_isAttracted) * 255,
                //     Ci->getWorldModel()->getRobotLED_greenValue(),
                //     Ci->getWorldModel()->getRobotLED_blueValue());
                if(Cj->_isAttracted)
                    gAttracted++;

                // int fpdnbNeighbours = 0;
                // double fpdarea = _wm->_cameraSensorsNb; // proxy for area around center
                // for( int i = 0 ; i < _wm->_cameraSensorsNb ; i++)
                // {
                //     int fpdtargetRawIndex = _wm->getObjectIdFromCameraSensor(i);
                //     if ( fpdtargetRawIndex >= gRobotIndexStartOffset )   // sensor ray bumped into a robot -- WARNING: one (very close) neighbor can be seen by more than one sensor (in the following, we dont care if this happen, though it is not correct to do so)
                //     {
                //         //int fpdtargetRobotIndex = fpdtargetRawIndex - gRobotIndexStartOffset; // convert image registering index into robot id.
                //         fpdnbNeighbours ++;
                //         double fpddist = _wm->getNormalizedDistanceValueFromCameraSensor( i );
                //         fpdarea += (fpddist - 1);
                //     }
                // }
                
                // int td = tile[ntiles*((int)_wm->_xReal/tilesize)+((int)_wm->_yReal/tilesize)];
                // int t = (int)(_wm->_xReal/tilesize) + (int)(_wm->_yReal/tilesize);

                meanSquaredRadius += avg_dist[j];


                // int ring = sqrt(pow(Cj->getWorldModel()->_xReal - gScreenWidth/2 , 2) + pow(Cj->getWorldModel()->_yReal - gScreenWidth/2 , 2)) / 10;
                // ring_dist[ring] += avg_dist[j];
                // ninr[ring]++;

                // cloudDensity += (1. + fpdnbNeighbours) / fpdarea; // proxy using distance to visible neighbors
                // cloudDensity += td; // proxy using density in tiles of size SensorRange
                // cloudDensity += ld[j]; // proxy using count of visible neighbors

                // _wm->setRobotLED_colorValues(td*25,255 - td*20, t%2 * 255);
                }


            // double radius = 0;
            // double cx = 0;
            // double cy = 0;
            perGroup ++; //initially stores number of groups, will be revered further down
            // heapCount ++;
            // heapSize += (cc[i].size());

            // find corresponding cc
        /*    int gid = -1;
            for (int j : cc[i]){
                RobotWorldModel* temp = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(j)->getController()))->getWorldModel();
                if(temp->getGroupId() != 0)
                    gid = temp->getGroupId();
                if(temp->getGroupId() != 0 && temp->getGroupId()<=SwapWalkSharedData::gKeptGroups)
                    break;
                // cx += temp->_xReal;
                // cy += temp->_yReal;
            }
            // cx /= cc[i].size();
            // cy /= cc[i].size();

            if(gid==-1 || (!availibleGID.empty() && gid > SwapWalkSharedData::gKeptGroups && cc[i].size() > groupMinSize)){
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
        //        radius += getSquaredEuclidianDistance(cx,cy,Cj->getWorldModel()->_xReal,Cj->getWorldModel()->_yReal);
             //   Cj->getWorldModel()->setRobotLED_colorValues((!Cj->_isAttracted) * 255, Ci->getWorldModel()->getRobotLED_greenValue(), Ci->getWorldModel()->getRobotLED_blueValue());
            }
            // radii[gid] = radius / cc[i].size();*/
        }
    }

    //TODO compute cloud density here

    for(int i = 0; i<gNbOfRobots; i++){
        SwapWalkController* temp = (dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()));
        RobotWorldModel* _wm = temp->getWorldModel();
        if(cc[cc[i].front()].size() < groupMinSize){
            _wm->setGroupId(0);
            if (temp->_isAttracted)
                attracted ++;
        }
        else{ // VERY rarely used
            _wm->setGroupId(1);
           // inGroup++;
            if (temp->_isAttracted){
                
                attracted ++;
            }



        }
        
    }

    if(perGroup>0){
        perGroup = inGroup / perGroup;
        meanSquaredRadius /= inGroup;
    }
    std::string sLog = std::to_string(inGroup) +"\t"+ std::to_string(perGroup) +"\t"+ std::to_string(attracted/2) +"\t"+ std::to_string(gAttracted) +"\t"+ std::to_string(meanSquaredRadius);

    // std::string sLog = std::to_string(heapCount) + std::string("\t") + std::to_string(heapSize);
    // std::map< int,int > gs;
    // for(int i = 0; i<gNbOfRobots; i++){
    //     gs[(dynamic_cast<SwapWalkController*>(gWorld->getRobot(i)->getController()))->getWorldModel()->getGroupId()]++;
    // }
    // int curr = 0;
    // while (!gs.empty())
    // {
    //     if( gs.begin()->first != 0 && gs.begin()->second >= 20 && gs.begin()->first <= SwapWalkSharedData::gKeptGroups ){//
    //         for(int i = curr+1; i<gs.begin()->first; i++)
    //             sLog += "\t0\t0";
    //         curr = gs.begin()->first;
    //         sLog += "\t"+std::to_string(gs.begin()->second)+"\t"+std::to_string(radii[gs.begin()->first]);
    //     }
    //     // std::cout << gs.begin()->first << " => " << gs.begin()->second << '\n';
    //     gs.erase(gs.begin());
    // }


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

    // gLogManager->write(sLog + "\n");
    // if(gWorld->getIterations() == 2000)
    //     for(int i = 0; i<gScreenWidth/20; i++)
    //         std::cout<<(ring_dist[i]/ninr[i])<<"\n";
}
