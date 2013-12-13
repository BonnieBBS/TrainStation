/*
 * Last Update: Nov 8
 * State: Can read in all csv files
 */

#ifdef TRAIN 
#include "basic.hpp"
#include "time.hpp"
#endif
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

    std::vector<Reuse> reusesVec;

    // parameters

    Time junTime, disjTime, revTime, minAsbTime, minResTime, maxDwellTime;
    int junCost, disjCost, platAsgCost, reuseCost, nbDays, maxMaint;
    double remDCost, remTCost, dwellCost;

    void readParameters(FILE* pFile) // waiting for test with more than one instance.
    {
        ignoreFirstLine(pFile);
        char c, cc;
        while(true)
        {
            if(feof(pFile)) break;
            c = fgetc(pFile);
            switch(c)
            {
                case 'j':
                    for(int i=0; i<3; i++)
                        c = fgetc(pFile);
                    switch(c)
                    {
                        case 'T':
                            fscanf(pFile, "ime;%d:%d:%d;\n", &junTime.hour, &junTime.min, &junTime.sec);
                            break;
                        case 'C':
                            fscanf(pFile, "ost;%d;\n", &junCost);
                            break;
                    }
                    break;
                case 'd':
                    for(int i=0; i<4; i++)
                        c = fgetc(pFile);
                    switch(c)
                    {
                        case 'T':
                            fscanf(pFile, "isjTime;%d:%d:%d;\n", &disjTime.hour, &disjTime.min, &disjTime.sec);
                            break;
                        case 'C':
                            fscanf(pFile, "ost;%d;\n", &disjCost);
                            break;
                        case 'l':
                            fscanf(pFile, "Cost;%lf;\n", &dwellCost); // look up scanf double
                            break;
                    }
                    break;
                case 'r':
                    for(int i=0; i<2; i++)
                        c = fgetc(pFile);
                    switch(c)
                    {
                        case 'v':
                            fscanf(pFile, "Time;%d:%d:%d;\n", &revTime.hour, &revTime.min, &revTime.sec);
                            break;
                        case 'm':
                            c = fgetc(pFile);
                            switch(c)
                            {
                                case 'D':
                                    fscanf(pFile, "Cost;%lf;\n", &remDCost); // look up scanf double
                                    break;
                                case 'T':
                                    fscanf(pFile, "Cost;%lf;\n", &remTCost); // look up scanf double
                                    break;
                            }
                            break;
                        case 'u':
                            fscanf(pFile, "seCost;%d;\n", &reuseCost);
                            break;
                    }
                    break;
                case 'p':
                    fscanf(pFile, "latAsgCost;%d;\n", &platAsgCost);
                    break;
                case 'n':
                    fscanf(pFile, "bDays;%d;\n", &nbDays);
                    break;
                case 'm':
                    for(int i=0; i<3; i++)
                        c = fgetc(pFile);
                    switch(c)
                    {
                        case 'A':
                            fscanf(pFile, "sbTime;%d:%d:%d;\n", &minAsbTime.hour, &minAsbTime.min, &minAsbTime.sec);
                            break;
                        case 'R':
                            fscanf(pFile, "esTime;%d:%d:%d;\n", &minResTime.hour, &minResTime.min, &minResTime.sec);
                            break;
                        case 'D':
                            fscanf(pFile, "wellTime;%d:%d:%d;\n", &maxDwellTime.hour, &maxDwellTime.min, &maxDwellTime.sec);
                            break;
                        case 'M':
                            fscanf(pFile, "aint;%d;\n", &maxMaint);
                            break;
                    }
                    break;
            }
        }
    }

    void setupParametersFromFile(std::string path)
    {
        FILE * pFile = fopen( path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
            readParameters(pFile);
        fclose(pFile);
    }
    void showParameters()
    {
    }

    // arrDepSequences: 
    // all arrivals and departures have a Arr/DepSeq 
    // which can lead them to the exact tracGroup to use and the rank in sequence

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
                std::cout << type << seqID << " trackGroup" << trackGroup 
                    << " rankInSequence " << rankInSequence << std::endl;
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
            Time maxTBM;
            Time maintTimeD;
            Time maintTimeT;

            void setupFromFile(FILE * pFile)
            {   
                fscanf(pFile, "Cat%d;", &id);
                fscanf(pFile, "%d;CatGroup%d;%d;", &length, &catGroup, &maxDBM);
                fscanf(pFile, "%d:%d:%d;", &maxTBM.hour, &maxTBM.min, &maxTBM.sec);
                fscanf(pFile, "%d:%d:%d;", &maintTimeD.hour, &maintTimeD.min, &maintTimeD.sec);
                fscanf(pFile, "%d:%d:%d;\n", &maintTimeT.hour, &maintTimeT.min, &maintTimeT.sec);
            }   

            void print()
            {   
                std::cout << "trainCategoriesid " << id 
                    << " maintTimeDMin " << maintTimeD.min 
                    << " maintTimeTimein " << maintTimeT.min << std::endl;
            }       
    };

    std::vector<trainCategory> trainCategoriesVec;

    /************************************* Train Dynamic Properties **************************************/

    class Arrival
    {
        public:
            Time time;
            Time idealDwell;
            Time maxDwell;
            int arrivalID;
            int trainID;
            int category; // 1-4
            int remDBM;
            Time remTBM;
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
                fscanf(pFile, "d%d %d:%d:%d;", &time.day, &time.hour, &time.min, &time.sec);
                fscanf(pFile, "ArrSeq%d;", &arrSeq);
                char c;
                c = fgetc(pFile);
                if(c==';') jointArr = -1;
                else if(c=='J') fscanf(pFile, "ointArr%d;", &jointArr);
                else std::cout << arrivalID << " ATTENTION!!!!!!!!!!!!! " << c << std::endl;
                c = fgetc(pFile);
                if(c==';') dep = -1;
                else if(c=='D') fscanf(pFile, "ep%d;", &dep); 
                else std::cout << "ATTENTION!!!!!!!!!!!!! " << c << std::endl;
                fscanf(pFile, "Cat%d;", &category);
                fscanf(pFile, "%d:%d:%d;", &idealDwell.hour, &idealDwell.min, &idealDwell.sec);
                fscanf(pFile, "%d:%d:%d;", &maxDwell.hour, &maxDwell.min, &maxDwell.sec);
                fscanf(pFile, "%d;", &remDBM);
                fscanf(pFile, "%d:%d:%d;\n", &remTBM.hour, &remTBM.min, &remTBM.sec);
            }

            void print()//incomplete
            {
                std::cout << arrivalID << " " << trainID << "\n";
                std::cout << time.day << " " << time.hour <<  " " << time.min << " " << time.sec << std::endl;
                std::cout << arrSeq << " " << jointArr << " " << dep << " " << category << "\n ";
                std::cout << idealDwell.hour << " " << idealDwell.min << " " << idealDwell.sec << std::endl;
                std::cout << maxDwell.hour << " " << maxDwell.min << " " << maxDwell.sec << std::endl;
                std::cout << remDBM << std::endl;
                std::cout << remTBM.hour << " " << remTBM.min << " " << remTBM.sec << std::endl;
                std::cout << "**********Prefered Platforms are:\n";
                showPrimitiveVector(prefPlats);
                if(jointArr==-1) std::cout << "There is no joint departure" << std::endl;
                else
                    std::cout << "**********joint position is:" << jointArrPosition << std::endl;
            }
    };

    class Departure // need revision
    {
        public:
            Time time;
            Time idealDwell;
            Time maxDwell;
            int departureID;
            int reqDBM;
            Time reqTBM;
            int depSeq;
            int jointDep;
            int jointDepPosition;
            std::vector<int> prefPlats;
            int compatibleCategory;
            int assignedTrainID;

        public:
            Departure() {}
            ~Departure() {}

            // read a line in the pFile to get an Arrival info and assign them to 'arrivial'
            void setupFromFile(FILE * pFile) 
            {
                //std::cout << "Departure set up from file\n";
                fscanf(pFile, "Dep%d;", &departureID);
                fscanf(pFile, "d%d %d:%d:%d;", &time.day, &time.hour, &time.min, &time.sec);
                fscanf(pFile, "DepSeq%d;", &depSeq);
                char c = fgetc(pFile);
                if(c == 'J') 
                    fscanf(pFile, "ointDep%d;", &jointDep);
                else
                    jointDep = -1;
                fscanf(pFile, "%d:%d:%d;", &idealDwell.hour, &idealDwell.min, &idealDwell.sec);
                fscanf(pFile, "%d:%d:%d;", &maxDwell.hour, &maxDwell.min, &maxDwell.sec);
                fscanf(pFile, "%d;", &reqDBM);
                fscanf(pFile, "%d:%d:%d;\n", &reqTBM.hour, &reqTBM.min, &reqTBM.sec);
                assignedTrainID = 0;
            }

            void print()//incomplete
            {
                std::cout << "departureID " << departureID << "\n";
                std::cout << time.day << " " << time.hour <<  " " << time.min << " " << time.sec << std::endl;
                std::cout << depSeq << " " << jointDep << " " <<  "\n ";
                std::cout << idealDwell.hour << " " << idealDwell.min << " " << idealDwell.sec << std::endl;
                std::cout << maxDwell.hour << " " << maxDwell.min << " " << maxDwell.sec << std::endl;
                std::cout << reqDBM << std::endl;
                std::cout << reqTBM.hour << " " << reqTBM.min << " " << reqTBM.sec << std::endl;
                std::cout << "**********Prefered Platforms are:\n";
                showPrimitiveVector(prefPlats);
                if(jointDep==-1) std::cout << "There is no joint departure" << std::endl;
                else
                    std::cout << "**********joint position is:" << jointDepPosition << std::endl;
                std::cout << "**********compatible category is:" << compatibleCategory;
                std::cout << std::endl;
            }
    };

    std::vector<Arrival> allArrivalsVec;

    std::vector<Departure> allDeparturesVec;

    // read files to setup all preferred platforms for all arrivals and departures

    void setupPrefPlats(std::string path) 
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

    // read files to setup all joint position sequence for all arrivals and departures

    void setupJointPosition(std::string path) 
    {
        FILE * pFile = fopen (path.c_str(), "r");
        if (pFile == NULL)
            perror ("Error opening file");
        else
        {
            ignoreFirstLine(pFile);
            char c;
            int jointNum, num, positionInSeq;
            while(true)
            {
                if(feof(pFile)) break;
                for(int i=0; i<6; i++)
                    c = fgetc(pFile);
                if(c=='A')
                {
                    fscanf(pFile, "rr%d;Arr%d;%d;\n", &jointNum, &num, &positionInSeq);
                    if(allArrivalsVec[num-1].jointArr != jointNum)
                    {
                        std::cout << "JointArr does not correspond to Arr\n";
                        std::cout << "allArrivalsVec[" << num-1 << "].jointArr is " 
                            << allArrivalsVec[num-1].jointArr 
                            << " but jointNum is " << jointNum << std::endl;
                    }
                    else
                        allArrivalsVec[num-1].jointArrPosition = positionInSeq;
                }
                if(c=='D')
                {
                    fscanf(pFile, "ep%d;Dep%d;%d;\n", &jointNum, &num, &positionInSeq);
                    if(allDeparturesVec[num-1].jointDep != jointNum)
                    {
                        std::cout << "JointDep does not correspond to Dep\n";
                    }
                    else
                        allDeparturesVec[num-1].jointDepPosition = positionInSeq;
                }

            }
            fclose(pFile);
            std::cout << "Joint Position in Sequence is set up.\n";
        }
    }

    // read files to setup all compatible train categories for all departures

    void setupCompCatDep(std::string path) 
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
            int currentResourceNumber;
            int remDBM;
            Time remTBM;
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
                    << "\nremTBM: " << remTBM.day << " " 
                    << remTBM.hour << ":" << remTBM.min << ":" 
                    << remTBM.sec << std::endl;
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
                currentResourceNumber = resourceNumber;
                fscanf(pFile, "%d;%d:%d:%d;\n", &remDBM, &remTBM.hour, &remTBM.min, &remTBM.sec);
            }
    };


    std::vector<Train> allTrainsVec;

    void initAllTrainsVec(std::string initialInTrainsFilePath)
    {
        // get all the initial in trains
        FILE * pFile = fopen(initialInTrainsFilePath.c_str(), "r");
        if(pFile == NULL)
            perror ("Error opening file");
        else
        {
            // get arriving trains
            for(int i=0; i<allArrivalsVec.size(); i++)
            {
                Train t;
                t.setupFromAnArrival(allArrivalsVec[i]);
                allTrainsVec.push_back(t);
            }

            ignoreFirstLine(pFile);
            while(true)
            {
                if(feof(pFile)) break;
                Train t;
                t.setupTheInitialInTrainFromFile(pFile);
                allTrainsVec.push_back(t);
            }
            fclose(pFile);

        }

    }

    std::vector<trainCategory> allTrainCategoriesVec; // trainCategories.id = vector[id-1]

    std::vector<reusePair> reusePairsVec;

 
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
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterSystem;"
                    << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterResource;"
                    << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;ExitResource;"
                    << "Facility" << temp.currentResourceNumber << ";;;" << std::endl;
                break;
            case 'P'-'A':
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterSystem;"
                    << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterResource;"
                    << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;ExitResource;"
                    << "Platform" << temp.currentResourceNumber << ";;;" << std::endl;
                break;
            case 'S'-'A':
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterSystem;"
                    << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterResource;"
                    << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;ExitResource;"
                    << "SingleTrack" << temp.currentResourceNumber << ";;;" << std::endl;
                break;
            case 'T'-'A':
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterSystem;"
                    << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterResource;"
                    << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;ExitResource;"
                    << "TrackGroup" << temp.currentResourceNumber << ";;;" << std::endl;
                break;
            case 'Y'-'A':
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterSystem;"
                    << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;EnterResource;"
                    << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
                csvFile << "Train" << temp.trainID << ";d1 00:00:00;ExitResource;"
                    << "Yard" << temp.currentResourceNumber << ";;;" << std::endl;
                break;
        }
    }

