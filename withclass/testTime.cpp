#include "time.hpp"

int main()
{
    Time t;
    t.print();
    Time t1 ( 1, 2, 3, 4);
    t1.print();
    t1.minus(t).print();
    return 0;
}
