#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
  public:
    int m, n;
    int len;

    bool dfs(int x, int y, vector<vector<char>> &board, int idx, string &word,
             vector<vector<bool>> &visited)
    {
        if (idx == len)
            return true;

        for (int i = -1; i <= 1; ++i) {
            if (x + i < 0 || x + i >= m)
                continue;

            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0)
                    continue;
                if (i == j || i == -j)
                    continue;
                if (y + j < 0 || y + j >= n)
                    continue;
                if (visited[x + i][y + j])
                    continue;

                if (board[x + i][y + j] == word[idx]) {
                    visited[x + i][y + j] = true;
                    int ret               = dfs(x + i, y + j, board, idx + 1, word, visited);
                    if (ret)
                        return true;
                }
            }
        }
        visited[x][y] = false;
        return false;
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        m   = board.size();
        n   = board[0].size();
        len = word.size();

        vector<vector<bool>> visited(m, {vector<bool>(n, false)});

        char ch = word[0];

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == ch) {
                    visited[i][j] = true;
                    bool ret      = dfs(i, j, board, 1, word, visited);
                    if (ret)
                        return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    vector<vector<char>> test = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

    string word = "ABCCED";

    Solution s;

    cout << s.exist(test, word) << endl;
}
