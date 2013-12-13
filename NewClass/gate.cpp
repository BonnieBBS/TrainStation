#include "base.hpp"

class Gate()
{
    private:
        char gateType;
        int gateNumber;
        Resource* gateResource[2];
    
    public:
        Gate();
        ~Gate();

    std::string getGateName()
    {
        std::string s = gateType + (char)(gateNumber + '0');
        return s;
    }

    Resource* getNeighbourResourcePointer()
    {
        
    }
}
