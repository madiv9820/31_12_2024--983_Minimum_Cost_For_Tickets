from typing import List

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