#include <iostream>

class Time
{
    public:
        int day, hour, min, sec;

        Time();
        Time(int d, int h, int m, int s);
        ~Time();

        bool isPointTime();

        bool isDurationTime();

        bool equals(Time t);

        bool isEarlierThan(Time t);

        Time add(Time& t);

        Time minus(Time& t);

        void print();

        void printToStream(std::ostream output);

        std::string toString();

        void showTime(Time temp);

        void showTimeInFile(Time temp, std::ostream& tempTimeFile);
};
