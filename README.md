- ## Approach 3:- Recursion

    - ### Intuition  
        The problem revolves around minimizing the cost of traveling on specific days using three types of passes (1-day, 7-day, and 30-day) with associated costs. The solution requires deciding the optimal pass for each travel day to minimize the overall expense. The key observation is that the cost for a specific day depends on whether it is a travel day and the cost incurred by choosing different passes. By using recursion and considering overlapping subproblems (e.g., calculating costs for overlapping ranges of days), we can find the minimum cost efficiently.

    - ### Approach  
        1. **Travel Days Set**:  
            - Use a set to store the travel days for quick lookup, ensuring O(1) complexity when checking if a day is a travel day.

        2. **Recursive Function (`findCostForDay`)**:  
            - Define a recursive function that computes the minimum cost to cover travel up to a given day.  
            - **Base Case**:  
                - If the day is `<= 0`, no travel is required, and the cost is 0.  
            - **Non-Travel Day**:  
                - If the day is not in the set of travel days, inherit the cost of the previous day (no additional cost).  
            - **Travel Day**:  
                - Calculate the cost for all three pass options:
                    - **1-Day Pass**: Add the cost of a 1-day pass to the cost of `day - 1`.  
                    - **7-Day Pass**: Add the cost of a 7-day pass to the cost of `day - 7`.  
                    - **30-Day Pass**: Add the cost of a 30-day pass to the cost of `day - 30`.  
                - Take the minimum of these three options as the cost for the current day.

        3. **Final Calculation**:  
            - Begin the recursion from the last travel day (`days[-1]`) and calculate the minimum cost for all travel days.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def mincostTickets(self, days: List[int], costs: List[int]) -> int:
                    # Set of travel days for fast lookup
                    travelling_Days = set(days)
                    
                    # Recursive function to calculate the minimum cost for a given day
                    def findCostForDay(day: int) -> int:
                        # Base case: If day is 0 or negative, no cost is required (0 cost)
                        if day <= 0: 
                            return 0
                        
                        # If it's not a travel day, carry forward the previous day's cost
                        if day not in travelling_Days: 
                            return findCostForDay(day-1)
                        
                        # If it is a travel day, calculate the cost for all 3 possible ticket options
                        # Option 1: Buy a 1-day pass (previous day + 1-day pass)
                        cost1 = findCostForDay(day-1) + costs[0]
                        
                        # Option 2: Buy a 7-day pass (7 days back + 7-day pass)
                        cost7 = findCostForDay(day-7) + costs[1]
                        
                        # Option 3: Buy a 30-day pass (30 days back + 30-day pass)
                        cost30 = findCostForDay(day-30) + costs[2]

                        # Return the calculated cost for the current day
                        return min(cost1, cost7, cost30)
                                
                    # Start the calculation from the last travel day
                    return findCostForDay(days[-1])
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity  
        - **$O(3^N)$**, where `N` is the number of travel days:  
            - The recursive solution explores all three options (1-day, 7-day, and 30-day passes) for every travel day, leading to exponential growth in computations.  
            - This is inefficient for large inputs.  

    - ### Space Complexity  
        - **$O(N)$**:  
            - The maximum recursion depth is proportional to the number of travel days (`N`).  
            - Additional space is required for the `travelling_Days` set, which is $O(N)$.  