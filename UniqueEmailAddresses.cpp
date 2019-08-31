/*
Every email consists of a local name and a domain name, separated by the @ sign.
For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.
Besides lowercase letters, these emails may contain '.'s or '+'s.
If you add periods ('.') between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name.  
For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)
If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)
It is possible to use both of these rules at the same time.
Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails? 
*/

class Solution {
private:
    std::string normalize(const std::string& str) {
        const size_t N = str.size();
        std::string normal;
        normal.reserve( N );
        size_t i;
        for (i = 0; i < N; ++i) {
            if (str[i] == '.') {
                continue;
            } else if (str[i] == '+' or str[i] == '@') {
                break;
            } else {
                normal += str[i];
            }
        }
        while (i < N and str[i] != '@') {
            ++i;
        }
        while (i < N) {
            normal += str[i++];
        }
        return normal;
    }

    int solution1(std::vector<std::string>& emails) {
        /* 
         * Time-Complexity:     O( L )
         * Space-Complexity:    O( L )
         * where L = SUM({ length(email) | email in emails })
         * */
        std::unordered_set<std::string> unique;
        
        for (const auto& _email : emails) {
            const auto email = normalize( _email );
            if (!unique.count( email )) {
                unique.insert( email );
            }
        }

        return unique.size();
    }
public:
    int numUniqueEmails(vector<string>& emails) {
		return solution1( emails );        
    }
};
