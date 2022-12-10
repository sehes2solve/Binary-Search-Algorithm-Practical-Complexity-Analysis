#include <iostream>
#include "Searcher.h"
using namespace std;

int main()
{
    Searcher<string> s("test.txt");
    s.testPerformance();
    s.display_avg();
    return 0;
}
