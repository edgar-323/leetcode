/*
A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 231.
The first stone's position is always 0.
Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as 
the gap between the 5th and 6th stone is too large.
*/

class Solution {
private:
    int N;
    /********************************************************************************************************************************/
    std::unordered_map<int, bool>* cache1;
    bool* seen_index;
    void init_cache1() {
        cache1 = new std::unordered_map<int, bool>[N];
        seen_index = new bool[N];
        for (int i = 0; i < N; ++i) {
            seen_index[i] = false;
        }
    }
    void destroy_cache1() {
        delete[] cache1;
        delete[] seen_index;
    }
    bool in_cache1(const int i, const int leap) {
        return seen_index[i] and cache1[i].count(leap);
    }
    bool get_cache1(const int i, const int leap) {
        return cache1[i].at(leap);
    }
    bool set_cache1(const int i, const int leap, const bool val) {
        cache1[i].insert({leap, val});
        return get_cache1(i, leap);
    }
    int recurse1(
            const int i,
            const int leap,
            const std::vector<int>& stones,
            const std::unordered_map<int, int>& leap_map) {
        if (in_cache1(i, leap)) {
            return get_cache1(i, leap);
        }
        const int unit = stones[i];
        const bool can_cross =  i == N-1 or 
                                (leap_map.count(unit + leap + 1) and recurse1(leap_map.at(unit + leap + 1), leap+1, stones, leap_map)) or
                                (leap > 0 and leap_map.count(unit + leap) and recurse1(leap_map.at(unit + leap), leap, stones, leap_map)) or 
                                (leap-1 > 0 and leap_map.count(unit + leap - 1) and recurse1(leap_map.at(unit + leap - 1), leap-1, stones, leap_map));
        return set_cache1(i, leap, can_cross);
    }
    int solution1(const std::vector<int>& stones) {
        /* Time-Complexity:     O(N * 2^31)
         * Space-Complexity:    O(N * 2^31)
         */
        /* Explanation:
         * First we compute MAP<position, index> which tells
         * us whether some position maps to a valid stone index.
         * We cached the brute force solution.
         * This solution computes on the state:
         *      { i, leap }
         * where i in the current stone index, and leap is the
         * last leap we did.
         * We assume we got to stone i using leap.
         * If i is the last stone, then the answer is true.
         * Else we recurse on the following states:
         *      { leap_map[i+leap+1], leap+1 }  if (i+leap+1) is stone position
         *      { leap_map[i+leap],   leap }    if leap > 0 and (i+leap) is stone position
         *      { leap_map[i+leap-1], leap-1}   if leap-1 > 0 and (i+leap-1) is stone position
         * If none of above are true then answer is false.
         * Having to cache the leap paramter is a very bad idea since according to the description
         * it is bounded by 2^31 (huge number).
         */
        N = stones.size();
        std::unordered_map<int, int> leap_map;
        for (int i = 0; i < N; ++i) {
            leap_map.insert({stones[i], i});
        }
        init_cache1();
        const int can_cross = recurse1(0, 0, stones, leap_map);
        destroy_cache1();

        return can_cross;
    }
    /********************************************************************************************************************************/
    int** cache2;
    void init_cache2() {
        cache2 = new int*[N];
        for (int i = 0; i < N; ++i) {
            cache2[i] = new int[N];
            for (int j = 0; j < N; ++j) {
                cache2[i][j] = -1;
            }
        }
    }
    void destroy_cache2() {
        for (int i = 0; i < N; ++i) {
            delete[] cache2[i];
        }
        delete[] cache2;
    }
    bool in_cache2(const int i, const int j) {
        return cache2[i][j] >= 0;
    }
    bool get_cache2(const int i, const int j) {
        return cache2[i][j];
    }
    bool set_cache2(const int i, const int j, const int val) {
        return cache2[i][j] = val;
    }
    int recurse2(
            const int i,
            const int j,
            const std::vector<int>& stones,
            const std::unordered_map<int, int>& leap_map) {
        // we got to stone i from stone j
        if (in_cache2(i, j)) {
            return get_cache2(i, j);
        }
        const int leap = stones[j] - stones[i];
        const int unit = stones[j];
        bool can_cross =    j == N-1 or 
                            (leap_map.count(unit+leap+1) and recurse2(j, leap_map.at(unit+leap+1), stones, leap_map)) or
                            (leap > 0 and leap_map.count(unit+leap) and recurse2(j, leap_map.at(unit+leap), stones, leap_map)) or
                            (leap-1 > 0 and leap_map.count(unit+leap-1) and recurse2(j, leap_map.at(unit+leap-1), stones, leap_map)); 

        return set_cache2(i, j, can_cross);
    }

    int solution2(const std::vector<int>& stones) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        /* Explanation:
         * Equivalent to solution1 except that we compute on states of the following form:
         *      { i, j }
         * This tells us that we reached stone j by leaping from stone i.
         * Then we can deduce the leap paramter as follows:
         *      leap = stones[j] - stones[i].
         * This rids us of the complexity of the leap paramter but introduces another factor
         * of N to the runtime.
         */
        N = stones.size();
        std::unordered_map<int, int> leap_map;
        for (int i = 0; i < N; ++i) {
            leap_map.insert({stones[i], i});
        }
        init_cache2();
        const int can_cross = recurse2(0, 0, stones, leap_map);
        destroy_cache2();

        return can_cross;
    }
    /********************************************************************************************************************************/
    int solution3(const std::vector<int>& stones) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         */
        /* Explanation:
         * DP Version of Solution2.
         */
        N = stones.size();
        std::unordered_map<int, int> leap_map;
        for (int i = 0; i < N; ++i) {
            leap_map.insert({stones[i], i});
        }
        auto DP = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
        for (int i = 0; i < N; ++i) {
            DP[i][N-1] = true;
        }
        for (int j = N-2; j >= 0; --j) {
            const int unit = stones[j];
            for (int i = j; i >= 0; --i) {
                const int leap = stones[j] - stones[i];
                DP[i][j] =  DP[i][j] or 
                            (leap_map.count(unit + leap + 1) and DP[j][leap_map[unit + leap + 1]]) or
                            (leap > 0 and leap_map.count(unit + leap) and DP[j][leap_map[unit + leap]]) or
                            (leap-1 > 0 and leap_map.count(unit + leap - 1) and DP[j][leap_map[unit + leap - 1]]);
            }
        }

        return DP[0][0];
    }
    /********************************************************************************************************************************/
public:
    bool canCross(vector<int>& stones) {
        return solution3(stones);
    }
};
