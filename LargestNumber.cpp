/*
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:
Input: [10,2]
Output: "210"

Example 2:
Input: [3,30,34,5,9]
Output: "9534330"

Note: The result may be very large, so you need to return a string instead of an integer.
*/

class Solution {
private:
    std::string solution1(const std::vector<int>& nums) { 
        // Transform
        if (nums.empty()) {
            return ""; 
        }
        int sz = 0;
        std::vector<std::string> strs( nums.size(), "" );
        for (const int& num : nums) {
            strs[i] = std::to_string( num );
            sz += strs[i].size();
        }
        // Sort
        std::sort( strs.begin(), strs.end(),
                []
                (const std::string& a, const std::string& b) {
                    std::string ab = a+b;
                    std::string ba = b+a;
                    return ba < ab; 
                }
        );
        // Collect
        if ( strs[0] == "0" ) {
            // Most significant digit is zero, thus, the rest digits
            // must also be zero (since we sorted it accordingly)
            return "0"; 
        }
        
        std::string results = "";
        results.reserve( sz );

        for (const auto& str : strs) {
            results += str;
        }

        return results;
    }
public:
    std::string largestNumber(std::vector<int>& nums) {
        return solution1( nums ); 
    }
};
