#include "solution.h"

// Merge two already-sorted vectors into a single sorted vector.
//
// Tests cover:
//   - Basic merge: {1,3,5} + {2,4,6} → {1,2,3,4,5,6}
//   - One empty input: the other is returned as-is
//   - Both empty: returns {}
//   - Duplicates across inputs: {1,2,3} + {2,3,4} → {1,2,2,3,3,4}
//   - Duplicates within one input: {1,1,1} + {1,1} → {1,1,1,1,1}
//   - Different lengths: short + long
//   - Negative numbers and mixed signs
//   - Non-overlapping ranges: {1,2,3} + {10,20,30}
//   - Large inputs (100k elements each)
//
// Aim for O(n + m) using two pointers, not O((n+m) log(n+m)) via concat+sort.
std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    
    std::vector<int> retVector;

    size_t aSize = a.size();
    size_t bSize = b.size();

    int aIndex = 0;
    int bIndex = 0;
    while (aIndex < aSize && bIndex < bSize)
    {
        if (a[aIndex] > b[bIndex])
        {
            retVector.push_back(b[bIndex]);
            bIndex++;
        }
        else
        {
            retVector.push_back(a[aIndex]);
            aIndex++;
        }
    }

    if (aIndex < aSize)
    {
        //If we got through all of the values in vector b, and there are still values in vector a, we assume that all of the values in b are greater,
        // and add them to the return vector.
        for (; aIndex < aSize; ++aIndex)
        {
            retVector.push_back(a[aIndex]);
        }
    }
    else if (bIndex < bSize)
    {
        //If we got through all of the values in vector a, and there are still values in vector b, we assume that all of the values in b are greater,
        // and add them to the return vector.
        for (; bIndex < bSize; ++bIndex)
        {
            retVector.push_back(b[bIndex]);
        }
    }

    return retVector;
}
