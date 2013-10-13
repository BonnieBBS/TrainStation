#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <string>
#include <stdio.h>
#include <string.h>

#define TrainBo
#define num_of_categories 5 // Require number of categories
#define num_of_trains 2000 // max number of trains
#define num_of_trackgroups 15 // max number of track groups
#define typedGate std::pair<int, void*> // A0 B1 F5 P15 S18 T19 Y24
//typedef std::pair<int, int> reustPair;

#ifdef TrainBo

namespace bonnie
{
    // Reuse
    typedef std::pair<int,int> reusePair;

    std::vector<reusePair> reusePairsvec;

    void readReusePairs(FILE * pFile)
    {
        reusePair temp;
        fscanf(pFile, "Arr%d;Dep%d;\n", &temp.first, &temp.second);
        reusePairsvec.push_back(temp);
    }

    void showReusePairs()
    {
        std::cout << "SHOW reusePairs:\n";
        for(std::vector<reusePair>::iterator it=reusePairsvec.begin(); it!=reusePairsvec.end(); it++)
        {
            std::cout << "arrival " << (*it).first
                << " departure " << (*it).second << std::endl;
        }
    }

    // parameters

    tm junTime, disjTime, revTime, minAsbTime, minResTime, maxDwellTime;
    int junCost, disjCost, platAsgCost, reuseCost, nbDays, maxMaint;
    double remDCost, remTCost, dwellCost;

    void readParameters()
    {
    }

    void showParameters()
    {
    }

    struct arrivals
    {
        tm time;
        tm idealDwell;
        tm maxDwell;
        int arrivalID;
        int trainID;
        int category; // 1-4
        int remDBM;
        tm remTBM;
        int arrSeq;
        int jointArr;
        int dep;
    };

    struct categories
    {
        int id;
        int length;
        int catGroup;
        int maxDBM;
        tm maxTBM;
        tm maintTimeD;
        tm maintTimeT;
    };

    struct initialIns
    {
        int trainID;
        int category;
        char currentResource[30];
        int remDBM;
        tm remTBM;
    };


    class Train
    {
        private:
            int trainID;
            int trainCategory;
            char * currentResource[30];
            int remDBM;
            tm remTBM;
            arrivals arrival;
            initialIns initialIn;

        public:
            Train()
            {
            }

            ~Train()
            {
            }

            void readInitialIns(FILE * pFile)
            {
                fscanf(pFile, "Train%d;Cat%d;", &initialIn.trainID, &initialIn.category);
                int i=0;
                char c;
                while(true)
                {
                    c = fgetc(pFile);
                    //std::cout << c;
                    initialIn.currentResource[i++] = c;
                    if(c==';') break;
                }
                fscanf(pFile, "%d;%d:%d:%d;\n", &initialIn.remDBM, &initialIn.remTBM.tm_hour, &initialIn.remTBM.tm_min, &initialIn.remTBM.tm_sec);
                getInitialIn();
            }

            void getInitialIn()
            {
                std::cout << initialIn.trainID << " " << initialIn.category << std::endl;
                std::cout << initialIn.currentResource  << std::endl;
                std::cout << initialIn.remDBM  << initialIn.remTBM.tm_min << std::endl;
            }

            // waiting for revision: reusepair -> connect arrival with ideal departure
            void readArrivals(FILE * pFile) 
            {
                fscanf(pFile, "Arr%d;Train%d;", &arrival.arrivalID, &arrival.trainID);
                fscanf(pFile, "d%d %d:%d:%d;", &arrival.time.tm_mday, &arrival.time.tm_hour, &arrival.time.tm_min, &arrival.time.tm_sec);
                fscanf(pFile, "ArrSeq%d;", &arrival.arrSeq);
                char c;
                c = fgetc(pFile);
                if(c==';') arrival.jointArr = -1;
                else fscanf(pFile, "ointArr%d;", &arrival.jointArr);
                c = fgetc(pFile);
                if(c==';') arrival.dep = -1;
                else fscanf(pFile, "ep%d", &arrival.dep); 
                fscanf(pFile, "Cat%d;", &arrival.category);
                fscanf(pFile, "%d:%d:%d;", &arrival.idealDwell.tm_hour, &arrival.idealDwell.tm_min, &arrival.idealDwell.tm_sec);
                fscanf(pFile, "%d:%d:%d;", &arrival.maxDwell.tm_hour, &arrival.maxDwell.tm_min, &arrival.maxDwell.tm_sec);
                fscanf(pFile, "%d;", &arrival.remDBM);
                fscanf(pFile, "%d:%d:%d;\n", &arrival.remTBM.tm_hour, &arrival.remTBM.tm_min, &arrival.remTBM.tm_sec);
            }

