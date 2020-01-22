/*
A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].

Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.

Note:

A transaction will be given as a tuple (x, y, z). Note that x ≠ y and z > 0.
Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.
Example 1:

Input:
[[0,1,10], [2,0,5]]

Output:
2

Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.

Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.
Example 2:

Input:
[[0,1,10], [1,0,1], [1,2,5], [2,0,5]]

Output:
1

Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.

Therefore, person #1 only need to give person #0 $4, and all debt is settled.
*/
class Solution {
private:
    int N;

    std::vector<int> build_debt_array(const std::vector<std::vector<int>>& transactions) {

        auto debt_map = std::unordered_map<int,int>();
        for (const auto& transaction : transactions) {
            const auto giver = transaction[0];
            const auto taker = transaction[1];
            const auto amount = transaction[2];
            debt_map[giver] += amount;
            debt_map[taker] -= amount;
        }

        auto debt = std::vector<int>(debt_map.size());
        int index = 0;
        for (const auto& p : debt_map) {
            debt[index++] = p.second;
        }
        return debt;
    }

    int recurse1(int curr_id, std::vector<int>& debt) {
        while (curr_id < N and debt[curr_id] == 0) {
            ++curr_id;
        }
        if (curr_id == N) {
            return 0;
        }
        int min_transactions = INT_MAX;
        for (int next_id = curr_id + 1; next_id < N; ++next_id) {
            if (debt[next_id] * debt[curr_id] < 0) {
                debt[next_id] += debt[curr_id];
                min_transactions = std::min(
                                            min_transactions,
                                            1 + recurse1( curr_id + 1, debt )
                                        );
                debt[next_id] -= debt[curr_id];
            }
        }

        return min_transactions;
    }

    int solution1(const std::vector<std::vector<int>>& transactions) {
        /* Time-Complexity:     O(N!)
         * Space-Complexity:    O(N)
         */
        auto debt = build_debt_array(transactions);
        N = debt.size();
        return recurse1(0, debt);
    }

public:
    int minTransfers(vector<vector<int>>& transactions) {
        return solution1(transactions);        
    }
};
