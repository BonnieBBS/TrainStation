include "base.hpp"

class Event
{
    Train* train;
    Time* time;
    std::string eventType;
    Resource* resource;
    Gate* gate;
    std::string complement;

    std::string toString()
    {
        std::string s;
        s = "Train";
        s = s + (char)(train->trainID+'0') + ';' + time->toString() + ';' +  eventType +  ';' + resource->toString() + ';' + gate->toString() + ';' + complement + ';' ;
    }
};

