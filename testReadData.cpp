#include "train.hpp"

using namespace bonnie;

int main()
{
    initVector(allArrivalsVec, "Data//arrivals.csv");
    showVector(allArrivalsVec);
    initVector(trackGroupsVec, "Data//trackGroups.csv");
    showVector(trackGroupsVec);
    initVector(platformsVec, "Data//platforms.csv");
    showVector(platformsVec);
    initVector(singleTracksVec, "Data//singleTracks.csv");
    showVector(singleTracksVec);
    initVector(facilitiesVec, "Data//facilities.csv");
    showVector(facilitiesVec);
    initVector(yardsVec, "Data//yards.csv");
    showVector(yardsVec);
    setupNeighbourshipFromFile("Data//gates.csv");

    std::cout << "\nShow all the neighbours of trackGroups\n" << std::endl;
    for(int i=0; i<trackGroupsVec.size(); i++)
    {
        std::cout << "\ntrackGroupsid " << trackGroupsVec[i].id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(int j=0; j<(trackGroupsVec[i].gateANeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(trackGroupsVec[i].gateANeighbours[j])).print();
        }
        std::cout << "Gate B:\n";
        for(int j=0; j<(trackGroupsVec[i].gateBNeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(trackGroupsVec[i].gateBNeighbours[j])).print();
        }
    }

    std::cout << "\nShow all the neighbours of yards\n" << std::endl;
    for(int i=0; i<yardsVec.size(); i++)
    {
        std::cout << "\nyardsid " << yardsVec[i].id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(int j=0; j<(yardsVec[i].gateANeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(yardsVec[i].gateANeighbours[j])).print();
        }
        std::cout << "Gate B:\n";
        for(int j=0; j<(yardsVec[i].gateBNeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(yardsVec[i].gateBNeighbours[j])).print();
        }
    }
    std::cout << "\nShow all the neighbours of singleTracks\n" << std::endl;
    for(int i=0; i<singleTracksVec.size(); i++)
    {
        std::cout << "\nsingleTracksid " << singleTracksVec[i].id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(int j=0; j<(singleTracksVec[i].gateANeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(singleTracksVec[i].gateANeighbours[j])).print();
        }
        std::cout << "Gate B:\n";
        for(int j=0; j<(singleTracksVec[i].gateBNeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(singleTracksVec[i].gateBNeighbours[j])).print();
        }
    }
    std::cout << "\nShow all the neighbours of facilities\n" << std::endl;
    for(int i=0; i<facilitiesVec.size(); i++)
    {
        std::cout << "\nfacilitiesid " << facilitiesVec[i].id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(int j=0; j<(facilitiesVec[i].gateANeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(facilitiesVec[i].gateANeighbours[j])).print();
        }
        std::cout << "Gate B:\n";
        for(int j=0; j<(facilitiesVec[i].gateBNeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(facilitiesVec[i].gateBNeighbours[j])).print();
        }
    }
    std::cout << "\nShow all the neighbours of platforms\n" << std::endl;
    for(int i=0; i<platformsVec.size(); i++)
    {
        std::cout << "\nplatformsid " << platformsVec[i].id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(int j=0; j<(platformsVec[i].gateANeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(platformsVec[i].gateANeighbours[j])).print();
        }
        std::cout << "Gate B:\n";
        for(int j=0; j<(platformsVec[i].gateBNeighbours.size()); j++)
        {
            std::cout << "NO." << j+1 << " " ;
            (*(platformsVec[i].gateBNeighbours[j])).print();
        }
    }

    return 0;
}
