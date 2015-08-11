#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 55;
string line;
double p;

int main() {
    getline(cin, line);
    cin >> p;

    double cntNoIdea = 0, cntNasty = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '?') {
            cntNoIdea++;
        } else if (line[i] == '1') {
            cntNasty++;
        }
    }

    cntNasty += cntNoIdea * p;
    cout << fixed << setprecision(5) << cntNasty / line.size() << endl;

    return 0;
}
