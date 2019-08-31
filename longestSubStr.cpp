#include <iostream>
#include <unordered_map>

bool contains(std::unordered_map<char, int>& some_map, char some_char) {
    auto position = some_map.find(some_char);
    return position != some_map.end();
}

int lengthOfLongestSubstring(std::string str) {
  std::unordered_map<char, int> helper_map;
  int max_len = 0;
  int current_len = 0;
  int start = 0;
  for (int index = 0; index < str.size(); ++index) {
      char current_char = str[index];
      if (contains(helper_map, current_char)) {
          auto position = helper_map[current_char];
          start = std::max(start, position);
          current_len = index - start;
          helper_map.erase(current_char);
      } else {
          ++current_len;
      }
      std::pair<char, int> current_pair(current_char, index);
      helper_map.insert(current_pair);
      max_len = std::max(max_len, current_len);
  }

  return max_len;
}
