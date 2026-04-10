#include "solution.h"
#include <unordered_map>

// Given a vector of integers and a target sum, return the indices of the two
// elements that add up to target. There is always exactly one valid pair.
//
// Tests cover:
//   - Basic case: pair at the start of the array ({2,7,11,15}, target=9 → {0,1})
//   - Pair in the middle: ({3,2,4}, target=6 → {1,2})
//   - Negative numbers: ({-1,-2,-3,-4,-5}, target=-8 → {2,4})
//
// The returned indices can be in any order. A brute-force O(n²) solution will
// pass, but try for O(n) using a hash map.
std::vector<int> two_sum(const std::vector<int>& nums, int target) {
    
    //The O(n^2) solution is a double for-each loop, go thru each index, and at each one, loop thru
    // the rest to see if any add up to the sum.  EZ PZ.

    //The O(n) solution is.... interesting.  In C++, std::unordered_map<int, int> represents a hash map, where each key is mapped to a value. 
    // When passing in a key, you need to first run a hash function to determine what the key should be.  With a good hash function, you are unlikely
    // to have collisions.
    // So if you are slotting in values from "nums" to the array as you go, you can check if ("target" - <current number>) exists in the map.  If it
    // does, you've found the 2 numbers, and just return both.
    std::unordered_map<int, int> valueMap;
    std::vector<int> returnVector;



    int size = nums.size();
    for (int i = 0; i < size; ++i)
    {
        //If i==0, just throw it in
        if (0 == i)
        {
            std::pair<int, int> vectorIndexValuePair(nums[i], i); //number as the key, for calculations later.
            valueMap.insert(vectorIndexValuePair);
        }
        else
        {
            int subtract = target - nums[i];
            std::unordered_map<int, int>::const_iterator iter = valueMap.find(subtract);
            if (iter != valueMap.cend())
            {
                // Found it
                returnVector.push_back(i);
                returnVector.push_back(iter->second); // The index is the value in the map.
                return returnVector;
            }
            else
            {
                // Didn't find it, add the value to the map
                std::pair<int, int> newPair(nums[i], i);
                valueMap.insert(newPair);
            }
        }
    }
    
    // I suppose reaching this point means there was no answer, and the data was wrong (or our algo was).

    return {};
}
