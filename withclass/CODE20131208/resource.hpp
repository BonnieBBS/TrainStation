#ifdef RESOURCE
#include "time.hpp"
#include "basic.hpp"
#endif
   /****************************************** RESOURCES ************************************************/

    // The base class for all the resource
    class Resource
    {
        class NeighbourResource
        {
            public:
                Resource* rp;
                char gateType;
                int gateID;
                void print()
                {
                    rp->printBasicInfo();
                    std::cout << gateType << " " << gateID << std::endl;
                }
        };

        protected:
        class ImposedConsumption // anything concerning this class needs testing. btw, union?
        {
            public:
                // 0 no consumption; 'F'-'A' Facility; 'Y'-'A' Yard; 'T'-'A' TrackGroup
                Time begTime, endTime;
                int nb;
                char originGateC, destinationGateC;
                int originGateN, destinationGateN;
                Time entranceTime;
        };

        public:
        int resourceType;
            int id;
        std::vector<ImposedConsumption> imposedConsumptions;
        std::vector<NeighbourResource> gateANeighbours;
        std::vector<NeighbourResource> gateBNeighbours;
        std::vector<int> compatibleCategories;   
        std::set<int> currentTrainsID;

        Resource() {}
        Resource(int n) { resourceType = n; }
        ~Resource() {}

        void setResourceType(int n)
        {
            resourceType = n;
        }

        virtual void addImposedConsumption(FILE* pFile){}

        void addNeighbour(char AorB, Resource* rp, char neighbourGateType, int neighbourGateID)
        {
            if(rp==NULL) std::cout << "rp is NULL\n";
            else
            {
                std::cout << "here\n";
                (*rp).print();
                NeighbourResource temp;
                temp.rp = rp;
                temp.gateType = neighbourGateType;
                temp.gateID = neighbourGateID;
                std::cout << "here\n";
                if(AorB == 'A')
                    gateANeighbours.push_back(temp);
                else
                    gateBNeighbours.push_back(temp);
                std::cout << gateANeighbours.size() << " " <<gateBNeighbours.size() << std::endl;
            }
        }

        virtual std::string getResourceName(){}

        virtual void print(){}

        virtual void printBasicInfo(){}

        void printNeighbours()
        {
            //put here for test (temporarily)
            std::cout << "compatible categories:\n";
            showPrimitiveVector(compatibleCategories);

            std::cout << "Neighbours:\ngateA:\n";
            showVector(gateANeighbours);
            std::cout << "gateB:\n";
            showVector(gateBNeighbours);
            std::cout << std::endl;
        }
    };

    class TrackGroups: public Resource
    {
        public:
            Time trTime;
            Time hwTime;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "TrackGroup%d;", &id);
                fscanf(pFile, "%d:%d:%d;", &trTime.hour, &trTime.min, &trTime.sec);
                fscanf(pFile, "%d:%d:%d;\n", &hwTime.hour, &hwTime.min, &hwTime.sec);
            }   
            std::string getResourceName()
            {
                return "TrackGroup"+id;
            }
            void printBasicInfo()
            {   
                std::cout << "trackGroupsid " << id 
                    << " trTimeMin " << trTime.min 
                    << " hwTimeMin " << hwTime.min << std::endl;
            }
            void print()
            {
                printBasicInfo();
                printNeighbours();
            }
            void addImposedConsumption(FILE* pFile)
            {
                //fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;%c%d;%c;%d;d%d %d:%d:%d;\n", &)
                ImposedConsumption temp;
                fscanf(pFile, ";;;%c%d;%c;%d;d%d %d:%d:%d;\n", 
                        &temp.originGateC, &temp.originGateN, &temp.destinationGateC, &temp.destinationGateN,
                        &temp.entranceTime.day, &temp.entranceTime.hour, &temp.entranceTime.min,
                        &temp.entranceTime.sec);
                imposedConsumptions.push_back(temp);
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
            int length;

            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "Platform%d;%d;\n", &id, &length);
            }   

            std::string getResourceName()
            {
                return "Platform"+id;
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
            void addImposedConsumption(FILE* pFile)
            {
                //fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;%c%d;%c;%d;d%d %d:%d:%d;\n", &)
                ImposedConsumption temp;
                fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;;;;;;\n", 
                        &temp.begTime.day, &temp.begTime.hour, &temp.begTime.min,
                        &temp.begTime.sec, 
                        &temp.endTime.day, &temp.endTime.hour, &temp.endTime.min,
                        &temp.endTime.sec);
                imposedConsumptions.push_back(temp);
            }
    };
    std::vector<Platform> platformsVec;

    class Facility: public Resource
    {
        public:
            char type;
            int length;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "Facility%d;%c;%d;\n", &id, &type, &length);
            }   
            std::string getResourceName()
            {
                return "Facility"+id;
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
            void addImposedConsumption(FILE* pFile)
            {
                //fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;%c%d;%c;%d;d%d %d:%d:%d;\n", &)
                ImposedConsumption temp;
                fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;;;;;;\n", 
                        &temp.begTime.day, &temp.begTime.hour, &temp.begTime.min,
                        &temp.begTime.sec, 
                        &temp.endTime.day, &temp.endTime.hour, &temp.endTime.min,
                        &temp.endTime.sec);
                imposedConsumptions.push_back(temp);
            }
    };

    std::vector<Facility> facilitiesVec;

    class SingleTrack: public Resource
    {
        public:
            int length;
            int capa;

            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "SingleTrack%d;%d;%d;\n", &id, &length, &capa);
            }
            std::string getResourceName()
            {
                return "SingleTrack"+id;
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
            void addImposedConsumption(FILE* pFile)
            {
                //fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;%c%d;%c;%d;d%d %d:%d:%d;\n", &)
                ImposedConsumption temp;
                fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;;;;;;\n", 
                        &temp.begTime.day, &temp.begTime.hour, &temp.begTime.min,
                        &temp.begTime.sec, 
                        &temp.endTime.day, &temp.endTime.hour, &temp.endTime.min,
                        &temp.endTime.sec);
                imposedConsumptions.push_back(temp);
            }
    };

    std::vector<SingleTrack> singleTracksVec;

    class Yard: public Resource
    {
        public:
            int capa;
            void setupFromFile(FILE * pFile)
            {
                fscanf(pFile, "Yard%d;%d;\n", &id, &capa);
            }
            std::string getResourceName()
            {
                return "Yard"+id;
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
            void addImposedConsumption(FILE* pFile)
            {
                //fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;%c%d;%c;%d;d%d %d:%d:%d;\n", &)
                ImposedConsumption temp;
                fscanf(pFile, "d%d %d:%d:%d;d%d %d:%d:%d;%d;;;;;\n", 
                        &temp.begTime.day, &temp.begTime.hour, &temp.begTime.min,
                        &temp.begTime.sec, 
                        &temp.endTime.day, &temp.endTime.hour, &temp.endTime.min,
                        &temp.endTime.sec,
                        &temp.nb);
                imposedConsumptions.push_back(temp);
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
                if(feof(pFile)) break;
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

    // add imposedComsumptions
    void readImposedConsumption(FILE* pFile) 
    {
        int resID;
        char c;
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            c = fgetc(pFile);
            switch(c)
            {
                case 'F':
                    fscanf(pFile,"acility%d;", &resID);
                    facilitiesVec[resID-1].addImposedConsumption(pFile);
                    break;
                case 'T':
                    fscanf(pFile, "rackGroup%d;", &resID);
                    facilitiesVec[resID-1].addImposedConsumption(pFile);
                    break;
                case 'P':
                    fscanf(pFile,"latform%d;", &resID);
                    facilitiesVec[resID-1].addImposedConsumption(pFile);
                    break;
                case 'S':
                    fscanf(pFile,"ingleTrack%d;", &resID);
                    facilitiesVec[resID-1].addImposedConsumption(pFile);
                    break;
                case 'Y':
                    fscanf(pFile,"ard%d;", &resID);
                    facilitiesVec[resID-1].addImposedConsumption(pFile);
                    break;
                default:
                    break;
            }
        }
    }

    void setupImposedConsumptionsFromFile(std::string path)
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
            readImposedConsumption(pFile);
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
                    theResourceP.addNeighbour(rGateSide, neighbour, nGateSide, nGatei); 
                    // add 'neighbour' pointer to the resource's 'rGateSide'(A or B) neighbour vector 
                    break;
                }

            case 'P':
                {
                    fscanf(pFile, "latform%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Platform &theResourceP = platformsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour, nGateSide, nGatei);
                    break;
                }

            case 'S':
                {
                    fscanf(pFile, "ingleTrack%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    SingleTrack &theResourceP = singleTracksVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour, nGateSide, nGatei);
                    break;
                }

            case 'T':
                {
                    fscanf(pFile, "rackGroup%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    std::cout << "Is neighbour == NULL? " << (neighbour==NULL) << std::endl;
                    TrackGroups &theResourceP = trackGroupsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour, nGateSide, nGatei);
                    break;
                }

            case 'Y':
                {
                    fscanf(pFile, "ard%d;%c;%d;", &rNum, &rGateSide, &rGatei);
                    nc = fgetc(pFile);
                    switchNC(nc, pFile);
                    Yard &theResourceP = yardsVec[rNum-1];
                    theResourceP.addNeighbour(rGateSide, neighbour, nGateSide, nGatei);
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
