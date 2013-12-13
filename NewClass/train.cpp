std::string getTrainName()
{
    std::string s = "Train";
    s = s + (char)(trainID + '0');
    return s;
}

