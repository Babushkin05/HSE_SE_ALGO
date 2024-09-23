#include <iostream>
#include <stack>
#include <string>

int main() {
  std::string s;
  std::getline(std::cin, s);
  std::stack<int> numbers;
  std::stack<std::string> str;
  int curn = 0;
  std::string curs = "";
  for (size_t i = 0; i < s.size(); ++i) {

    if (isdigit(s[i])) {
      curn = s[i] - '0';
      numbers.push(curn);

    } else if (s[i] == '[') {
      str.push(curs);
      curn = 0;
      curs.clear();

    } else if (s[i] == ']') {
      std::string temp = curs;
      curs = str.top();
      str.pop();
      int repeat_count = numbers.top();
      numbers.pop();
      for (int j = 0; j < repeat_count; ++j)
        curs += temp;

    } else {
      curs += s[i];
    }
  }

  std::cout << curs << std::endl;
}