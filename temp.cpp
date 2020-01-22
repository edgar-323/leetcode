void print(const std::vector<std::vector<int>>& grid) {
        const int N = grid.size();
        for (int i = 0; i < N; ++i) {
            cout << "[";
            for (int j = 0; j < N; ++j) {
                cout << grid[i][j] << (j < N-1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    }
        cout << "grid:" << endl; print(grid);
        cout << "left:" << endl; print(left);
        cout << "right:" << endl; print(right);
        cout << "top:" << endl; print(top);
        cout << "down: " << endl; print(down);
