from typing import List

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