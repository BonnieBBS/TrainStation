class Time
{
    public:
        int day, hour, min, sec;

        Time() { day = hour = min = sec = 0;}
        Time(int d, int h, int m, int s) { day = d; hour = h; min = m; sec = s; }
        ~Time() {}

        bool isPointTime()
        {
            if(day>7 || day<1) return false;
            if(hour>23 || hour<0) return false;
            if(min>59 || min<0) return false;
            if(sec>59 || sec<0) return false;
            return true;
        }

        bool isDurationTime()
        {
            if(day>7 || day<0) return false;
            if(hour>23 || hour<0) return false;
            if(min>59 || min<0) return false;
            if(sec>59 || sec<0) return false;
            return true;
        }

        bool equals(Time t)
        {
            if(day==t.day && hour==t.hour && min==t.min && sec==t.sec) return true;
            else return false;
        }

        bool isEarlierThan(Time t)
        {
            if(day > t.day) return true;
            if(day < t.day) return false;
            if(day ==t.day)
            {
                if(hour > t.hour) return true;
                if(hour < t.hour) return false;
                if(hour ==t.hour)
                {
                    if(min > t.min) return true;
                    if(min < t.min) return false;
                    if(min ==t.min)
                    {
                        if(sec > t.sec) return true;
                        if(sec > t.sec) return false;
                        if(min ==t.sec) return false;
                    }
                }
            }

        }

        Time add(Time& t)
        {
            Time rtn;
            int temp;
            temp = sec + t.sec;
            if(temp>59)
            {
                rtn.min ++;
                rtn.sec = temp-60;
            }
            else rtn.sec = temp;
            temp = min + t.min;
            if(temp>59)
            {
                rtn.hour ++;
                rtn.min = temp - 60;
            }
            else rtn.min += temp;
            temp = hour + t.hour;
            if(temp>23)
            {
                rtn.day ++;
                rtn.hour = temp - 24;
            }
            else rtn.hour += temp;
            rtn.day += day + t.day;
            return rtn;
        }

        Time minus(Time& t)
        {
            Time rtn;
            int temp;
            if(isEarlierThan(t)) 
            {
                std::cout << "The first is smaller than the latter." << std::endl;
                goto e;
            }
            else 
            {
                rtn.day = day-t.day;
                if(hour < t.hour)
                {
                    if(rtn.day == 0)
                    {
                        std::cout << "The first is smaller than the latter." << std::endl;
                        goto e;
                    }
                    else
                    {
                        rtn.hour = hour + 24 - t.hour;
                        rtn.day --;
                    }
                }
                else 
                {
                    rtn.hour = hour - t.hour;
                    if(min < t.min)
                    {
                        if(rtn.hour == 0)
                        {
                            std::cout << "The first is smaller than the latter." << std::endl;
                            goto e;
                        }
                        else
                        {
                            rtn.min = min + 60 - t.min;
                            rtn.min --;
                        }
                    }
                    else
                    {
                        rtn.min = min - t.min;
                        if(sec < t.sec)
                        {
                            if(rtn.hour == 0)
                            {
                                std::cout << "The first is smaller than the latter." << std::endl;
                                goto e;
                            }
                            else
                            {
                                rtn.sec = sec + 60 - t.sec;
                                rtn.sec --;
                            }
                        }
                        else rtn.sec = sec - t.sec;
                    }
                }
            }
e: ;
        }

        void print()
        {
            if(isDurationTime())
            std::cout << "d" << day << " " << hour << ":" << min << ":" << sec << std::endl;
            else std::cout << "It is not a duration time." << std::endl;
        }


        void showTime(Time temp)
        {
            std::cout << temp.day << " " << temp.hour << " " << temp.min << " " << temp.sec << std::endl;
        }

        void showTimeInFile(Time temp, std::ostream& tempTimeFile)
        {
            tempTimeFile << temp.day << " " << temp.hour << " " << temp.min << " " << temp.sec << std::endl;
        }
};
