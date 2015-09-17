#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-10;
const double PI = 3.1415927;

double n, R, r;

int main() {
    while (~scanf("%lf%lf%lf", &n, &R, &r)) {
        if (n == 1) {
            if (r <= R) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else if (n == 2) {
            if (2 * r <= R) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else {
            if (asin(r / (R-r)) * n + EPS <= PI) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}