            void getArrival()
            {
                std::cout << arrival.arrivalID << " " << arrival.trainID << "\n";
                std::cout << arrival.time.tm_mday << " " << arrival.time.tm_hour <<  " " << arrival.time.tm_min << " " << arrival.time.tm_sec << std::endl;
                std::cout << arrival.arrSeq << " " << arrival.jointArr << " " << arrival.dep << " " << arrival.category << "\n ";
                std::cout << arrival.idealDwell.tm_hour << " " << arrival.idealDwell.tm_min << " " << arrival.idealDwell.tm_sec << std::endl;
                std::cout << arrival.maxDwell.tm_hour << " " << arrival.maxDwell.tm_min << " " << arrival.maxDwell.tm_sec << std::endl;
                std::cout << arrival.remDBM << std::endl;
                std::cout << arrival.remTBM.tm_hour << " " << arrival.remTBM.tm_min << " " << arrival.remTBM.tm_sec << std::endl;
            }


            void getCategory(int n)
            {
                // print infomation of allCategories[n]
            }
    };

    struct trainCategories
    {
        int id;
        int length;
        int catGroup;
        int maxDBM;
        tm maxTBM;
        tm maintTimeD;
        tm maintTimeT;
    };

    std::vector<trainCategories> trainCategoriesvec; // trainCategories.id = vector[id-1]

    void readTrainCategories(FILE * pFile)
    {   
        trainCategories temp;
        fscanf(pFile, "Cat%d;", &temp.id);
        fscanf(pFile, "%d;CatGroup%d;%d;", &temp.length, &temp.catGroup, &temp.maxDBM);
        fscanf(pFile, "%d:%d:%d;", &temp.maxTBM.tm_hour, &temp.maxTBM.tm_min, &temp.maxTBM.tm_sec);
        fscanf(pFile, "%d:%d:%d;", &temp.maintTimeD.tm_hour, &temp.maintTimeD.tm_min, &temp.maintTimeD.tm_sec);
        fscanf(pFile, "%d:%d:%d;\n", &temp.maintTimeT.tm_hour, &temp.maintTimeT.tm_min, &temp.maintTimeT.tm_sec);
        trainCategoriesvec.push_back(temp);
    }   

    void showTrainCategories()
    {   
        std::cout << "SHOW trainCategoriesS:\n";
        for(std::vector<trainCategories>::iterator it=trainCategoriesvec.begin(); it!=trainCategoriesvec.end(); it++)
        {   
            std::cout << "trainCategoriesid " << (*it).id 
                << " maintTimeDMin " << (*it).maintTimeD.tm_min 
                << " maintTimeTMin " << (*it).maintTimeT.tm_min << std::endl;
        }
    }       


    /****************************************** RESOURCES ************************************************/


    struct trackGroups
    {
        int id;
        tm trTime;
        tm hwTime;
        std::vector<typedGate> gatesA, gatesB;
    };

    std::vector<trackGroups> trackGroupsvec;

    void readTrackGroups(FILE * pFile)
    {   
        trackGroups temp;
        fscanf(pFile, "TrackGroup%d;", &temp.id);
        fscanf(pFile, "%d:%d:%d;", &temp.trTime.tm_hour, &temp.trTime.tm_min, &temp.trTime.tm_sec);
        fscanf(pFile, "%d:%d:%d;\n", &temp.hwTime.tm_hour, &temp.hwTime.tm_min, &temp.hwTime.tm_sec);
        trackGroupsvec.push_back(temp);
    }   

    void showTrackGroups()
    {   
        std::cout << "SHOW trackGroupsS:\n";
        for(std::vector<trackGroups>::iterator it=trackGroupsvec.begin(); it!=trackGroupsvec.end(); it++)
        {   
            std::cout << "trackGroupsid " << (*it).id 
                << " trTimeMin " << (*it).trTime.tm_min 
                << " hwTimeMin " << (*it).hwTime.tm_min << std::endl;
        }
        std::cout << "SHOW trackGroups is over\n";
    }       


    struct platform
    {
        int id;
        int length;
        std::vector<typedGate> gatesA, gatesB;
    };
    std::vector<platform> platformsvec;

    void readPlatforms(FILE * pFile)
    {
        platform temp;
        fscanf(pFile, "Platform%d;%d;\n", &temp.id, &temp.length);
        platformsvec.push_back(temp);
    }   

