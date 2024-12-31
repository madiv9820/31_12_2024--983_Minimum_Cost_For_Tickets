# 983. Minimum Cost For Tickets (All Approaches)

- ## Approach 1:- Recursion

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

- ## Approach 3:- Dynamic Programming

    - ### Intuition
        The problem asks us to find the minimum cost required to cover all the travel days given the option to buy different types of tickets (1-day, 7-day, or 30-day passes). The goal is to minimize the total cost while ensuring all travel days are covered, and we can make the decision of which pass to buy based on the cost incurred up to that day.

        We use dynamic programming (DP) to solve this problem efficiently. The idea is to maintain an array `ticketCost` where each entry at index `i` represents the minimum cost to cover all travel days up to day `i`. By iterating through the days and checking the available ticket options for each travel day, we can decide the optimal pass to buy at each step.

        #### Key Insights:
        1. If we’re not traveling on a given day, the cost is the same as the previous day (i.e., no new ticket is needed).
        2. If we are traveling on a day, we have three options:
            - Buy a 1-day pass, which adds the cost of the previous day + the 1-day pass price.
            - Buy a 7-day pass, which looks 7 days back and adds the cost of that day + the 7-day pass price.
            - Buy a 30-day pass, which looks 30 days back and adds the cost of that day + the 30-day pass price.
        3. The solution builds up the cost incrementally, choosing the minimum cost option at each step.

    - ### Approach
        1. **Initialize the `ticketCost` array**: 
            - This array stores the minimum cost to cover travel up to each day, where `ticketCost[i]` represents the minimum cost for the first `i` days.
        
        2. **Travel Days Set**: 
            - We maintain a set of travel days to quickly check if a specific day requires a ticket purchase.
        
        3. **Iterate through each day**:
            - For each day from 1 to the last travel day, if it’s a travel day, calculate the three possible costs:
                - **1-day pass**: Add the cost of the previous day’s ticket and the price of a 1-day pass.
                - **7-day pass**: Add the cost of the day 7 days ago (if possible) and the price of a 7-day pass.
                - **30-day pass**: Add the cost of the day 30 days ago (if possible) and the price of a 30-day pass.
        
        4. **Update the `ticketCost` array**: 
            - For each travel day, the minimum cost is stored in `ticketCost[i]`.

        5. **Final Answer**:
            - After processing all the days, the value at `ticketCost[total_No_of_Travelling_Days]` will contain the minimum cost required to cover all travel days.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def mincostTickets(self, days: List[int], costs: List[int]) -> int:
                    # Total number of days in the travel plan (last travel day in the input)
                    total_No_of_Travelling_Days = days[-1]
                    
                    # Array to store the minimum cost for each day from 1 to total_No_of_Travelling_Days
                    ticketCost = [0] * (total_No_of_Travelling_Days + 1)
                    
                    # Set of all days on which travel happens (for faster lookup)
                    travelling_Days = {day: True for day in days}

                    # Iterate over each day from 1 to total_No_of_Travelling_Days
                    for day in range(1, total_No_of_Travelling_Days + 1):
                        if day not in travelling_Days:
                            # If no travel is scheduled for this day, carry forward the previous day's cost
                            ticketCost[day] = ticketCost[day - 1]
                        else:
                            # If today is a travel day, compute the cost for different pass options

                            # Option 1: Buy a 1-day pass (add the cost of previous day + 1-day pass)
                            cost1 = ticketCost[day - 1] + costs[0]
                            
                            # Option 2: Buy a 7-day pass (look 7 days back, add cost of 7-day pass)
                            cost7 = ticketCost[max(0, day - 7)] + costs[1]
                            
                            # Option 3: Buy a 30-day pass (look 30 days back, add cost of 30-day pass)
                            cost30 = ticketCost[max(0, day - 30)] + costs[2]

                            # Choose the minimum cost among the 3 options and store it
                            ticketCost[day] = min(cost1, cost7, cost30)

                    # Return the minimum cost to cover all the travel days (i.e., on the last day)
                    return ticketCost[-1]
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **$O(n)$**: We loop through all the days from 1 to the last travel day. For each day, we compute the cost for three ticket options, and each computation takes constant time.
            - Here, `n` is the number of days in the travel plan (i.e., the last travel day, which is `days[-1]`).
    
            The overall time complexity is linear with respect to the number of travel days.

    - ### Space Complexity
        - **$O(n)$**: We use an array `ticketCost` of size `n + 1` to store the minimum cost for each day. Additionally, we use a set `travelling_Days` to track the days on which we need to travel. Both of these data structures take linear space in relation to the total number of days.