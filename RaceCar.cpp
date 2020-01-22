/*
Your car starts at position 0 and speed +1 on an infinite number line.  
(Your car can go into negative positions.)
Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).
When you get an instruction "A", your car does the following: position += speed, speed *= 2.
When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
Now for some target position, say the length of the shortest sequence of instructions to get there.

Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.

Example 2:
Input: 
target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0->1->3->7->7->6.

Note:
1 <= target <= 10000.
*/

class Node {
public:
    int pos;
    int speed;
    Node(const int _pos, const int _speed):
        pos(_pos), speed(_speed)
    {}
};

class Solution {
private:
    int bit_length(const int x) {
        unsigned int var = x < 0 ? -x : x;
        unsigned int bits;
        for (bits = 0; var; ++bits) {
            var >>= 1;
        }
        return bits; 
    }
    /********************************************************************************************************************************/
    std::string get_str_val(const int pos, const int speed) {
        return std::to_string(pos) + "$" + std::to_string(speed);
    }
    bool contains(std::unordered_set<std::string>& set, const int pos, const int speed) {
        return set.count(get_str_val(pos, speed));
    }
    void push(std::unordered_set<std::string>& set, const int pos, const int speed) {
        set.insert(get_str_val(pos, speed));
    }
	int solution1(const int target) {
        // BFS Algorithm
        /* Explanation:
         * We view this problem as a graph problem as follows:
         *  A node is characterized by two parameters {position, speed}
         *  Node {position, speed} has an edges to the following two nodes:
         *      { position + speed, 2 * speed }
         *      { position, speed > 0 ? -1 : 1 }
         * We are looking for shortest path to Node(s):
         *      { target, * }
         * where "*" indicates that the speed does not matter so long as we reach a node with position = target.
         * Since all edge weight are unity, we can run Breadth First Search in order to locate first such node.
         *
         * However, notice that everytime we pop from Queue, we insert two more node (due to above two edges).
         * This means our Q reaches size 2^N where N is the min # steps to reach target node.
         * Thus we need to do some smart pruning.
         * First, notice that the above edge transition might introduce cycles, so we need to cache previous visited nodes.
         * Secondly, notice that our position should never reach a negative position because not only does this leave us further
         * from target than we initially started with, but also, once we decide to turn back towards target, our speed returns to
         * unity and we begin a very slow/wasteful start towards target.
         * Thirdly, our optimal command will never begin or end with a reverse command because those commands do not change our
         * position and instead just waste a cmd.
         * So our optimal cmd will be of the form:
         *      A^k1 -> R -> A^k2 -> R -> ... -> R -> A^kn
         * where A^ki denotes ki acceleration commands.
         * Notice that since the above sequence converges towards target, we must have 
         *      k1 <= k2 <= ... <= kn
         * I.e., ki is monotone decreasing.
         * Key claim: 
         * ki < a+1 where a is the smallest integerr s.t. 2^a >= target.
         * This is because, if we surpass target, there is no need to keep driving since this adds more unnecessary commands and is
         * thus not optimal.
         * So, we never want to go past 0 towards negative infinity or past barrier = 2^bit_length(target).
         *
         * These pruning methods will make a BFS solution feasible.
         */
        const size_t barrier = 1 << bit_length(target);
        // Queue<Pair<distance, Node>>
        std::queue<std::pair<size_t, Node>> Q;
        Q.push({0, Node(0, 1)});
        // The underlying graph may have cycles so we need to make sure to memorize previous states
        std::unordered_set<std::string> set;
        push(set, 0, 1);
        
        while (not Q.empty()) {
            const size_t dist = Q.front().first;
            const Node v = Q.front().second;
            Q.pop();
            if (v.pos == target) {
                return dist;
            }
            // Accelerate
            const int acc_pos = v.pos + v.speed;
            const int acc_speed = 2 * v.speed;
            if (0 < acc_pos and acc_pos <= barrier and
                not contains(set, acc_pos, acc_speed)) {
                Q.push({dist+1, Node(acc_pos, acc_speed)});
                push(set, acc_pos, acc_speed);
            }
            // Reverse
            // We don't have to check that the reverse position is within boundaries because we already inserted it, 
            // so it must be valid.
            const int rev_pos = v.pos;
            const int rev_speed = v.speed > 0 ? -1 : 1;
            if (not contains(set, rev_pos, rev_speed)) {
                Q.push({dist+1, Node(rev_pos, rev_speed)});
                push(set, rev_pos, rev_speed);
            }
        }
         
        return -1;
	}
    /********************************************************************************************************************************/
    int* cache2;
    void init_cache2(const int target) {
        cache2 = new int[target+1];
        for (int t = 0; t <= target; ++t) {
            cache2[t] = -1;
        }
    }
    void destroy_cache() {
        delete[] cache2;
    }
    bool in_cache2(const int target) {
        return cache2[target] >= 0;
    }
    int set_cache2(const int target, const int min_steps) {
        return cache2[target] = min_steps;
    }
    int recurse2(const int t) {
        if (in_cache2(t)) {
            return cache2[t];
        }
        int min_steps = INT_MAX;
        
        int m = 1;
        int j = 1;
        for (; j < t; j = (1 << ++m) - 1) {
            for (int q = 0, p = 0; p < j; p = (1 << ++q) - 1) {
                min_steps = std::min(min_steps, m + 1 + q + 1 + recurse2(t - (j - p)));
            }
        }
        
        min_steps = std::min(min_steps, m + (j == t ? 0 : 1 + recurse2(j - t)));
                
        return set_cache2(t, min_steps);
    }
    int solution2(const int target) {
        /* Time-Complexity:     O(T * log^2(T))
         * Space-Complexity:    O(T)
         */
        /* Explanation:
         * Define:
         *  DP[t] = # minimum steps required to reach positon t, starting with default (position = 0, speed = 1)
         * 
         * We are interested in DP[target].
         * 
         * What are the transition functions?
         * When computing DP[t], we know that we are beginning from default.
         * If t == target, then we are finished, and we return 0.
         * More importantly, let's assume t < target.
         * Firstly, it is important to note that our speed does not return to 1 until after we initiate a reverse cmd.
         * Remember that our total command will be of the form "A^k1 -> R -> A^k2 -> R -> ... -> R -> A^kn".
         * This tells us that when computing DP[t] we may (possibly) need to reverse at some point(s).
         * First, we know that t < target, so we will have to initiate at least one acceleration cmd.
         * Say we need m acceleration cmds to reach position >= target.
         * Remember that m acceleration leaves us at positon 2^m - 1.
         * Let our current position be denoted by j = 2^m - 1.
         * While j < m:
         *  we haven't reached (or surpassed) target, and there is no way to directly transition to other DP[] states (yet).
         *  Supposed we decide to reverse at this point (maybe the optimal solution does this).
         *  Then we still cannot transitioin into other DP[] states because now we are facing the direction opposite of target.
         *  So it must be the case that if we reverse now, then we must initiate some number q of accelerations before reversing 
         *  again and facing target.
         *  At most how many accelerations can we initiate before reversing to face target?
         *  Well, we never want to accelerate so much that we end up in a negative positiom (pos < 0) since this means we will
         *  now be at an even further distance from target than we started with.
         *  Let q be number of accelerations we need after reversing and p be the position we end at after q accelerations, we 
         *  know that p = 2^q - 1.
         *  So if we reverse at positon j, then we will accelerate in opposite position (leaving us at p) and see if its worth to
         *  reverse again towards target, this means our command length is: m + 1 + q + 1 + DP[t - (j - p)]
         *  And we never let p exceed j since this symbollically means that we go past 0 in negative direction.
         *  Thus while we are in this loop we will minimize over the above double-reverse situation.
         * I.e., our loops looks like:
         * for (int m = 1, j = 1; j < target; ++m, j = 2^m - 1) {
         *      for (int p = 0, q = 0; p < j; ++q, p = 2^q - 1) {
         *          DP[target] = min{ DP[target], m + 1 + q + 1 + DP[target - (j - p)] }
         *      }
         * }
         *
         * We eventually reach a point where j >= target.
         *  if j == target:
         *      DP[target] = std::min{ DP[target], m }
         *  else:
         *      DP[target] = std::min{ DP[target], m + 1 + DP[j - target]
         */
        init_cache2(target);
        const int min_cmds = recurse2(target);
        destroy_cache();
        return min_cmds;
    }
    /********************************************************************************************************************************/
    int solution3(const int target) {
        /* Time-Complexity:     O(T * log^2(T))
         * Space-Complexity:    O(T)
         */
        /* Explanation:
         * DP Version of Solution2
         */
        std::vector<int> DP = std::vector<int>(target + 1, INT_MAX);
        for (int t = 1; t <= target; ++t) {
            int m = 1;
            int j = 1;
            for (; j < t; j = (1 << ++m) - 1) {
                for (int q = 0, p = 0; p < j; p = (1 << ++q) - 1) {
                    DP[t] = std::min(DP[t], m + 1 + q + 1 + DP[t - (j - p)]);
                }
            }
            DP[t] = std::min(DP[t], m + (j == t ? 0 : 1 + DP[j - t]));
        }
        
        return DP[target];
    }
    /********************************************************************************************************************************/
public:
    int racecar(int target) {
  		return solution2(target);
    }
};
