#ifdef READCSV
#include "basic.hpp"
#include "time.hpp"
#include "resource.hpp"
#include "train.hpp"
#include <fstream>
#endif

void readInAllCSVs()
{
    initVector(allArrivalsVec, "Data//arrivals.csv");
    initVector(allDeparturesVec, "Data//departures.csv");
    setupJointPosition("Data//jointArrDep.csv");
    setupPrefPlats("Data//prefPlat.csv");
    setupCompCatDep("Data//compCatDep.csv");
    initVector(trainCategoriesVec, "Data//trainCategories.csv");
    initVector(reusesVec, "Data//reuses.csv");
    initVector(arrDepSequencesVec, "Data//arrDepSequences.csv");

    initAllTrainsVec("Data//initialTrains.csv");

    initVector(trackGroupsVec, "Data//trackGroups.csv");
    initVector(platformsVec, "Data//platforms.csv");
    initVector(singleTracksVec, "Data//singleTracks.csv");
    initVector(facilitiesVec, "Data//facilities.csv");
    initVector(yardsVec, "Data//yards.csv");
    setupNeighbourshipFromFile("Data//gates.csv");
    std::cout << "***********************************************\n";
    setupCompCatResFromFile("Data//compCatRes.csv");

    // These two methods have not been tested with output yet!!!!!!!!!!!
    setupImposedConsumptionsFromFile("Data//imposedConsumptions.csv");
    setupParametersFromFile("Data//parameters.csv");


    /********** have read in all the files except 'parameter.csv' and 'imposedConsumptions.csv' ***/

    // showVector(allArrivalsVec);
     showVector(allDeparturesVec);

    // showVector(allTrainsVec);

     showVector(trackGroupsVec);
    // showVector(platformsVec);
    // showVector(singleTracksVec);
    // showVector(facilitiesVec);
    // showVector(yardsVec);

    // showVector(trainCategoriesVec);
    // showVector(reusesVec);
    // showVector(arrDepSequencesVec);
}

template <class T>

void checkVector(std::vector<T> &vec)
{
    for(int i=0; i<vec.size(); i++)
        if (vec[i].id != i+1)
        {
            vec[i].print();
            break;
        }
}

void checkAllVectors()
{
    checkVector(allArrivalsVec);
    checkVector(allDeparturesVec);
    checkVector(allTrainsVec);
    checkVector(trackGroupsVec);
    checkVector(platformsVec);
    checkVector(singleTracksVec);
    checkVector(facilitiesVec);
    checkVector(yardsVec);
    checkVector(trainCategoriesVec);
//    checkVector(reusesVec);
//    checkVector(arrDepSequencesVec);
}

void connecTAR() // connect a train and a resource
{
    for(int i=0; i<allTrainsVec.size(); i++)
    {
        Train& t = allTrainsVec[i];
        if(t.currentResource = -1)
        {
            // go to arrival
        }
        else
        {
        }
    }
}
