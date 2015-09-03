#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string s;

int cnt[2016][13][32], Max, ansY, ansM, ansD;

int main() {
    getline(cin, s);

    Max = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            int d = s[i] - '0';
            if (s[i+1] >= '0' && s[i+1] <= '9') {
                d = d * 10 + (s[i+1] - '0');
                if (d == 0 || d > 31) continue;

                if (s[i+2] == '-') {
                    if (s[i+3] >= '0' && s[i+3] <= '9') {
                        int m = s[i+3] - '0';
                        if (s[i+4] >= '0' && s[i+4] <= '9') {
                            m = m * 10 + (s[i+4] - '0');
                            if (m == 0 || m > 12) continue;

                            if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
                                if (d > 31) continue;
                            } else if (m == 2) {
                                if (d > 28) continue;
                            } else {
                                if (d > 30) continue;
                            }

                            if (s[i+5] == '-') {
                                if (s[i+6] == '2') {
                                    if (s[i+7] == '0') {
                                        if (s[i+8] == '1') {
                                            if (s[i+9] >= '3' && s[i+9] <= '5') {
                                                int y = 2010 + (s[i+9] - '0');

                                                cnt[y][m][d]++;
                                                if (cnt[y][m][d] > Max) {
                                                    Max = cnt[y][m][d];
                                                    ansY = y;
                                                    ansM = m;
                                                    ansD = d;
                                                }
                                                //cout << d << " " << m << " " << y << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (ansD >= 10) {
        printf("%d", ansD);
    } else {
        printf("0%d", ansD);
    }

    printf("-");

    if (ansM >= 10) {
        printf("%d", ansM);
    } else {
        printf("0%d", ansM);
    }

    printf("-");

    printf("%d\n", ansY);

    return 0;
}
