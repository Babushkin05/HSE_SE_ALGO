#include <iostream>
#include <random>
#include <set>
#include <stack>
#include <utility>
#include <vector>

struct cell {
  int x, y;
  bool operator<(const cell &other) const {
    return (x < other.x) || (x == other.x && y < other.y);
  }
};

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

bool is_valid(int x, int y, int n, int m) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

bool dfs_reachable(const std::vector<std::vector<int>> &maze, int n, int m,
                   cell entry, cell exit) {
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  std::stack<cell> stack;
  stack.push(entry);
  visited[entry.x][entry.y] = true;

  while (!stack.empty()) {
    cell cur = stack.top();
    stack.pop();

    if (cur.x == exit.x && cur.y == exit.y)
      return true;

    for (int d = 0; d < 4; ++d) {
      int nx = cur.x + dx[d];
      int ny = cur.y + dy[d];
      if (is_valid(nx, ny, n, m) && maze[nx][ny] == 1 && !visited[nx][ny]) {
        visited[nx][ny] = true;
        stack.push({nx, ny});
      }
    }
  }

  return false;
}

void generate_maze(std::vector<std::vector<int>> &maze, int n, int m,
                   cell entry, cell exit) {
  std::random_device rd;
  std::mt19937_64 rng(rd());

  do {
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::set<std::pair<cell, cell>> wall_list;
    maze.assign(n, std::vector<int>(m, 0));

    visited[entry.x][entry.y] = true;
    maze[entry.x][entry.y] = 1;

    for (int d = 0; d < 4; ++d) {
      int nx = entry.x + dx[d];
      int ny = entry.y + dy[d];
      if (is_valid(nx, ny, n, m))
        wall_list.insert({entry, {nx, ny}});
    }

    while (!visited[exit.x][exit.y] && !wall_list.empty()) {
      std::uniform_int_distribution<size_t> dist(0, wall_list.size() - 1);
      size_t idx = dist(rng);
      auto it = wall_list.begin();
      std::advance(it, idx);
      auto wall = *it;
      wall_list.erase(it);

      cell from = wall.first;
      cell to = wall.second;
      if (!is_valid(to.x, to.y, n, m) || visited[to.x][to.y])
        continue;

      int count = 0;
      for (int d = 0; d < 4; ++d) {
        int nx = to.x + dx[d];
        int ny = to.y + dy[d];
        if (is_valid(nx, ny, n, m) && visited[nx][ny])
          ++count;
      }
      if (count != 1)
        continue;

      int exit_neighbors = 0;
      for (int d = 0; d < 4; ++d) {
        int nx = exit.x + dx[d];
        int ny = exit.y + dy[d];
        if (is_valid(nx, ny, n, m)) {
          if (visited[nx][ny] || (nx == to.x && ny == to.y))
            ++exit_neighbors;
        }
      }
      if (exit_neighbors > 1)
        continue;

      visited[to.x][to.y] = true;
      maze[to.x][to.y] = 1;

      for (int d = 0; d < 4; ++d) {
        int nx = to.x + dx[d];
        int ny = to.y + dy[d];
        if (is_valid(nx, ny, n, m) && !visited[nx][ny])
          wall_list.insert({to, {nx, ny}});
      }
    }

  } while (!dfs_reachable(maze, n, m, entry, exit));
}

int main() {
  int n, m;
  std::cout << "n m: ";
  std::cin >> n >> m;
  cell entry = {0, 0};
  cell exit = {n - 1, m - 1};

  std::vector<std::vector<int>> maze;
  generate_maze(maze, n, m, entry, exit);

  // красивый вывод
  std::cout << "█";
  for (int j = 0; j < m; ++j) {
    std::cout << "█";
  }
  std::cout << "█\n";

  for (int i = 0; i < n; ++i) {
    if (entry.x == i && entry.y == 0)
      std::cout << " ";
    else
      std::cout << "█";

    for (int j = 0; j < m; ++j) {
      if (maze[i][j])
        std::cout << " ";
      else
        std::cout << "█";
    }

    if (exit.x == i && exit.y == m - 1)
      std::cout << " ";
    else
      std::cout << "█";
    std::cout << '\n';
  }

  for (int j = 0; j < m + 1; ++j) {
    std::cout << "█";
  }
  std::cout << "█\n";

  return 0;
}
