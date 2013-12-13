#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cout << s << endl;
    s = s + "Add a string.\n";
    cout << s << endl;
    char c = 'c';
    s = s + c;
    cout << s << endl;
    int n = 5;
    s = s + (char)(n+'0');
    cout << s << endl;
    return 0;
}
