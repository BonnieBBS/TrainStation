#include "train.hpp"

using namespace bonnie;

int main()
{
    initVector(allArrivalsVec, "Data//arrivals.csv");
   // initVector(allDeparturesVec, "Data//departures.csv");
   // setupJointPosition("Data//jointArrDep.csv");
   // setupPrefPlats("Data//prefPlat.csv");
   // setupCompCatDep("Data//compCatDep.csv");
   // initVector(trainCategoriesVec, "Data//trainCategories.csv");
   // initVector(reusesVec, "Data//reuses.csv");
   // initVector(arrDepSequencesVec, "Data//arrDepSequences.csv");

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
    // showVector(allDeparturesVec);

    showVector(allTrainsVec);

   // showVector(trackGroupsVec);
   // showVector(platformsVec);
   // showVector(singleTracksVec);
   // showVector(facilitiesVec);
   // showVector(yardsVec);
    
    // showVector(trainCategoriesVec);
    // showVector(reusesVec);
    // showVector(arrDepSequencesVec);

    return 0;
}
