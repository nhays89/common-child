#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


int commonChild(string s1, string s2) {
  int len = s1.size();
  unordered_map<char, vector<int>> s1_map, s2_map;      //for each char in s1 and s2 map all its indices
  vector<int> s1_max(len), s2_max(len);                 //used to store max values at each index of each string
  int index, prev_max,i_max, i, j;

  for (i = 0; i < len; i++) {
    char s1_c = s1[i];
    char s2_c = s2[i];
    s1_map[s1_c].push_back(i);
    s2_map[s2_c].push_back(i);

    if (s1_map.count(s2_c)) {
      vector<int> &s1_char_indicies = s1_map[s2_c];
      for (j = s1_char_indicies.size() - 1; j >= 0; j--) {
        index = s1_char_indicies[j];
        if (index == 0) {
          s1_max[0] = 1;
        }
        else {
          prev_max = s1_max[index - 1];
          s1_max[index] = ++prev_max;
        }
      }

      for (j = 0; j < s1_char_indicies.size(); j++) {
        index = s1_char_indicies[j];
        i_max = s1_max[index];
        index++;
        while (index <= i && s1_max[index] < i_max) {
          s1_max[index] = i_max;
          index++;
        }
      }
     
    }

    if (s2_map.count(s1_c)) {
      vector<int> &s2_char_indicies = s2_map[s1_c];
      for (j = s2_char_indicies.size() - 1; j >= 0; j--) {
        index = s2_char_indicies[j];
        if (index == 0) {
          s2_max[0] = 1;
        }
        else {
          prev_max = s2_max[index - 1];
          s2_max[index] = ++prev_max;
        }
      }

      for (j = 0; j < s2_char_indicies.size(); j++) {
        index = s2_char_indicies[j];
        i_max = s2_max[index];
        index++;
        while (index <= i && s2_max[index] < i_max) {
          s2_max[index] = i_max;
          index++;
        }
      }

    }

    if (i > 0) {
      s1_max[i] = s1_max[i] > s1_max[i - 1] ? s1_max[i] : s1_max[i - 1];
      s2_max[i] = s2_max[i] > s2_max[i - 1] ? s2_max[i] : s2_max[i - 1];
      if (s2_max[i] > s1_max[i]) {
        s1_max[i] = s2_max[i];
      }
      else {
        s2_max[i] = s1_max[i];
      }
    }
  }
  return s2_max[len - 1] > s1_max[len - 1] ? s2_max[len - 1] : s1_max[len - 1];
}

int main() {
  string s1;
  cin >> s1;
  string s2;
  cin >> s2;
  int result = commonChild(s1, s2);
  cout << result << endl;
  return 0;
}
