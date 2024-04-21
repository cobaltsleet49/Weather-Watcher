#include "RedBlackTree.h"
#include "HashTable.h"

// You can add more data sets at https://www.ncei.noaa.gov/access/monitoring/climate-at-a-glance/county/mapping
// Format for the .csv files is "Year-Month-P/T", where P stands for precipitation and T for average temperature

using namespace std;

int main() {
    RedBlackTree test;

    test.buildTree();

    return 0;
}