    void showPlatforms()
    {   
        std::cout << "SHOW platformS:\n";
        for(std::vector<platform>::iterator it=platformsvec.begin(); it!=platformsvec.end(); it++)
        {
            std::cout << "platformid " << (*it).id << " length " << (*it).length << std::endl;
        }
    }   


    struct facility
    {
        int id;
        char type;
        int length;
        std::vector<typedGate> gatesA, gatesB;
    };

    std::vector<facility> facilitiesvec;

    void readFacilities(FILE * pFile)
    {   
        facility temp;
        fscanf(pFile, "Facility%d;%c;%d;\n", &temp.id, &temp.type, &temp.length);
        facilitiesvec.push_back(temp);
    }   

    void showFacilities()
    {   
        std::cout << "SHOW facilityS:\n"; 
        for(std::vector<facility>::iterator it=facilitiesvec.begin(); it!=facilitiesvec.end(); it++)
        {   
            std::cout << "facilityid " << (*it).id << 
                " type " << (*it).type << " length " << (*it).length << std::endl;
        }
    }   

    struct singleTrack
    {
        int id;
        int length;
        int capa;
        std::vector<typedGate> gatesA, gatesB;
    };

    std::vector<singleTrack> singleTracksvec;

    void readSingleTracks(FILE * pFile)
    {
        singleTrack temp;
        fscanf(pFile, "SingleTrack%d;%d;%d;\n", &temp.id, &temp.length, &temp.capa);
        singleTracksvec.push_back(temp);
    }

    void showSingleTracks()
    {
        std::cout << "SHOW SingleTrackS:\n";
        for(std::vector<singleTrack>::iterator it=singleTracksvec.begin(); it!=singleTracksvec.end(); it++)
        {
            std::cout << "SingleTrackid " << (*it).id 
                << " length " << (*it).length
                << " capa " << (*it).capa << std::endl;
        }
    }


    struct yard
    {
        int id;
        int capa;
        std::vector<typedGate> gatesA, gatesB;
    };

    std::vector<yard> yardsvec;

    void readYards(FILE * pFile)
    {
        yard temp;
        fscanf(pFile, "Yard%d;%d;\n", &temp.id, &temp.capa);
        yardsvec.push_back(temp);
    }

    void showYards()
    {
        std::cout << "SHOW YARDS:\n";
        for(std::vector<yard>::iterator it=yardsvec.begin(); it!=yardsvec.end(); it++)
        {
            std::cout << "yardid " << (*it).id << " capa " << (*it).capa << std::endl;
        }
    }

    char rGateSide, nGateSide;
    int rNum, nNum, rGatei, nGatei;
    void * neighbour;

