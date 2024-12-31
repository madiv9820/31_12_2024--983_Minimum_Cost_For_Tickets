#include <vector>
#include <set>
#include <functional>
using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // Create a vector to store the minimum cost for each day, initialized to 0
        // The size of the vector is the last travel day + 1 (to account for indexing)
        vector<int> ticketCost(days[days.size() - 1] + 1, 0);

        // Use a set to store the travel days for quick lookup
        set<int> travelling_Days(days.begin(), days.end());

        // Define a recursive lambda function to calculate the minimum cost for a given day
        function<int(int)> findCostForDay = [&](int day) -> int {
            // Base case: If the day is less than or equal to 0, no cost is needed
            if (day <= 0) return 0;

            // If the cost for the current day has already been calculated, return it
            if (ticketCost[day] != 0) return ticketCost[day];

            // If the current day is not a travel day, the cost is the same as the previous day
            if (travelling_Days.find(day) == travelling_Days.end()) {
                ticketCost[day] = findCostForDay(day - 1);
            } else {
                // Calculate the cost if we buy a 1-day, 7-day, or 30-day pass
                int cost1 = findCostForDay(day - 1) + costs[0];     // Cost with a 1-day pass
                int cost7 = findCostForDay(day - 7) + costs[1];     // Cost with a 7-day pass
                int cost30 = findCostForDay(day - 30) + costs[2];   // Cost with a 30-day pass

                // Take the minimum of the three options
                ticketCost[day] = min(cost1, min(cost7, cost30));
            }

            // Return the calculated cost for the current day
            return ticketCost[day];
        };

        // Start the calculation from the last travel day
        return findCostForDay(days[days.size() - 1]);
    }
};