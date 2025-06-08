#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

const int INF = 1e9 + 7;
const int MAXN = 1e6;

#define debug(x) cerr << (#x) << ": " << (x) << endl

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> read_vector(int n) {
    vector<int> vec(n);
    for (int &x : vec) cin >> x;
    return vec;
}

void print_vector(const vector<int>& vec) {
    for (int val : vec) cout << val << ' ';
    cout << endl;
}

int count_squares(const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int cnt = 0;
    for (int i1 = 0; i1 < rows; ++i1) {
        for (int j1 = 0; j1 < cols; ++j1) {
            for (int i2 = i1 + 1; i2 < rows; ++i2) {
                for (int j2 = j1 + 1; j2 < cols; ++j2) {
                    int val = grid[i1][j1];
                    if (val == grid[i1][j2] && val == grid[i2][j1] && val == grid[i2][j2]) {
                        ++cnt;
                    }
                }
            }
        }
    }
    return cnt;
}

void print_precomputed_output(int n, int m, int c) {
    if (n == 8 && m == 10 && c == 3) {
        cout << "1 2 2 1 2 3 1 3 2 2\n"
             << "3 3 2 2 1 2 2 3 3 1\n"
             << "2 1 3 1 2 1 2 3 1 3\n"
             << "1 1 1 3 3 2 3 2 2 1\n"
             << "3 2 1 2 3 3 1 2 1 3\n"
             << "2 1 3 3 1 3 1 2 3 2\n"
             << "2 2 1 1 1 2 3 1 3 3\n"
             << "2 3 3 2 3 1 1 1 2 1\n";
        exit(0);
    }
    if (n == 9 && m == 10 && c == 3) {
        cout << "3 2 3 1 2 2 1 2 3 3\n"
             << "3 3 1 1 3 3 2 2 1 1\n"
             << "1 3 1 2 1 2 1 3 2 3\n"
             << "2 1 1 2 3 1 3 2 3 2\n"
             << "2 2 3 3 1 3 2 1 2 1\n"
             << "1 1 2 2 2 3 2 3 3 1\n"
             << "3 2 2 3 1 1 3 3 1 2\n"
             << "1 3 3 1 2 1 3 1 2 2\n"
             << "2 1 2 3 3 2 1 1 1 3\n";
        exit(0);
    }
    if (n == 10 && m == 10 && c == 3) {
        cout << "2 1 1 2 3 3 2 1 2 3\n"
             << "2 1 3 1 2 2 1 3 1 3\n"
             << "1 3 1 2 2 3 1 3 3 2\n"
             << "2 2 1 3 1 3 3 2 1 2\n"
             << "1 3 2 1 3 2 3 1 2 2\n"
             << "3 2 1 1 2 1 3 3 2 1\n"
             << "3 2 3 3 3 2 2 1 1 1\n"
             << "1 1 3 2 1 2 3 2 3 1\n"
             << "3 2 2 2 1 1 1 1 3 3\n"
             << "1 3 2 3 2 1 2 2 1 3\n";
        exit(0);
    }
    if (n == 7 && m == 10) {
        cout << "2 2 3 2 3 3 1 3 1 1\n"
             << "3 2 2 1 3 2 1 1 3 3\n"
             << "1 3 2 3 1 3 2 1 2 2\n"
             << "2 1 2 3 1 1 3 3 1 3\n"
             << "3 1 3 2 2 2 3 1 2 1\n"
             << "2 3 1 1 1 2 2 2 3 1\n"
             << "1 2 1 3 2 1 1 2 3 2\n";
        exit(0);
    }
}

int main() {
    int n, m, c;
    cin >> n >> m >> c;

    print_precomputed_output(n, m, c);

    vector<vector<int>> grid(n, vector<int>(m));

    auto randomize_grid = [&]() {
        for (auto& row : grid)
            for (int& cell : row)
                cell = 1 + rng() % c;
    };

    randomize_grid();

    while (true) {
        int cur_cnt = count_squares(grid);

        for (int step = 0; step < 10000000 && cur_cnt > 0; ++step) {
            vector<pii> positions;
            vector<int> old_values;

            for (int i = 0; i < 8; ++i) {
                int x = rng() % n;
                int y = rng() % m;
                positions.emplace_back(x, y);
                old_values.push_back(grid[x][y]);
            }

            for (int i = 0; i < 2 || (i < 8 && rng() % 5 == 0); ++i)
                grid[positions[i].first][positions[i].second] = 1 + rng() % c;

            int new_cnt = count_squares(grid);

            if (new_cnt > cur_cnt || (new_cnt == cur_cnt && rng() % 5200 == 0) || rng() % 52000 == 0) {
                for (int i = 0; i < positions.size(); ++i)
                    grid[positions[i].first][positions[i].second] = old_values[i];
            } else {
                cur_cnt = new_cnt;
            }

            if (rng() % 520000 == 0)
                randomize_grid();
        }

        if (count_squares(grid) == 0)
            break;

        randomize_grid();
    }

    for (const auto& row : grid) {
        for (int val : row) cout << val << ' ';
        cout << '\n';
    }

    return 0;
}
