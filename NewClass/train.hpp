#include "base.hpp"
#include "time.hpp"

class Train
{
    private:
        Resource* currentResourcePointer;
        int trainID;
        TrainCategory* trainCategory;
        int remDBM;
        Time remTBM;
        //need good variable for departure (reuse.csv, changable)
        std::string schedule;
        int departureID;
        
    public:
        std::string getTrainName();

        void transmitInto(Resource& resource);
};

// comparasion function of two trains to judge their priority
int TrainCMP(Train& t1, Train& t2);
    // declare the train priority
