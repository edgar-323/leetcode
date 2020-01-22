/*
Given a positive integer n, return the number of all possible attendance records with length n, which will be regarded as rewardable. 
The answer may be very large, return it after mod 109 + 7.

A student attendance record is a string that only contains the following three characters:
    1)  'A' : Absent.
    2)  'L' : Late.
    3)  'P' : Present.
A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

Example 1:
Input: n = 2
Output: 8 
Explanation:
There are 8 records with length 2 will be regarded as rewardable:
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" won't be regarded as rewardable owing to more than one absent times. 

Note: The value of n won't exceed 100,000.
*/

class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;
    int N;

    int recurse1(
            const int rec_len, 
            const int absences, 
            const int recent_tardies,
            std::vector<std::vector<std::vector<int>>>& cache) {
        // Assumes absences <= 1 and  recent_tardies <= 2. 
        if (rec_len == N) {
            return 1;
        } else if (cache[rec_len][absences][recent_tardies] >= 0) {
            return cache[rec_len][absences][recent_tardies];
        }
        // decide which value to put next
        int result = recurse1(rec_len + 1, absences, 0, cache);
        if (absences == 0) {
            result = (result + recurse1(rec_len + 1, 1, 0, cache)) % MOD_VAL;
        }
        if (recent_tardies < 2) {
            result = (result + recurse1(rec_len + 1, absences, recent_tardies + 1, cache)) % MOD_VAL;
        }

        return cache[rec_len][absences][recent_tardies] = (result % MOD_VAL);
    }

    int solution1(const int N) {
        /* Time-Complexity:     O(2*3*N) = O(N)
         * Space-Complexity:    O(2*3*N) = O(N)
         */
        this->N = N;
        auto cache = std::vector<std::vector<std::vector<int>>>(N, 
                        std::vector<std::vector<int>>(2, 
                            std::vector<int>(3, -1)));
        return recurse1(0, 0, 0, cache); 
    }
public:
    int checkRecord(int n) {
        return solution1(n);        
    }
};
