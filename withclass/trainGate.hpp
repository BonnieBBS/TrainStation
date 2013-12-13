#include <iostream>
#include <vector>
#include <set>
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
    /********************************* READING FILE METHODS ************************************/

    // read resource name from pFile and return the first character of resource name minus 'A'
    static int readResourceName(FILE * pFile)
    {
        char c,c0;
        c0 = fgetc(pFile);
        while(true)
        {
            c = fgetc(pFile);
            if(c==';') break;
        }
        return c0-'A';
    }

    // ignore the first line in pFile including the property names of the object
    static void ignoreFirstLine(FILE * pFile)
    {
        char mystring[200];
        if ( fgets (mystring , 200 , pFile) != NULL )
            puts ("Ignore the following line:");
        puts (mystring);
    }

    /******************************* Train Static Properties **************************************/

    // Reuse
    typedef std::pair<int,int> reusePair;

    class Reuse
    {
        public:
            reusePair rp;

            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "Arr%d;Dep%d;\n", &rp.first, &rp.second);
            }

            void print()
            {
                std::cout << "arrival " << rp.first
                    << " departure " << rp.second << std::endl;
            }
    };


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

    // arrDepSequences
    
    class ArrDepSequence
    {
        public:
            char type; // A or D
            int seqID, trackGroup, rankInSequence;
            ArrDepSequence(){}
            ~ArrDepSequence(){}
            
            void setupFromFile(FILE * pFile)
            {
               type = fgetc(pFile);
               fgetc(pFile);
               fgetc(pFile);
               fscanf(pFile, "Seq%d;TrackGroup%d;%d;\n", &seqID, &trackGroup, &rankInSequence);
            }

            void print()
            {
            }
    }; 
    
    std::vector<ArrDepSequence> arrDepSequencesVec;

    // Category Information

    class trainCategory
    {
        public:
            int id;
            int length;
            int catGroup;
            int maxDBM;
            tm maxTBM;
            tm maintTimeD;
            tm maintTimeT;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "Cat%d;", &id);
                fscanf(pFile, "%d;CatGroup%d;%d;", &length, &catGroup, &maxDBM);
                fscanf(pFile, "%d:%d:%d;", &maxTBM.tm_hour, &maxTBM.tm_min, &maxTBM.tm_sec);
                fscanf(pFile, "%d:%d:%d;", &maintTimeD.tm_hour, &maintTimeD.tm_min, &maintTimeD.tm_sec);
                fscanf(pFile, "%d:%d:%d;\n", &maintTimeT.tm_hour, &maintTimeT.tm_min, &maintTimeT.tm_sec);
            }   

            void print()
            {   
                std::cout << "trainCategoriesid " << id 
                    << " maintTimeDMin " << maintTimeD.tm_min 
                    << " maintTimeTMin " << maintTimeT.tm_min << std::endl;
            }       
    };

    /************************************* Train Dynamic Properties **************************************/

    class Arrival
    {
        public:
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
            int jointArrPosition;
            int dep;
            std::vector<int> prefPlats;

        public:
            Arrival() {}
            ~Arrival() {}

            // read a line in the pFile to get an Arrival info and assign them to 'arrivial'
            void setupFromFile(FILE * pFile) 
            {
                fscanf(pFile, "Arr%d;Train%d;", &arrivalID, &trainID);
                fscanf(pFile, "d%d %d:%d:%d;", &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);
                fscanf(pFile, "ArrSeq%d;", &arrSeq);
                char c;
                c = fgetc(pFile);
                if(c==';') jointArr = -1;
                else fscanf(pFile, "ointArr%d;", &jointArr);
                c = fgetc(pFile);
                if(c==';') dep = -1;
                else fscanf(pFile, "ep%d", &dep); 
                fscanf(pFile, "Cat%d;", &category);
                fscanf(pFile, "%d:%d:%d;", &idealDwell.tm_hour, &idealDwell.tm_min, &idealDwell.tm_sec);
                fscanf(pFile, "%d:%d:%d;", &maxDwell.tm_hour, &maxDwell.tm_min, &maxDwell.tm_sec);
                fscanf(pFile, "%d;", &remDBM);
                fscanf(pFile, "%d:%d:%d;\n", &remTBM.tm_hour, &remTBM.tm_min, &remTBM.tm_sec);
            }

            void print()//incomplete
            {
                std::cout << arrivalID << " " << trainID << "\n";
                std::cout << time.tm_mday << " " << time.tm_hour <<  " " << time.tm_min << " " << time.tm_sec << std::endl;
                std::cout << arrSeq << " " << jointArr << " " << dep << " " << category << "\n ";
                std::cout << idealDwell.tm_hour << " " << idealDwell.tm_min << " " << idealDwell.tm_sec << std::endl;
                std::cout << maxDwell.tm_hour << " " << maxDwell.tm_min << " " << maxDwell.tm_sec << std::endl;
                std::cout << remDBM << std::endl;
                std::cout << remTBM.tm_hour << " " << remTBM.tm_min << " " << remTBM.tm_sec << std::endl;
            }
    };

    class Departure // need revision
    {
        public:
            tm time;
            tm idealDwell;
            tm maxDwell;
            int arrivalID;
            int trainID;
            int category; // 1-4
            int remDBM;
            tm remTBM;
            int arrSeq;
            int jointDep;
            int jointDepPosition;
            int dep;
            std::vector<int> prefPlats;
            int compatibleCategory;

        public:
            Departure() {}
            ~Departure() {}

            // read a line in the pFile to get an Arrival info and assign them to 'arrivial'
            void setupFromFile(FILE * pFile) 
            {
                fscanf(pFile, "Arr%d;Train%d;", &arrivalID, &trainID);
                fscanf(pFile, "d%d %d:%d:%d;", &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);
                fscanf(pFile, "ArrSeq%d;", &arrSeq);
                char c;
                c = fgetc(pFile);
                if(c==';') jointDep = -1;
                else fscanf(pFile, "ointArr%d;", &jointDep);
                c = fgetc(pFile);
                if(c==';') dep = -1;
                else fscanf(pFile, "ep%d", &dep); 
                fscanf(pFile, "Cat%d;", &category);
                fscanf(pFile, "%d:%d:%d;", &idealDwell.tm_hour, &idealDwell.tm_min, &idealDwell.tm_sec);
                fscanf(pFile, "%d:%d:%d;", &maxDwell.tm_hour, &maxDwell.tm_min, &maxDwell.tm_sec);
                fscanf(pFile, "%d;", &remDBM);
                fscanf(pFile, "%d:%d:%d;\n", &remTBM.tm_hour, &remTBM.tm_min, &remTBM.tm_sec);
            }

            void print()//incomplete
            {
                std::cout << arrivalID << " " << trainID << "\n";
                std::cout << time.tm_mday << " " << time.tm_hour <<  " " << time.tm_min << " " << time.tm_sec << std::endl;
                std::cout << arrSeq << " " << jointDep << " " << dep << " " << category << "\n ";
                std::cout << idealDwell.tm_hour << " " << idealDwell.tm_min << " " << idealDwell.tm_sec << std::endl;
                std::cout << maxDwell.tm_hour << " " << maxDwell.tm_min << " " << maxDwell.tm_sec << std::endl;
                std::cout << remDBM << std::endl;
                std::cout << remTBM.tm_hour << " " << remTBM.tm_min << " " << remTBM.tm_sec << std::endl;
            }
    };

    std::vector<Arrival> allArrivalsVec;

    std::vector<Departure> allDeparturesVec;


    void setPrefPlats(std::string path) // was not tested!
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            ignoreFirstLine(pFile);
            char c;
            int a, b;
            while(true)
            {
                if(feof(pFile)) break;
                c = fgetc(pFile);
                if(c=='A')
                {
                    fscanf(pFile, "rr%d;Platform%d;\n", &a, &b);
                    allArrivalsVec[a-1].prefPlats.push_back(b);
                }
                if(c=='D')
                {
                    fscanf(pFile, "ep%d;Platform%d;\n", &a, &b);
                    allDeparturesVec[a-1].prefPlats.push_back(b);
                }

            }
            fclose(pFile);
        }
    }

    void setJointPosition(std::string path) // was not tested!
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            ignoreFirstLine(pFile);
            char c;
            int a, b;
            while(true)
            {
                if(feof(pFile)) break;
                for(int i=0; i<6; i++)
                    c = fgetc(pFile);
                int a, b, c;
                if(c=='A')
                {
                    fscanf(pFile, "rr%d;Arr%d;%d;\n", &a, &b, &c);
                    if(allArrivalsVec[b-1].jointArr != a)
                        std::cout << "JointArr does not correspond to Arr\n";
                    else
                        allArrivalsVec[b-1].jointArrPosition = c;
                }
                if(c=='D')
                {
                    fscanf(pFile, "rr%d;Arr%d;%d;\n", &a, &b, &c);
                    if(allDeparturesVec[b-1].jointDep != a)
                        std::cout << "JointDep does not correspond to Arr\n";
                    else
                        allDeparturesVec[b-1].jointDepPosition = c;
                }

            }
            fclose(pFile);
        }
    }

    void setCompCatDep(std::string path) // was not tested!
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            ignoreFirstLine(pFile);
            int depID, compCat;
            while(true)
            {
                if(feof(pFile)) break;
                fscanf(pFile, "Dep%d;Cat%d;\n", &depID, &compCat);
                allDeparturesVec[depID-1].compatibleCategory = compCat;
            }
            fclose(pFile);
        }
    }
    /******************************************** Train **********************************************/

    class Train
    {
        public:
            int trainID;
            int category;
            int currentResource;
            int remDBM;
            tm remTBM;
            int arrivalID;
            //need good variable for departure (reuse.csv, changable)
            std::string schedule;

        public:
            Train() {}
            ~Train() {}

            void print()
            {
                std::cout << "Train" << trainID 
                    << "\ntrainCategory: " << category 
                    << "\ncurrentResource: " << currentResource
                    << "\nremDBM: " << remDBM
                    << "\nremTBM: " << remTBM.tm_mday << " " 
                    << remTBM.tm_hour << ":" << remTBM.tm_min << ":" 
                    << remTBM.tm_sec << std::endl;
            }

            void getCategoryInfo()
            {
                // print infomation of allCategories[n]
            }

            void setupFromAnArrival(Arrival arr)
            {
                trainID = arr.trainID;
                category = arr.category;
                currentResource = -1; // use -1 to mark the train need more info from allArrivalsVec
                remDBM = arr.remDBM;
                remTBM = arr.remTBM;
                arrivalID = arr.arrivalID;
            }

            void setupTheInitialInTrainFromFile(FILE * pFile)
            {
                fscanf(pFile, "Train%d;Cat%d;", &trainID, &category);
                currentResource = readResourceName(pFile);
                fscanf(pFile, "%d;%d:%d:%d;\n", &remDBM, &remTBM.tm_hour, &remTBM.tm_min, &remTBM.tm_sec);
            }
    };


    /*************************** Vector Operation ****************************************/

    std::vector<Train> allTrainsVec;

    std::vector<trainCategory> allTrainCategoriesVec; // trainCategories.id = vector[id-1]

    std::vector<reusePair> reusePairsVec;

    // Initialize a class T vector(using REFERENCE instead of POINTER) from a file exiting at path

    template <class T>

        void initVector(std::vector<T> &vec, std::string path)
        {
            vec.clear();
            FILE * pFile = fopen (path.c_str(), "r");
            if (pFile == NULL) 
                perror ("Error opening file");
            else
            {
                std::cout << "\nTSET IS HERE\n";
                ignoreFirstLine(pFile);
                while(true)
                {
                    if(feof(pFile))
                    {
                        std::cout << "It is EOF\n";
                        break;
                    }
                    T t;
                    t.setupFromFile(pFile);
                    t.print();
                    vec.push_back(t);
                    //std::cout << "VEC SIZE is " << vec.size() << std::endl;
                }
                fclose (pFile);
            }
        }

    // Show all the element in the class T vector(using REFERENCE instead of POINTER)

    template <class T>

        void showVector(std::vector<T> &vec)
        {
            typename std::vector<T>::iterator it;
            for(it = vec.begin(); it!=vec.end(); it++)
            {
                //std::cout << "Print a element in the vector\n";
                (*it).print();
                std::cout << std::endl;
            }
        }

    template <class T>

        void showPointerVector(std::vector<T> &vec)
        {
            typename std::vector<T>::iterator it;
            for(it = vec.begin(); it!=vec.end(); it++)
            {
                //std::cout << "Print a element in the vector\n";
                (*it)->printBasicInfo();
            }
        }

    /****************************************** RESOURCES ************************************************/
    
    class Gate;

    // The base class for all the resource
    class Resource
    {
        public:
            int resourceType;
            std::vector<Gate*>gateAs;
            std::vector<Gate*>gateBs;
            std::vector<int> compatibleCategories;   
            std::set<Train> currentTrains;

            Resource() {}
            Resource(int n) { resourceType = n; }
            ~Resource() {}

            void setResourceType(int n)
            {
                resourceType = n;
            }

            /*
            void addNeighbour(char AorB, Resource* rp)
            {
                if(rp==NULL) std::cout << "rp is NULL\n";
                else
                {
                    std::cout << "here\n";
                    (*rp).print();
                    std::cout << "here\n";
                    if(AorB == 'A')
                        gateANeighbours.push_back(rp);
                    else
                        gateBNeighbours.push_back(rp);
                    std::cout << gateANeighbours.size() << " " <<gateBNeighbours.size() << std::endl;
                }
            }*/

            void addGate(char AorB, Gate* g)
            {
                if(AorB == 'A')
                    gateAs.push_back(g);
                if(AorB == 'B')
                    gateBs.push_back(g);
            }

            virtual void print(){}

            virtual void printBasicInfo(){}

            void printNeighbours()
            {
                /*
                std::cout << "Neighbours:\ngateA:\n";
                showPointerVector(gateANeighbours);
                std::cout << "gateB:\n";
                showPointerVector(gateBNeighbours);
                std::cout << std::endl;*/
            }
    };


    class TrackGroups: public Resource
    {
        public:
            int id;
            tm trTime;
            tm hwTime;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "TrackGroup%d;", &id);
                fscanf(pFile, "%d:%d:%d;", &trTime.tm_hour, &trTime.tm_min, &trTime.tm_sec);
                fscanf(pFile, "%d:%d:%d;\n", &hwTime.tm_hour, &hwTime.tm_min, &hwTime.tm_sec);
            }   
            void printBasicInfo()
            {   
                std::cout << "trackGroupsid " << id 
                    << " trTimeMin " << trTime.tm_min 
                    << " hwTimeMin " << hwTime.tm_min << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
            /*
               void printNeighbours()
               {
               std::cout << "Neighbours:\ngateA:\n";
               showPointerVector(gateANeighbours);
               std::cout << "gateB:\n";
               showPointerVector(gateBNeighbours);
               std::cout << std::endl;
               }*/
    };

    std::vector<TrackGroups> trackGroupsVec;

    class Platform: public Resource
    {
        public:
            int id;
            int length;

            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "Platform%d;%d;\n", &id, &length);
            }   

            void printBasicInfo()
            {
                std::cout << "platformid " << id << " length " << length << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
    };
    std::vector<Platform> platformsVec;

    class Facility: public Resource
    {
        public:
            int id;
            char type;
            int length;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "Facility%d;%c;%d;\n", &id, &type, &length);
            }   
            void printBasicInfo()
            {   
                std::cout << "facilityid " << id << 
                    " type " << type << " length " << length << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
    };

    std::vector<Facility> facilitiesVec;

    class SingleTrack: public Resource
    {
        public:
            int id;
            int length;
            int capa;

            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "SingleTrack%d;%d;%d;\n", &id, &length, &capa);
            }
            void printBasicInfo()
            {   
                std::cout << "SingleTrackid " << id 
                    << " length " << length
                    << " capa " << capa << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
    };

    std::vector<SingleTrack> singleTracksVec;

    class Yard: public Resource
    {
        public:
            int id;
            int capa;
            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "Yard%d;%d;\n", &id, &capa);
            }
            void printBasicInfo()
            {   
                std::cout << "yardid " << id << " capa " << capa << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
    };

    std::vector<Yard> yardsVec;

    void setupCompCatResFromFile(std::string path)
    {
        int resID, catID;
        char c;
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            ignoreFirstLine(pFile);
            while(true)
            {
                c = fgetc(pFile);
                switch(c)
                {
                    case 'F':
                        fscanf(pFile,"acility%d;Cat%d;\n", &resID, &catID);
                        facilitiesVec[resID-1].compatibleCategories.push_back(catID);
                        break;
                    case 'T':
                        fscanf(pFile, "rackGroup%d;Cat%d;\n", &resID, &catID);
                        trackGroupsVec[resID-1].compatibleCategories.push_back(catID);
                        break;
                    case 'P':
                        fscanf(pFile,"latform%d;Cat%d;\n", &resID, &catID);
                        platformsVec[resID-1].compatibleCategories.push_back(catID);
                        break;
                    case 'S':
                        fscanf(pFile,"ingleTrack%d;Cat%d;\n", &resID, &catID);
                        singleTracksVec[resID-1].compatibleCategories.push_back(catID);
                        break;
                    case 'Y':
                        fscanf(pFile,"ard%d;Cat%d;\n", &resID, &catID);
                        yardsVec[resID-1].compatibleCategories.push_back(catID);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    /*** SET UP THE NEIGHBOUR RELATIONSHIPS BETWEEN RESOURCES ***/

    char rGateSide, nGateSide; // the resource gate side; the neighbour gate side
    int rNum, nNum, rGatei, nGatei;
    Resource* neighbour;


    // According the neighbour info, assign its address to 'neighbour' Resource pointer
    void switchNC(char nc, FILE* pFile)
    {
        switch(nc)
        {
            case 'F':
                fscanf(pFile,"acility%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                neighbour = &facilitiesVec[nNum-1]; 
                break;
            case 'T':
                fscanf(pFile, "rackGroup%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                neighbour = &trackGroupsVec[nNum-1]; 
                break;
            case 'P':
                fscanf(pFile,"latform%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                neighbour = &platformsVec[nNum-1];
                break;
            case 'S':
                fscanf(pFile,"ingleTrack%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                neighbour = &singleTracksVec[nNum-1];
                break;
            case 'Y':
                fscanf(pFile,"ard%d;%c;%d;\n", &nNum, &nGateSide, &nGatei);
                neighbour = &yardsVec[nNum-1];
                break;
            default:
                std::cout << "It has no neighbour\n";
                fscanf(pFile,";;\n");
                neighbour = NULL; 
                std::cout << (neighbour==NULL) << std::endl;
                break;
        }
    }

    class Gate
    {
        public:
        Resource* rA, rB;
        Gate();
        ~Gate();

        setupFromFile(FILE * pFile)
        {
        char rc, nc; // resource character & neighbour character
        rc = fgetc(pFile); // read the resource name's first character

        switch(rc) 
        {
            case 'F':
                {
                    fscanf(pFile,"acility%d;%c;%d;", &rNum, &rGateSide, &rGatei); // read the resource info
                    nc = fgetc(pFile); // get the neighour name's first character
                    switchNC(nc, pFile); // assigned the neighbour object's address to 'neighbour'
                    Facility &theResourceP = facilitiesVec[rNum-1]; // use reference(alias): get the resource
                    theResourceP.addNeighbour(rGateSide, neighbour); 
                    // add 'neighbour' pointer to the resource's 'rGateSide'(A or B) neighbour vector 
                    break;
                }

            case 'P':
                {
                    fscanf(pFile, "latform%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Platform &theResourceP = platformsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'S':
                {
                    fscanf(pFile, "ingleTrack%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    SingleTrack &theResourceP = singleTracksVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'T':
                {
                    fscanf(pFile, "rackGroup%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    std::cout << "Is neighbour == NULL? " << (neighbour==NULL) << std::endl;
                    TrackGroups &theResourceP = trackGroupsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'Y':
                {
                    fscanf(pFile, "ard%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Yard &theResourceP = yardsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }
        }
        }
    };
    void readGates(FILE * pFile)
    {
        char rc, nc; // resource character & neighbour character
        rc = fgetc(pFile); // read the resource name's first character

        switch(rc) 
        {
            case 'F':
                {
                    fscanf(pFile,"acility%d;%c;%d;", &rNum, &rGateSide, &rGatei); // read the resource info
                    nc = fgetc(pFile); // get the neighour name's first character
                    switchNC(nc, pFile); // assigned the neighbour object's address to 'neighbour'
                    Facility &theResourceP = facilitiesVec[rNum-1]; // use reference(alias): get the resource
                    theResourceP.addNeighbour(rGateSide, neighbour); 
                    // add 'neighbour' pointer to the resource's 'rGateSide'(A or B) neighbour vector 
                    break;
                }

            case 'P':
                {
                    fscanf(pFile, "latform%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Platform &theResourceP = platformsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'S':
                {
                    fscanf(pFile, "ingleTrack%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    SingleTrack &theResourceP = singleTracksVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'T':
                {
                    fscanf(pFile, "rackGroup%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    std::cout << "Is neighbour == NULL? " << (neighbour==NULL) << std::endl;
                    TrackGroups &theResourceP = trackGroupsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }

            case 'Y':
                {
                    fscanf(pFile, "ard%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Yard &theResourceP = yardsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour);
                    break;
                }
        }
    }

    void setupNeighbourshipFromFile(std::string path)
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            std::cout << "Start to read gates.csv\n";
            ignoreFirstLine(pFile);
            while(true)
            {
                if(feof(pFile)) break;
                readGates(pFile);
            }
            std::cout << "gates.csv has been read in.\n";
            fclose(pFile);
        }
    }

}
#endif
