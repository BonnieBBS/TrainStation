#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream file ("testfile.txt");
    if(file.is_open())
    {
        file << "Line 1" << endl;
        file << "Line 2" << endl;
        file.close();
    }
    return 0;
}
