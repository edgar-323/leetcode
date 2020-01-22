/*
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
             But it is larger in lexical order.
*/

class Solution {
private:
    typedef std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> PQ;

    const std::string start_node = "JFK";

    void DFS(const std::string& node, std::unordered_map<std::string, PQ>& adj_list, std::vector<std::string>& itinerary) {
        while (not adj_list[node].empty()) {
            const auto next = adj_list[node].top(); adj_list[node].pop();
            DFS(next, adj_list, itinerary);
        }

        itinerary.push_back(node);
    }

    std::vector<std::string> solution1(const std::vector<std::vector<std::string>>& tickets) {
        
        auto adj_list = std::unordered_map<std::string, PQ>(); 
        for (const auto& ticket : tickets) {
            adj_list[ticket[0]].push(ticket[1]);
        }
        auto itinerary = std::vector<std::string>();

        DFS(start_node, adj_list, itinerary);
        std::reverse(itinerary.begin(), itinerary.end());

        return itinerary;
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        return solution1(tickets);         
    }
};
