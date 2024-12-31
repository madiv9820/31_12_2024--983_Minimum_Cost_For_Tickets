#include "Solution.cpp"
#include <iostream>
using namespace std;

struct testcase {
    vector<int> days;
    vector<int> costs;
    int output;
};

class UnitTest {
private:
    Solution obj;
    vector<testcase> testCases;
public:
    UnitTest() {
        testCases = {{{1,4,6,7,8,20}, {2,7,15}, 11}, 
                     {{1,2,3,4,5,6,7,8,9,10,30,31}, {2,7,15}, 15}};
    }

    void test() {
        for(int index = 0; index < testCases.size(); ++index) {
            vector<int> days = testCases[index].days, costs = testCases[index].costs;
            int output = testCases[index].output;
            int result = obj.mincostTickets(days, costs);
            cout << "TestCase " << index+1 << ": " << ((result == output) ? "passed":"failed") << endl;
        }
    }
};