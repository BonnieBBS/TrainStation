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


void printEntry(Train train, Resource r, Time time, string eventName, char gateType, int gateNumber, string compatibility, std::ostream& output)
{
    output << "Train" << train.id << ";";
    time.printToStream(output);
    output << ";" << eventName << ";" << r.getResourceName << ";"
        << gateType << gateNumber << ";" << compatibility << ";" << std::endl;
}

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
                <<";EnterResource;TrackGroup1;A7;;" << std::endl;
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
void printPlatform2Departure(Train& train, Departure temp, std::ostream& csvFile)
{
    switch(temp.depSeq)
    {
        case 1:
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;Platform7;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";Departure;Platform7;;Dep" << temp.id << ";" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;Platform7;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup1;A7;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup1;B9;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup3;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup3;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup6;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup6;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup7;A3;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup7;B7;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitSystem;TrackGroup7;;;" << std::endl;
            break;
        case 2:
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;Platform7;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";Departure;Platform7;;Dep" << temp.id << ";" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;Platform7;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup1;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup1;B9;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup3;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup3;B5;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup8;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup8;B3;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";EnterResource;TrackGroup10;A1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitResource;TrackGroup10;B1;;" << std::endl;
            csvFile << "Train" << train.id << ";d"
                << temp.time.day << " " << temp.time.hour << ":"
                << temp.time.min << ":" << temp.time.sec
                <<";ExitSystem;TrackGroup10;;;" << std::endl;
            break;
        default:
            std::cout << "HERE!!!!!!!!!!" << temp.depSeq <<  std::endl;
            break;
    }
}
//
//    void printInitialInTrain2Platform(Train& temp, std::ostream& csvFile)
//    {
//        switch(temp.currentResource)
//        {
//            case 'F'-'A':
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
//                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
//                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
//                    << "Facility" << temp.currentResourceP->id << ";;;" << std::endl;
//                break;
//            case 'P'-'A':
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
//                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
//                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
//                    << "Platform" << temp.currentResourceP->id << ";;;" << std::endl;
//                break;
//            case 'S'-'A':
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
//                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
//                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
//                    << "SingleTrack" << temp.currentResourceP->id << ";;;" << std::endl;
//                break;
//            case 'T'-'A':
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
//                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
//                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
//                    << "TrackGroup" << temp.currentResourceP->id << ";;;" << std::endl;
//                break;
//            case 'Y'-'A':
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
//                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
//                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
//                csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
//                    << "Yard" << temp.currentResourceP->id << ";;;" << std::endl;
//                break;
//        }
//    }
void printInitialInTrain2Platform(Train& temp, std::ostream& csvFile)
{
    switch(temp.currentResource)
    {
        case 'F'-'A':
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
            break;
        case 'P'-'A':
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
            break;
        case 'S'-'A':
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
            break;
        case 'T'-'A':
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
            break;
        case 'Y'-'A':
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterSystem;"
                << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;EnterResource;"
                << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
            csvFile << "Train" << temp.id << ";d1 00:00:00;ExitResource;"
                << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
            break;
    }
}

int main()
{
    readInAllCSVs();
    checkAllVectors();
    std::cout << "All vectors with ID numbers are checked." << std::endl;
    //showVector(allTrainsVec);
    std::ofstream csvFile ("auto_solution.csv");
    //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    //Departure d1 = allDeparturesVec[0];
    //d1.print();
    //Departure de = allDeparturesVec[allDeparturesVec.size()-1];
    //de.print();
    //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    if(csvFile.is_open())
    {
        csvFile << "Train;Time;Event type;Resource;Gate;Complement;\n";
        
        /* The GENERAL IDEA !!!!!!!!!!!!!
        while(wholeTime.ticksAway())
        {
        for(int i=0; i<allTrainsVec.size(); i++)
        {
            Train& train = allTrainsVec[i];
            for each train.currentResource.neightResource
                if( train.check(Resource resource) )
                    train.transmitTo(resource);
        }
        allTrainsVec.sort();
        }*/

        for(int i=0; i<allArrivalsVec.size(); i++)
        {
            Arrival &tempArr = allArrivalsVec[i];

            Train &tempTrain = allTrainsVec[i];

            printArrival2Platform(tempArr, i, csvFile);

            //Train& tempTrain = allTrainsVec[i];

            for(int j=0; j<allDeparturesVec.size(); j++)
            {
                Departure& tempDep = allDeparturesVec[j];
                if(tempDep.assignedTrainID) continue;
                if(tempArr.category != tempDep.compatibleCategory) continue;
                if(!tempArr.time.isEarlierThan(tempDep.time)) continue;////
                if(tempArr.remDBM<tempDep.reqDBM && tempDep.reqTBM.isEarlierThan(tempArr.remTBM) ) continue;
                tempDep.assignedTrainID = tempArr.id;
                tempTrain.departureID = tempDep.id;
                break;
            }  
            if(tempTrain.departureID != -1)
            {
                Departure& theAssignedDep = allDeparturesVec[tempTrain.departureID];
                printPlatform2Departure(tempTrain, theAssignedDep, csvFile);
            }
            else
            {
                for(int j=0; j<allDeparturesVec.size(); j++)
                {
                    Departure& tempDep = allDeparturesVec[j];
                    if(tempDep.assignedTrainID) continue;
                    tempDep.assignedTrainID = tempArr.id;
                    tempTrain.departureID = tempDep.id;
                    break;
                }
                Departure& theAssignedDep = allDeparturesVec[tempTrain.departureID-1];
                //if(tempTrain.id==1234) 
                //{
                //    std::cout << tempTrain.id << std::endl;
                //    std::cout << tempTrain.departureID << std::endl;
                //    theAssignedDep.print();
                //    printPlatform2Departure(tempTrain, theAssignedDep, std::cout);
                //}
                //if(tempTrain.id==1235) 
                //{
                //    std::cout << tempTrain.id << std::endl;
                //    std::cout << tempTrain.departureID << std::endl;
                //    theAssignedDep.print();
                //    printPlatform2Departure(tempTrain, theAssignedDep, std::cout);
                //}
                printPlatform2Departure(tempTrain, theAssignedDep, csvFile);
                /*
                   std::cout << i << std::endl;
                   csvFile << "Train" << i+1 << ";d7 23:59:59;EnterResource;TrackGroup7;;;" << std::endl;
                   csvFile << "Train" << i+1 << ";d7 23:59:59;Departure;TrackGroup7;;Dep1906;" << std::endl;
                   csvFile << "Train" << i+1 << ";d7 23:59:59;ExitResource;TrackGroup7;;;" << std::endl;
                   csvFile << "Train" << i+1 << ";d7 23:59:59;ExitSystem;TrackGroup7;;;" << std::endl;
                   */
            }
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
