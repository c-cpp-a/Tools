#include "tools/matrix.cpp"
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    vector<vector<int>> x={{0},{1,2},{1},{1,2,3,4,5},{0,0,1}};
    matrix a=x;
    cout << a << endl << "a.trace=" << a.trace();
    return 0;
}
