class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        int N = endWord.length();
        Set<String> dictionary = new HashSet<String>();
        for (String s : wordList) {
            dictionary.add(s);
        }
        Set<String> seen = new HashSet<String>(); 
        int minTransforms = 1;
        Queue<String> Q = new LinkedList<String>();
        Q.add(beginWord);

        while (!Q.isEmpty()) {
            for (int size = Q.size(); size > 0; --size) {
                String curr = Q.poll();
                if (curr.equals(endWord)) {
                    return minTransforms;
                }
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < 26; ++j) {
                        char a = 'a';
                        char c = (char)(a + j); 
                        String s = curr.substring(0, i) + String.valueOf(c) + curr.substring(i+1);
                        if (!seen.contains(s) && dictionary.contains(s)) {
                            Q.add(s);
                            seen.add(s);
                        }
                    }
                }
            }
            ++minTransforms;
        }
        
        return 0;

    }
}

