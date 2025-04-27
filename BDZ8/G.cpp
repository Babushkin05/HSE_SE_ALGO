#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

struct TrieNode {
  std::map<char, TrieNode*> children;
  TrieNode* suffix_link;
  TrieNode* output_link;
  std::vector<int> pattern_indices;
};

void BuildTrie(TrieNode* root, std::vector<std::string>& patterns) {
  for (size_t pattern_idx = 0; pattern_idx < patterns.size(); ++pattern_idx) {
    TrieNode* current_node = root;
    for (char character : patterns[pattern_idx]) {
      if (current_node->children.count(character)) {
        current_node = current_node->children[character];
      } else {
        TrieNode* new_node = new TrieNode;
        current_node->children.insert({character, new_node});
        current_node = new_node;
      }
    }
    current_node->pattern_indices.push_back(pattern_idx);
  }
}

void BuildLinks(TrieNode* root) {
  root->suffix_link = root;
  std::queue<TrieNode*> node_queue;
  
  for (auto& child : root->children) {
    node_queue.push(child.second);
    child.second->suffix_link = root;
  }
  
  while (!node_queue.empty()) {
    TrieNode* current_node = node_queue.front();
    node_queue.pop();
    
    for (auto& child : current_node->children) {
      char character = child.first;
      TrieNode* temp_node = current_node->suffix_link;
      
      while (temp_node->children.count(character) == 0 && temp_node != root) {
        temp_node = temp_node->suffix_link;
      }
      
      if (temp_node->children.count(character)) {
        child.second->suffix_link = temp_node->children[character];
      } else {
        child.second->suffix_link = root;
      }
      
      node_queue.push(child.second);
    }
    
    if (!current_node->suffix_link->pattern_indices.empty()) {
      current_node->output_link = current_node->suffix_link;
    } else {
      current_node->output_link = current_node->suffix_link->output_link;
    }
  }
}

void SearchPatterns(TrieNode* root, std::string& text, auto& matches, std::vector<std::string>& patterns) {
  TrieNode* current_state = root;
  
  for (size_t position = 0; position < text.length(); ++position) {
    char character = text[position];
    
    if (current_state->children.count(character)) {
      current_state = current_state->children[character];
      TrieNode* output_node = current_state;
      
      while (output_node != nullptr) {
        for (int pattern_idx : output_node->pattern_indices) {
          matches[pattern_idx].push_back(position);
        }
        output_node = output_node->output_link;
      }
    } else {
      while (current_state != root && current_state->children.count(character) == 0) {
        current_state = current_state->suffix_link;
      }
      if (current_state->children.count(character)) {
        --position;
      }
    }
  }
}

int main() {
  std::string text;
  std::getline(std::cin, text);
  
  int pattern_count;
  std::cin >> pattern_count;
  std::cin.ignore();
  
  std::vector<std::string> patterns(pattern_count);
  for (int i = 0; i < pattern_count; ++i) {
    std::getline(std::cin, patterns[i]);
  }
  
  TrieNode* root = new TrieNode;
  BuildTrie(root, patterns);
  BuildLinks(root);
  
  std::vector<std::vector<int>> matches(pattern_count);
  SearchPatterns(root, text, matches, patterns);
  
  for (int i = 0; i < pattern_count; ++i) {
    std::cout << matches[i].size() << ' ';
    for (int match_position : matches[i]) {
      std::cout << match_position - patterns[i].size() + 2 << ' ';
    }
    std::cout << "\n";
  }
}