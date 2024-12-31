- ## Approach 2:- Memoization
    
    - ### Intuition  
        The problem is about finding the minimum cost of covering specific travel days using three types of passes (1-day, 7-day, and 30-day) with given costs. The goal is to decide which pass to use on each travel day to minimize the total cost. By recursively calculating the cost for each day and storing intermediate results (memoization), we avoid recalculating values for overlapping subproblems, leading to an efficient solution.

    - ### Approach  
        1. **Dynamic Programming Array (`ticketCost`)**:  
            - Use an array to store the minimum cost for each day up to the last travel day.  
            - The array is initialized with 0 for all days, as non-travel days incur no additional cost.  

        2. **Travel Days Set**:  
            - Use a set to store the travel days, allowing quick lookup to determine whether a given day requires a ticket.  

        3. **Recursive Lambda Function (`findCostForDay`)**:  
            - Define a recursive function that calculates the minimum cost for any given day.  
            - **Base Case**: If the day is less than or equal to 0, the cost is 0 (no travel required).  
            - **Memoization**: Check if the cost for the current day has already been calculated to avoid redundant computation.  
            - **Travel Day Check**: If the current day is not a travel day, inherit the cost from the previous day.  
            - **Cost Calculation**: If it's a travel day, calculate the cost for:  
                    - A 1-day pass (add the cost to the previous day's minimum cost).  
                    - A 7-day pass (add the cost to the minimum cost of 7 days ago).  
                    - A 30-day pass (add the cost to the minimum cost of 30 days ago).  
            - Take the minimum of the three options and store it in the DP array.  

        4. **Final Result**:  
            - Start the computation from the last travel day (highest in the input `days` array) to ensure all relevant days are considered.  

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def mincostTickets(self, days: List[int], costs: List[int]) -> int:
                    # Create an array `ticketCost` where ticketCost[i] will store the minimum cost to cover travel up to day i
                    # Initialize the array to 0. The array size is `days[-1] + 1` to accommodate all days up to the last travel day.
                    ticketCost = [0] * (days[-1] + 1)
                    
                    # Set of travel days for fast lookup
                    travelling_Days = set(days)
                    
                    # Recursive function to calculate the minimum cost for a given day
                    def findCostForDay(day: int) -> int:
                        # Base case: If day is 0 or negative, no cost is required (0 cost)
                        if day <= 0: 
                            return 0
                        
                        # If we already have computed the cost for this day, return it to avoid recomputation
                        if ticketCost[day] != 0: 
                            return ticketCost[day]

                        # If it's not a travel day, carry forward the previous day's cost
                        if day not in travelling_Days: 
                            ticketCost[day] = findCostForDay(day-1)
                        else:
                            # If it is a travel day, calculate the cost for all 3 possible ticket options
                            # Option 1: Buy a 1-day pass (previous day + 1-day pass)
                            cost1 = findCostForDay(day-1) + costs[0]
                            
                            # Option 2: Buy a 7-day pass (7 days back + 7-day pass)
                            cost7 = findCostForDay(day-7) + costs[1]
                            
                            # Option 3: Buy a 30-day pass (30 days back + 30-day pass)
                            cost30 = findCostForDay(day-30) + costs[2]

                            # Store the minimum cost from the 3 options
                            ticketCost[day] = min(cost1, cost7, cost30)
                        
                        # Return the minimum cost to cover the travel up to the current day
                        return ticketCost[day]
                    
                    # The answer will be the minimum cost to cover all travel days, which will be computed for the last day in the list
                    return findCostForDay(days[-1])
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity  
        - **$O(D)$**, where `D` is the maximum travel day (`days[-1]`):  
            - Each day is processed once due to memoization.  
            - Checking if a day is in the set of travel days is O(1).  
            - Total iterations are limited by the range of `D`.  

    - ### Space Complexity  
        - **$O(D)$**:  
            - The `ticketCost` array requires space proportional to the maximum travel day (`D`).  
            - The travel days set requires O(N) space, where `N` is the number of travel days.  
            - The recursive call stack depth is proportional to `D` in the worst case.  