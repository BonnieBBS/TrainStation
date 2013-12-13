#ifdef RESOURCE
#include "train.hpp"
#include "readcsv.hpp"
#else
#include "basic.hpp"
#include "time.hpp"
#include "train.hpp"
#include "resource.hpp"
#include "readcsv.hpp"
#endif

/************************************ Create auto_solution.csv ***********************************/


    void printArrival2Platform(Arrival& temp, int i, std::ostream& csvFile)
    {
        switch(temp.arrSeq)
        {
            case 1:
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterSystem;TrackGroup7;;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup7;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup7;A3;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup6;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup6;A1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup3;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup3;A1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup1;B9;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup1;A7;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;Platform7;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";Arrival;Platform7;;Arrival" << i+1 << ";" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;Platform7;B1;;" << std::endl;
                break;
            case 2:
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterSystem;TrackGroup10;;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup10;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup10;A3;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup8;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup8;A1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;TrackGroup3;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup3;A1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;TrackGroup1;A7;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";EnterResource;Platform7;B1;;" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";Arrival;Platform7;;Arrival" << i+1 << ";" << std::endl;
                csvFile << "Train" << i+1 << ";d"
                    << temp.time.day << " " << temp.time.hour << ":"
                    << temp.time.min << ":" << temp.time.sec
                    <<";ExitResource;Platform7;B1;;" << std::endl;
                break;
        }
    }

    void printInitialInTrain2Platform(Train& temp, std::ostream& csvFile)
    {
        switch(temp.currentResource)
        {
            case 'F'-'A':
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
                break;
            case 'P'-'A':
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
                break;
            case 'S'-'A':
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
                break;
            case 'T'-'A':
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
                break;
            case 'Y'-'A':
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
                break;
        }
    }

int main()
{
    readInAllCSVs();
    checkAllVectors();
    std::cout << "All vectors with ID numbers are checked." << std::endl;
    std::ofstream csvFile ("auto_solution.csv");
    if(csvFile.is_open())
    {
        csvFile << "Train;Time;Event type;Resource;Gate;Complement;\n";
        for(int i=0; i<allArrivalsVec.size(); i++)
        {
            Arrival &tempArr = allArrivalsVec[i];

            printArrival2Platform(tempArr, i, csvFile);

            //Train& tempTrain = allTrainsVec[i];
/*
            for(int j=0; j<allDeparturesVec.size(); j++)
            {
               Departure& tempDep = allDeparturesVec[j];
               if(tempDep.assignedTrainID) continue;
               if(tempArr.category != tempDep.compatibleCategory) continue;
               showTime(calculateDurationBetween(tempDep.time, tempArr.time));
            }  
*/

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
