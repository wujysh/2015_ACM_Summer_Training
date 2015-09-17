#include <iostream>
#include <cstdio>
using namespace std;

struct Node {
    int v;
    Node *l, *r;
} *root;

int nCase, n, q, a;

void insert(Node* &rt, int a) {
    if (rt == NULL) {
        rt = new Node();
        rt->v = a;
        rt->l = rt->r = NULL;
    } else {
        if (a < rt->v) {
            insert(rt->l, a);
        } else {
            insert(rt->r, a);
        }
    }
}

void query(Node* &rt, int a) {
    if (rt->v == a) {
        printf("\n");
        return;
    } else {
        if (a < rt->v) {
            printf("E");
            query(rt->l, a);
        } else {
            printf("W");
            query(rt->r, a);
        }
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        root = NULL;

        scanf("%d", &n);
        while (n--) {
            scanf("%d", &a);
            insert(root, a);
        }

        scanf("%d", &q);
        while (q--) {
            scanf("%d", &a);
            query(root, a);
        }
    }
    return 0;
}
