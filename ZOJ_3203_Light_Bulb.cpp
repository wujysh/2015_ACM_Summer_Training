#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int nCase;

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        double H, h, D;
        scanf("%lf%lf%lf", &H, &h, &D);
        double x = H - sqrt(D * (H-h)), L;
        if (x > h) {
            L = h;
        } else if (x < 0) {
            L = D * h / H;
        } else {
            L = D*(h-x)/(H-x) + x;
        }
        printf("%.3lf\n", L);
    }
    return 0;
}
