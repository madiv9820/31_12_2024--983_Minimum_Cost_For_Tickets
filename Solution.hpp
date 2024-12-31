#include <vector>
#include <functional>
#include <set>
using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // Use a set to store the travel days for quick lookup
        set<int> travelling_Days(days.begin(), days.end());

        // Define a recursive lambda function to calculate the minimum cost for a given day
        function<int(int)> findCostForDay = [&](int day) -> int {
            // Base case: If the day is less than or equal to 0, no cost is needed
            if (day <= 0) return 0;

            // If the current day is not a travel day, the cost is the same as the previous day
            if (travelling_Days.find(day) == travelling_Days.end()) {
                return findCostForDay(day - 1);
            }

            // Calculate the cost if we buy a 1-day, 7-day, or 30-day pass
            int cost1 = findCostForDay(day - 1) + costs[0];     // Cost with a 1-day pass
            int cost7 = findCostForDay(day - 7) + costs[1];     // Cost with a 7-day pass
            int cost30 = findCostForDay(day - 30) + costs[2];   // Cost with a 30-day pass

            // Return the calculated cost for the current day
            return min(cost1, min(cost7, cost30));
        };

        // Start the calculation from the last travel day
        return findCostForDay(days[days.size() - 1]);
    }
};