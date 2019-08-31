/*
Note: This is a companion problem to the System Design problem: Design TinyURL.

TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
*/

class Solution {
private:
    const std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t ALPH_SZ = alphabet.size();
    const size_t KEY_SZ = 6;
    const std::string tiny_url = "http://tinyurl.com/";

    std::unordered_map<std::string, std::string> map;

    std::string produceKey() const {
        std::string key( KEY_SZ, 0 );
        for (size_t i = 0; i < KEY_SZ; ++i) {
            key[i] = alphabet[rand() % ALPH_SZ];
        }
        return key;
    }
public:


    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        // ASSUMES `longUrl` IS A NEW STRING WE'VE NEVER SEEN BEFORE
        auto key = produceKey();
        while ( map.count( key ) ) {
            key = produceKey();
        }
        map.insert( std::make_pair( key, longUrl ) );
        return tiny_url + key;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        auto& key = shortUrl.replace(0, tiny_url.size(), "");
        return map[key];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
