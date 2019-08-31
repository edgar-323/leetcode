/*
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.
 
Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/

class Solution {
private:
    typedef std::vector<int> Person;
    typedef std::vector<Person> Queue;

    Queue solution1(Queue& Q) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */ 
        const size_t N = Q.size();
        // First Sort by Heights:
        std::sort(Q.begin(), Q.end(), 
                [] // No need to capture any variables
                (const Person& p1, const Person& p2) {
                    // Remember pi[0] is height and pi[1] is # ppl in front of person i whose height is >= height of person i.
                    // If two persons have same height, the one who sees less ppl in front of them must come before. 
                    return p1[0] == p2[0] ? // same height?
                             p1[1] <= p2[1] : // then p1 < p2 if p1 sees less ppl
                             p1[0] > p2[0];  // else, p1 < p2 if p1 is taller than p2 -> we want tall ppl in front (for now).
                }
        );
        // At this point, everybody is sorted within their heights.
        // Additionally, everybody in front of person i is at least as tall as person i (i.e., he can see everyone)
        // Now we can begin to compare by # of ppl that person i can see.
        for (size_t i = 1; i < N; ++i) {
            // Lets see how forward we can bring person i:
            // If # of ppl reported to be seen by person i is < its current positon, then we keep bringing him forward one step at a time
            for (size_t j = i; j and Q[j][1] < j; --j) {
                std::swap( Q[j-1], Q[j] );
            }
        }

        return Q;
    }
public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
        return solution1( people );            
    }
};
