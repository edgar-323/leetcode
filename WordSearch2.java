class Trie {
    private int ALPH_SZ = 26;
    private String word;
    private Trie[] child;

    private int index(char c) {
        return c - 'a';
    }

    private void insert(String _word, int pos) {
        if (pos >= _word.length()) {
            word = _word;
            return;
        }
        int i = index(_word.charAt(pos));
        if (child[i] == null) {
            child[i] = new Trie();
        }
        child[i].insert(_word, pos+1);
    }

    public Trie() {
        word = null;
        child = new Trie[ALPH_SZ];
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = null;
        }
    }

    public void insert(String _word) {
        insert(_word, 0);
    }

    public boolean isWord() {
        return word != null;
    }

    public String getWord() {
       return word;
    }

    private boolean isLower(char c) {
        return 'a' <= c && c <= 'z';
    }
    
    public boolean hasChild(char c) {
       return isLower(c) && child[index(c)] != null;
    }
    
    public Trie getChild(char c) {
       return child[index(c)];
    } 
}

class Solution {
    private int M,N;
    private Trie root;
    private Set<String> results;
    private char[][] board;

    private boolean valid(int i, int j) {
        return i >= 0 && i < M && j >= 0 && j < N;
    }

    private void explore1(int i , int j, Trie trie) {
        if (trie.isWord()) { 
            results.add(trie.getWord());
        } 

        char c = board[i][j];
        board[i][j] = '*';

        // top
        if (valid(i-1, j)) {
            char top = board[i-1][j];
            if (trie.hasChild(top)) {
                explore1(i-1, j, trie.getChild(top));
            }
        }
        // bottom 
        if (valid(i+1, j)) {
            char bot = board[i+1][j];
            if (trie.hasChild(bot)) {
                explore1(i+1, j, trie.getChild(bot));
            }
        }
        // left 
        if (valid(i, j-1)) {
            char left = board[i][j-1];
            if (trie.hasChild(left)) {
                explore1(i, j-1, trie.getChild(left));
            }
        }
        // right  
        if (valid(i, j+1)) {
            char right = board[i][j+1];
            if (trie.hasChild(right)) {
                explore1(i, j+1, trie.getChild(right));
            }
        }

        board[i][j] = c;
    }

    private List<String> solution1(char[][] board, String[] words) {
        if (board == null || board.length == 0) {
            return new ArrayList<String>();
        }
        M = board.length;
        N = board[0].length;
        this.board = board;
        root = new Trie();
        results = new HashSet<String>();
        
        for (String word : words) {
            root.insert(word);
        }
        if (root.isWord()) {
            results.add("");
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                char c = board[i][j];
                if (root.hasChild(c)) {
                    explore1(i, j, root.getChild(c));
                }
            }
        }
        return new ArrayList<String>(results);
    }

    public List<String> findWords(char[][] board, String[] words) {
        return solution1(board, words);
    }
}

