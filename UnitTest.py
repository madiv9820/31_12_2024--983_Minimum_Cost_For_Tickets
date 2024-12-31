from timeout_decorator import timeout
import unittest
from Solution import Solution

class UnitTest(unittest.TestCase):
    def setUp(self):
        self.__testCases = {1: ([1,4,6,7,8,20], [2,7,15], 11), 
                            2: ([1,2,3,4,5,6,7,8,9,10,30,31], [2,7,15], 17)}
        self.__obj = Solution()
        return super().setUp()
    
    @timeout(0.5)
    def test_case_1(self):
        days, costs, output = self.__testCases[1]
        result = self.__obj.mincostTickets(days, costs)
        self.assertIsInstance(result, int)
        self.assertEqual(result, output)

    @timeout(0.5)
    def test_case_2(self):
        days, costs, output = self.__testCases[2]
        result = self.__obj.mincostTickets(days, costs)
        self.assertIsInstance(result, int)
        self.assertEqual(result, output)

if __name__ == '__main__': unittest.main()