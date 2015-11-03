#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

string line;
map<string, string> mp;

template <typename T>
string NumberToString(T Number) {
    ostringstream ss;
    ss << Number;
    return ss.str();
}

void init() {
    mp.clear();
}

inline bool valid(char c) {
    if (c == '-' || c == ',' || c == '.' || c == '"' || c == '(' || c == ')' || c == ':' || c == ';' || c == '!' || c == '?') return false;
    if (!isalpha(c)) return false;
    return true;
}

void abbreviate(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int len = word.size();
    char a = word[0], b = word[len-1];
    string abbr = a + NumberToString(len - 2) + b;
    //cout << abbr << endl;
    if (mp.find(abbr) == mp.end()) {
        mp[abbr] = word;
    } else if (mp[abbr] != word){
        mp[abbr] = "@invalid@";
    }
}

void solve() {
    int i = 0;
    while (i < line.size()) {
        if (isalpha(line[i])) {
            if (line[i + 1] >= '0' && line[i + 1] <= '9') {
                bool flag1 = false, flag2 = false;

                char a = line[i], A = line[i];
                if (isupper(a)) {
                    a = a - 'A' + 'a';
                    flag1 = true;
                }
                i++;

                int num = 0;
                while (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                    num = num * 10 + (line[i] - '0');
                    i++;
                }

                char b = line[i], B = line[i];
                if (isupper(b)) {
                    b = b - 'A' + 'a';
                    flag2 = true;
                }
                i++;

                string abbr = a + NumberToString(num) + b;
                if (mp.find(abbr) != mp.end() && mp[abbr] != "@invalid@") {
                    if (!flag1 && !flag2) {
                        cout << mp[abbr];
                    } else if (flag1 && !flag2) {
                        string word = mp[abbr];
                        word[0] = word[0] - 'a' + 'A';
                        cout << word;
                    } else if (flag1 && flag2) {
                        string word = mp[abbr];
                        for (int i = 0; i < word.size(); i++) {
                            word[i] = word[i] - 'a' + 'A';
                        }
                        cout << word;
                    }
                } else {
                    abbr = A + NumberToString(num) + B;
                    cout << abbr;
                }
            } else {
                string word = "";
                while (i < line.size() && valid(line[i])) {
                    word += line[i];
                    i++;
                }
                if (word.size() >= 4) {
                    abbreviate(word);
                }
                cout << word;
            }
        } else {
            cout << line[i];
            i++;
        }
    }
    cout << endl;
}

int main() {
    init();
    while (getline(cin, line)) {
        solve();
    }
    return 0;
}
