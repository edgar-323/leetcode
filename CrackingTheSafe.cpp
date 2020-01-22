/*
There is a box protected by a password. 
The password is a sequence of n digits where each digit can be one of the first k digits 0, 1, ..., k-1.

While entering a password, the last n digits entered will automatically be matched against the correct password.

For example, assuming the correct password is "345", if you type "012345", the box will open because the correct password matches the suffix of the entered password.

Return any password of minimum length that is guaranteed to open the box at some point of entering it.

Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.

Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.
 
Note:
n will be in the range [1, 4].
k will be in the range [1, 10].
k^n will be at most 4096.
*/
class Solution {
private:
    int N,K;
    int V;

    char to_char(const int k) {
        return k + '0';
    }

    bool recurse1(std::string& result, std::unordered_set<std::string>& seen) {
        if (seen.size() == V) {
            return true;
        }
        auto curr_node = result.substr(result.size() - (N-1));
        for (int k = 0; k < K; ++k) {
            auto neighbor_node = curr_node + std::string(1, to_char(k));
            if (not seen.count(neighbor_node)) {
                seen.insert(neighbor_node);
                result.push_back(to_char(k));
                if (recurse1(result, seen)) {
                    return true;
                }
                result.pop_back();
                seen.erase(neighbor_node); 
            }
        }
        return false;
    }

    std::string solution1(const int n, const int k) {
        /* Explanation:
         * This is a VERY difficult problem to simply understand (let alone come up with a solution).
         * First watch video: https://www.youtube.com/watch?v=iPLQgXUiU14
         * 
         * Now Lets talk about the solution...
         * After watching that video you will notice that a (there are multiple possible ones) solution has length K^N 
         * (The total number of possible solutions is (K!)^(K^(N-1)) / K^N)
         * So we know there are K^N total nodes.
         * Furthermore, we will solve this problem via construction of a Hamiltonian path (starting at some node).
         * Suppose we are at some node v (v has N total digits).
         * Then, we saw in the video that a neighbor of v will be some node whose prefix of size N-1 is the suffix of the curent node of size N-1.
         */
        N = n;
        K = k;
        V = std::pow(K, N);

        auto result = std::string(N, '0'); // start node
        auto seen = std::unordered_set<std::string>();
        seen.insert(result);

        recurse1(result, seen);

        return result;
    }
public:
    string crackSafe(int n, int k) {
        return solution1(n, k);        
    }
};
