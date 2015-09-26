#include <bits/stdc++.h>
using namespace std;

double k;
const double eps = 1e-10;
double x[1100];

void init() {
    double l = 0, r = 0.5, m;
    x[0] = 0.0;
    for(int i = 1; i <= 26; i++) {
        m = (l + r) / 2;
        x[i] = m;
        l = m;
    }
    //printf("%.10lf\n",x[26]);
}

int main() {
    int T;
    init();
    scanf("%d", &T);
    while(T--) {
        scanf("%lf", &k);
        if(fabs(k - 0.5) < eps) {
            puts("1000");
            continue;
        }
        int t = lower_bound(x, x + 27, k) - x;
        //cout << t << endl;
        //printf("%.10lf",x[t]);

        if(fabs(k - x[t]) < eps) puts("-1");
        else {
            printf("%d\n", 4 * t);
        }
    }
    return 0;
}
