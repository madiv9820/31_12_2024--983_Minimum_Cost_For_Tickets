- ## Approach 1:- Dynamic Programming

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