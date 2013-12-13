#include "train.hpp"

using namespace bonnie;

int main()
{
    FILE * pFile;

    pFile = fopen ("Data//singleTracks.csv" , "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nSingleTracks ARE HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            readSingleTracks(pFile);
        }
        showSingleTracks();
        fclose (pFile);
    }

    pFile = fopen ("Data//platforms.csv" , "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nplatformS ARE HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            readPlatforms(pFile);
        }
        showPlatforms();
        fclose (pFile);

    }

    pFile = fopen ("Data//facilities.csv" , "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nfacilitieS ARE HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            readFacilities(pFile);
        }
        showFacilities();
        fclose (pFile);

    }

    pFile = fopen ("Data//yards.csv" , "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nYARDS ARE HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            readYards(pFile);
            std::cout << std::endl;
        }
        showYards();
        fclose (pFile);
    }

    pFile = fopen ("Data//trackGroups.csv" , "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nTrackGroups ARE HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile)) break;
            readTrackGroups(pFile);
        }
        showTrackGroups();
        fclose (pFile);
    }

    pFile = fopen("Data//gates.csv", "r");
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
    /***********************************************
     * This is the mode of visiting some neighbour *
     ***********************************************
              typedGate temp;
              trackGroups tg = trackGroupsVec[7];
              std::cout << tg.id << std::endl;
              std::cout << tg.gateANeighbours.size() << std::endl;
              temp = tg.gateANeighbours[1];
              *(temp);

    //  std::cout << temp.first << " " << ((trackGroups*)(temp.second))->id << std::endl;
    std::cout << trackGroupsVec[7].id << std::endl; 
    std::cout << trackGroupsVec[7].gateANeighbours[1].first << std::endl;
    std::cout << ((trackGroups*)(trackGroupsVec[7].gateANeighbours[1].second))->id << std::endl;
    
    ***************************************************************
    * Try tranversing all the infrastructure and their neighbours *
    ***************************************************************
    
    *** using iterator ***

    std::cout << "\nShow all the neighbours of trackGroups\n" << std::endl;
    for(std::vector<trackGroups>::iterator it=trackGroupsVec.begin(); it!=trackGroupsVec.end(); it++)
    {
        std::cout << "\ntrackGroupsid " << (*it).id << "'s neighbours" << std::endl;
        std::vector<typedGate>::iterator gateit;
        std::cout << "Gate A:\n";
        for(gateit = (*it).gateANeighbours.begin(); gateit!= (*it).gateANeighbours.end(); gateit++)
        {
            *(*gateit);
        }
        std::cout << "Gate B:\n";
        for(gateit = (*it).gateBNeighbours.begin(); gateit!= (*it).gateBNeighbours.end(); gateit++)
        {
            *(*gateit);
        }
    }*/
    
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
