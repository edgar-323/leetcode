/*
Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.
In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level. For more information, see: Absolute path vs relative path in Linux/Unix
Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names. The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

Example 1:
Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:
Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:
Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:
Input: "/a/./b/../../c/"
Output: "/c"

Example 5:
Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:
Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
*/
class Solution {
private:
    std::string get_next_directory(const std::string& path, int& i) {
        const int N = path.size();
        while (i < N and path[i] == '/') {
            ++i;
        }
        auto dir = std::string("");
        while (i < N and path[i] != '/') {
            dir += std::string(1, path[i++]);
        }
        return dir;
    }

    std::string solution1(const std::string& path) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */

        auto deque = std::deque<std::string>();
        const int N = path.size();
        int i = 0;
        while (i < N) {
            const auto dir = get_next_directory(path, i);
            if (dir.empty() or dir == ".") {
                continue;
            } 
            if (dir == "..") {
                if (not deque.empty()) {
                    deque.pop_back();
                }
            } else {
                deque.push_back(dir);
            }
        }

        auto canonical_path = std::string("");

        while (not deque.empty()) {
            canonical_path += "/" + deque.front();
            deque.pop_front();
        }

        return canonical_path.empty() ? "/" : canonical_path;
    }
public:
    string simplifyPath(string path) {
        return solution1(path);       
    }
};
