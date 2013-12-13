#include "base.hpp"

class Resource
{
    Gate* gate;
    int resourceType;
};

class TrackGroups: public Resource
{
    public:
        Time trTime;
        Time hwTime;
};
