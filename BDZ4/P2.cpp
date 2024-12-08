#include <iostream>
#include <vector>

struct node {
  int number;
  int key;
  int left;
  int right;
  char color;
  int blackheight;
};

std::istream &operator>>(std::istream &sin, node &node) {
  sin >> node.number;
  sin >> node.key;
  std::string s;
  sin >> s;
  if (s == "null") {
    node.left = 0;
  } else {
    node.left = std::stoi(s);
  }
  sin >> s;
  if (s == "null") {
    node.right = 0;
  } else {
    node.right = std::stoi(s);
  }
  sin >> node.color;
  node.blackheight = 0;

  return sin;
}

std::vector<node> tree;

bool check_red_black(int num, bool must_be_black = 1) {
  if (num == 0) {
    return true;
  }
  bool f = check_red_black(tree[num].left, tree[num].color == 'R') &&
           check_red_black(tree[num].right, tree[num].color == 'R');
  f &= !must_be_black || (tree[num].color == 'B');
  int lefth =
      tree[tree[num].left].blackheight + static_cast<int>(tree[tree[num].left].color == 'B');
  int righth =
      tree[tree[num].right].blackheight + static_cast<int>(tree[tree[num].right].color == 'B');
  f &= lefth == righth;
  tree[num].blackheight = lefth;
  std:: cout<<tree[num].key <<' '<<lefth<<' '<<righth<<'\n';
  f &= tree[num].color == 'B' || tree[num].color == 'R';
  f &= (tree[num].right == 0 || tree[num].key < tree[tree[num].right].key) &&
       (tree[num].left == 0 || tree[num].key > tree[tree[num].left].key);
  return f;
}

int main() {
  int n, root;
  std::cin >> n >> root;
  tree.resize(n + 1);
  tree[0].blackheight = -1;
  tree[0].color = 'B';
  for (size_t i = 1; i <= n; ++i) {
    std::cin >> tree[i];
  }
  bool f = check_red_black(root);
  if (f) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}