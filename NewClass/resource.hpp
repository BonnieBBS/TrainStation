#include "base.hpp"

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
            void print();
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
    int trainsCapacity; // record how many trains can enter the resource
    std::vector<ImposedConsumption> imposedConsumptions;
    std::vector<NeighbourResource> gateANeighbours;
    std::vector<NeighbourResource> gateBNeighbours;
    std::vector<int> compatibleCategories;   
    std::set<Train*> currentTrainsPointer;

    Resource();
    Resource(int n);
    ~Resource();

    void setResourceType(int n);

    virtual void addImposedConsumption(FILE* pFile);

    void addNeighbour(char AorB, Resource* rp, char neighbourGateType, int neighbourGateID);

    virtual std::string getResourceName();

    virtual void print();

    virtual void printBasicInfo();

    void printNeighbours();

    void acceptTrainEntrance(Train& train);

};
class TrackGroups: public Resource
{
    public:
        Time trTime;
        Time hwTime;

        void setupFromFile(FILE * pFile);
        std::string getResourceName();
        void printBasicInfo();
        void print();
        void addImposedConsumption(FILE* pFile);
};

std::vector<TrackGroups> trackGroupsVec;

class Platform: public Resource
{
    public:
        int length;

        void setupFromFile(FILE * pFile);

        std::string getResourceName();

        void printBasicInfo();

        void print();

        void addImposedConsumption(FILE* pFile);
};
std::vector<Platform> platformsVec;

class Facility: public Resource
{
    public:
        char type;
        int length;

        void setupFromFile(FILE * pFile);

        std::string getResourceName();

        void printBasicInfo();

        void print();

        void addImposedConsumption(FILE* pFile);

        std::vector<Facility> facilitiesVec;
};

class SingleTrack: public Resource
{
    public:
        int length;
        int capa;

        void setupFromFile(FILE * pFile);

        std::string getResourceName();

        void printBasicInfo();

        void print();

        void addImposedConsumption(FILE* pFile);
};

std::vector<SingleTrack> singleTracksVec;

class Yard: public Resource
{
    public:
        int capa;
        void setupFromFile(FILE * pFile);

        std::string getResourceName();

        void printBasicInfo();

        void print();

        void addImposedConsumption(FILE* pFile);

        std::vector<Yard> yardsVec;

        void setupCompCatResFromFile(std::string path);

        // add imposedComsumptions
        void readImposedConsumption(FILE* pFile) ;

        void setupImposedConsumptionsFromFile(std::string path);

        /*** SET UP THE NEIGHBOUR RELATIONSHIPS BETWEEN RESOURCES ***/

        char rGateSide, nGateSide; // the resource gate side; the neighbour gate side
        int rNum, nNum, rGatei, nGatei;
        Resource* neighbour;


        // According the neighbour info, assign its address to 'neighbour' Resource pointer
        void switchNC(char nc, FILE* pFile);

        void readGates(FILE * pFile);

        void setupNeighbourshipFromFile(std::string path);
};
