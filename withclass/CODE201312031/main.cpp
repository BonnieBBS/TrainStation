#include "basic.hpp"
#include "time.hpp"
#include "train.hpp"
#include "resource.hpp"
#include "readcsv.hpp"
int main()
{
    readInAllCSVs();
    std::ofstream csvFile ("auto_solution.csv");
    if(csvFile.is_open())
    {
        csvFile << "Train;Time;Event type;Resource;Gate;Complement;\n";
        for(int i=0; i<allArrivalsVec.size(); i++)
        {
            Arrival &tempArr = allArrivalsVec[i];

            printArrival2Platform(tempArr, i, csvFile);

            //Train& tempTrain = allTrainsVec[i];

            for(int j=0; j<allDeparturesVec.size(); j++)
            {
               Departure& tempDep = allDeparturesVec[j];
               if(tempDep.assignedTrainID) continue;
               if(tempArr.category != tempDep.compatibleCategory) continue;
               showTime(calculateDurationBetween(tempDep.time, tempArr.time));
            }  


            csvFile << "Train" << i+1 << ";d7 23:59:59;EnterResource;TrackGroup7;;;" << std::endl;
            csvFile << "Train" << i+1 << ";d7 23:59:59;ExitResource;TrackGroup7;;;" << std::endl;
            csvFile << "Train" << i+1 << ";d7 23:59:59;ExitSystem;TrackGroup7;;;" << std::endl;
        }
        for(int i=allArrivalsVec.size(); i<allTrainsVec.size(); i++)
        {
            Train &temp = allTrainsVec[i];
            
            printInitialInTrain2Platform(temp, csvFile);

            csvFile << "Train" << i+1 << ";d7 23:59:59;EnterResource;TrackGroup7;;;" << std::endl;
            csvFile << "Train" << i+1 << ";d7 23:59:59;ExitResource;TrackGroup7;;;" << std::endl;
            csvFile << "Train" << i+1 << ";d7 23:59:59;ExitSystem;TrackGroup7;;;" << std::endl;
        }
    }

    return 0;
}
