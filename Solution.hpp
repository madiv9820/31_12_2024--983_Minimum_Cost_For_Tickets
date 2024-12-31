#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int total_No_of_Travelling_Days = days[days.size()-1];
        vector<int> ticketCost(total_No_of_Travelling_Days + 1, 0);
        set<int> travelling_Days(days.begin(), days.end());

        for(int day = 1; day <= total_No_of_Travelling_Days; ++day) {
            if(travelling_Days.find(day) == travelling_Days.end()) ticketCost[day] = ticketCost[day-1];
            else {
                int cost1 = ticketCost[day-1] + costs[0];
                int cost7 = ticketCost[max(0, day-7)] + costs[1];
                int cost30 = ticketCost[max(0, day-30)] + costs[2];
                ticketCost[day] = min(cost1, min(cost7, cost30));
            }
        }

        return ticketCost[total_No_of_Travelling_Days];
    }
};