    void readGates(FILE * pFile)
    {
        char rc, nc;
        rc = fgetc(pFile);
        switch(rc) // Can we simplify them by getting methods out?
        {
            case 'F':
                {
                    fscanf(pFile,"acility%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switch(nc)
                    {
                        case 'F':
                            fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &facilitiesvec[nNum-1]; 
                            break;
                        case 'T':
                            fscanf(pFile, "rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &trackGroupsvec[nNum-1]; 
                            break;
                        case 'P':
                            fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &platformsvec[nNum-1];
                            break;
                        case 'S':
                            fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &singleTracksvec[nNum-1];
                            break;
                        case 'Y':
                            fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &yardsvec[nNum-1];
                            break;
                        default:
                            std::cout << "It has no neighbour\n";
                            nc = 'A'-1;
                            neighbour = NULL;
                            break;
                    }
                    facility * resource =  & facilitiesvec[rNum-1];
                    typedGate temp;
                    temp.first = nc-'A';
                    temp.second = neighbour;
                    if(rGateSide-'A') (*resource).gatesB.push_back(temp);
                    else (*resource).gatesA.push_back(temp);
                    break;
                }

            case 'P':
                {
                    fscanf(pFile, "latform%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switch(nc)
                    {
                        case 'F':
                            fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &facilitiesvec[nNum-1]; 
                            break;
                        case 'P':
                            fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &platformsvec[nNum-1];
                            break;
                        case 'T':
                            fscanf(pFile,"rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &trackGroupsvec[nNum-1];
                            break;
                        case 'S':
                            fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &singleTracksvec[nNum-1];
                            break;
                        case 'Y':
                            fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &yardsvec[nNum-1];
                            break;
                        default:
                            std::cout << "It has no neighbour\n";
                            nc = 'A'-1;
                            neighbour = NULL;
                            break;
                    }
                    platform * resource =  & platformsvec[rNum-1];
                    typedGate temp;
                    temp.first = nc-'A';
                    temp.second = neighbour;
                    if(rGateSide-'A') (*resource).gatesB.push_back(temp);
                    else (*resource).gatesA.push_back(temp);
                    break;
                }

            case 'S':
                {
                    fscanf(pFile, "ingleTrack%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switch(nc)
                    {
                        case 'F':
                            fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &facilitiesvec[nNum-1]; 
                            break;
                        case 'P':
                            fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &platformsvec[nNum-1];
                            break;
                        case 'S':
                            fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &singleTracksvec[nNum-1];
                            break;
                        case 'T':
                            fscanf(pFile,"rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &trackGroupsvec[nNum-1];
                            break;
                        case 'Y':
                            fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &yardsvec[nNum-1];
                            break;
                        default:
                            std::cout << "It has no neighbour\n";
                            nc = 'A'-1;
                            neighbour = NULL;
                            break;
                    }
                    singleTrack * resource =  & singleTracksvec[rNum-1];
                    typedGate temp;
                    temp.first = nc-'A';
                    temp.second = neighbour;
                    if(rGateSide-'A') (*resource).gatesB.push_back(temp);
                    else (*resource).gatesA.push_back(temp);
                    break;
                }

            case 'T':
                {
                    fscanf(pFile, "rackGroup%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switch(nc)
                    {
                        case 'F':
                            fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &facilitiesvec[nNum-1]; 
                            break;
                        case 'P':
                            fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &platformsvec[nNum-1];
                            break;
                        case 'S':
                            fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &singleTracksvec[nNum-1];
                            break;
                        case 'T':
                            fscanf(pFile,"rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &trackGroupsvec[nNum-1];
                            break;
                        case 'Y':
                            fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &yardsvec[nNum-1];
                            break;
                        default:
                            std::cout << "It has no neighbour\n";
                            nc = 'A'-1;
                            neighbour = NULL;
                            break;
                    }
                    trackGroups * resource =  & trackGroupsvec[rNum-1];
                    typedGate temp;
                    temp.first = nc-'A';
                    temp.second = neighbour;
                    if(rGateSide-'A') 
                    {
                        (*resource).gatesB.push_back(temp);
                    }
                    else
                    {
                        (*resource).gatesA.push_back(temp);
                    }
                    break;
                }

            case 'Y':
                {
                    fscanf(pFile, "ard%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switch(nc)
                    {
                        case 'F':
                            fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &facilitiesvec[nNum-1]; 
                            break;
                        case 'P':
                            fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &platformsvec[nNum-1];
                            break;
                        case 'S':
                            fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &singleTracksvec[nNum-1];
                            break;
                        case 'T':
                            fscanf(pFile,"rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &trackGroupsvec[nNum-1];
                            break;
                        case 'Y':
                            fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                            neighbour = (void*) &yardsvec[nNum-1];
                            break;
                        default:
                            std::cout << "It has no neighbour\n";
                            nc = 'A'-1;
                            neighbour = NULL;
                            break;
                    }
                    yard * resource =  & yardsvec[rNum-1];
                    typedGate temp;
                    temp.first = nc-'A';
                    temp.second = neighbour;
                    if(rGateSide-'A') (*resource).gatesB.push_back(temp);
                    else (*resource).gatesA.push_back(temp);
                    break;
                }
        }
    }

    static void showNeighbourFromGate(typedGate gate)
    {
        switch(gate.first)
        {
            case -1:
                std::cout << "The gate has no neighbour" << std::endl;
                break;
            case 5:
                std::cout << "The neighbour is Facility" << ((facility*)(gate.second))->id<< std::endl;
                break;
            case 15:
                std::cout << "The neighbour is Platform" << ((platform*)(gate.second))->id<< std::endl;
                break;
            case 18:
                std::cout << "The neighbour is SingleTrack" << ((singleTrack*)(gate.second))->id<< std::endl;
                break;
            case 19:
                std::cout << "The neighbour is TrackGroup" << ((trackGroups*)(gate.second))->id<< std::endl;
                break;
            case 24:
                std::cout << "The neighbour is Yard" << ((yard*)(gate.second))->id<< std::endl;
                break;
            default:
                std::cout << "The gate type is unknown..." << std::endl;
                break;
        }
    }

    static void ignoreFirstLine(FILE * pFile)
    {
        char mystring[200];
        if ( fgets (mystring , 200 , pFile) != NULL )
            puts ("Ignore the following line:");
        puts (mystring);
    }

}
#endif
