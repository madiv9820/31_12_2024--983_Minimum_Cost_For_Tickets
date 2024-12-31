#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // Total number of days in the travel plan (last travel day in the input)
        int total_No_of_Travelling_Days = days[days.size() - 1];
        
        // Vector to store the minimum cost for each day from 1 to total_No_of_Travelling_Days
        vector<int> ticketCost(total_No_of_Travelling_Days + 1, 0);
        
        // Set of all days on which travel happens (for faster lookup)
        set<int> travelling_Days(days.begin(), days.end());

        // Iterate over each day from 1 to total_No_of_Travelling_Days
        for (int day = 1; day <= total_No_of_Travelling_Days; ++day) {
            // If the current day is not a travel day, carry forward the previous day's cost
            if (travelling_Days.find(day) == travelling_Days.end()) {
                ticketCost[day] = ticketCost[day - 1];
            }
            else {
                // Option 1: Buy a 1-day pass (add the cost of previous day + 1-day pass)
                int cost1 = ticketCost[day - 1] + costs[0];
                
                // Option 2: Buy a 7-day pass (look 7 days back, add cost of 7-day pass)
                int cost7 = ticketCost[max(0, day - 7)] + costs[1];
                
                // Option 3: Buy a 30-day pass (look 30 days back, add cost of 30-day pass)
                int cost30 = ticketCost[max(0, day - 30)] + costs[2];
                
                // Take the minimum cost among the 3 options and store it
                ticketCost[day] = min(cost1, min(cost7, cost30));
            }
        }

        // Return the minimum cost to cover all the travel days (i.e., on the last day)
        return ticketCost[total_No_of_Travelling_Days];
    }
};