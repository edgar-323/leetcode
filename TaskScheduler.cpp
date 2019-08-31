/*
Given a char array representing tasks CPU need to do. 
It contains capital letters A to Z where different letters represent different tasks. 
Tasks could be done without original order. 
Each task could be done in one interval. 
For each interval, CPU could finish one task or just be idle.
However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.
You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
 
Note:
The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].
*/

class Pair {
public:
    int cycles;
    int coolDown;
    
    Pair(int c1) {
        cycles = c1;
        coolDown = 0;
    }
    
    bool operator < (const Pair& other) const {
        return this->cycles > other.cycles;
    }
};

class Solution {
private:
    /*******************************************************************/	 
    int solution1(std::vector<char>& tasks, int M) {
        const int N = tasks.size();
        const int ALPH_SZ = 26;
        std::pair<int, int> map[ALPH_SZ];
        for (int i = 0; i < ALPH_SZ; ++i) {
            map[i].first = map[i].second = -1;
        }
        for (char task : tasks) {
            auto& p = map[task-'A'];
            if (p.first < 0) {
                p.first = p.second = 0;
            } 
            (p.first)++;
        }
        
        int total = 0;
        for (int rem = N; rem > 0; ++total) {
            bool reduced = false;
            for (int i = 0; i < ALPH_SZ; ++i) {
                auto& p = map[i];
                if (p.first <= 0) {
                    continue;
                } else if (p.second <= 0 && !reduced) {
                    reduced = true;
                    rem--;
                    p.first--;
                    p.second = M;
                } else {
                    p.second--;
                }
            }
        }
        
        return total;
    }
    /*******************************************************************/
    int solution2(std::vector<char>& tasks, int M) {
        const int ALPH_SZ = 26;
        int count[ALPH_SZ];
        for (int i = 0; i < ALPH_SZ; ++i) {
            count[i] = -1;
        }
        for (auto task : tasks) {
            int i = task - 'A';
            if (count[i] < 0) {
                count[i] = 0;
            }
            ++count[i];
        }
        std::vector<Pair> vec;
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (count[i] > 0) {
                vec.push_back(Pair(count[i]));
            }
        }
    
        const int K = vec.size();
        int minCycles = 0;
        for (int rem = tasks.size(); rem > 0; ++minCycles) {
            // O( ALPH_SZ * log( ALPH_SZ ) )
            std::sort(vec.begin(), vec.end());
            bool usedCycle = false;
            for (int i = 0; i < K; ++i) {
                Pair& p = vec[i];
                if (p.cycles <= 0) {
                    continue;
                } else if (p.coolDown <= 0 && !usedCycle) {
                    p.cycles--;
                    p.coolDown = M;
                    rem--;
                    usedCycle = true;
                } else {
                    p.coolDown--;
                }
            }
        }
        
        return minCycles;
    } 
    /*******************************************************************/ 
public:
    int leastInterval(vector<char>& tasks, int n) {
        return solution2(tasks, n);
    }
};
