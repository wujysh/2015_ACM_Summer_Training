#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define L x->c[0]
#define R x->c[1]
#define KT root->c[1]->c[0]
const int maxn = 111111;

int n, m, k;

struct node {
    struct node *c[2], *fa;
    int id;
    int sz;
    bool flip;
    char name[5];
    inline bool d() {
        return fa->c[0] == this;
    }
    inline void setc(int d, node *s) {
        c[d] = s;
        s->fa = this;
    }
    inline void up() {
        sz = c[0]->sz + c[1]->sz + 1;
    }
    inline void down() {
        if(flip) {
            c[0]->flip ^= 1;
            c[1]->flip ^= 1;
            swap(c[0], c[1]);
            flip = false;
        }
    }
    inline void clear(node *null) {
        c[0] = c[1] = null;
        sz = 1;
    }
} NODE[2 * maxn], *null = &NODE[0] ;

int top;
node* ID[maxn];

struct SplayTree {
    node* root;
    void Rotate(node *x, int f) {
        node *y = x->fa;
        y->down();
        x->down();
        y->setc(!f, x->c[f]);
        x->fa = y->fa;
        if (y->fa != null)    y->fa->setc(!y->d(), x);
        x->setc(f, y);
        y->up();
    }
    void Splay(node *x, node *goal) {
        x->down();
        while (x->fa != goal) {
            x->fa->fa->down();
            x->fa->down();
            x->down();
            if (x->fa->fa == goal)
                Rotate(x, x->d());
            else {
                int f = x->fa->d();
                x->d() == f ? Rotate(x->fa, f) : Rotate(x, !f);
                Rotate(x, f);
            }
        }
        x->up();
        if (goal == null) root = x;
    }
    void RTO(int k, node *goal) {
        node *x = root;
        x->down();
        while (L->sz + 1 != k) {
            if(k < L->sz + 1) x = L;
            else {
                k -= L->sz + 1;
                x = R;
            }
            x->down();
        }
        Splay(x, goal);
    }
    void build(node* &x, int l, int r, node *fa) {
        if(l > r) return ;
        int m = (l + r) >> 1;
        x = new_node(fa, num[m]);
        build(x->c[0], l, m - 1, x);
        build(x->c[1], m + 1, r, x);
        x->up();
    }
    node *new_node(node *fa, char *s) {
        node *x = &NODE[++top];
        x->id = top;
        x->c[0] = x->c[1] = null;
        x->sz = 1;
        x->flip = false;
        strcpy(x->name, s);
        x->fa = fa;
        return x;
    }
    void ADD(char *s) {
        RTO(1, null);
        RTO(2, root);
        node *tmp = new_node(root->c[1], s);
        root->c[1]->setc(0, tmp);
        root->c[1]->up();
        root->up();
//      //  debug();
//        puts("");
//        print(root);
//        puts("");
    }
    void ROTATE(int K) {
        if(root->sz - 2 <= K) {
            RTO(1, null);
            RTO(root->sz, root);
            KT->flip ^= 1;
        } else {
            RTO(1, null);
            RTO(K + 2, root);
            KT->flip ^= 1;
        }
    }
    void print(node *x) {

        if(x != null) {
            x->down();
            print(x->c[0]);
            if(strcmp(x->name, "***") != 0) printf("%s\n", x->name);
            print(x->c[1]);
        }
    }
    void init(int n) {
        for(int i = 0; i < n; i++)  scanf("%s", num[i]);
        root = new_node(null, "***");
        root->c[1] = new_node(root, "***");
        build(KT, 0, n - 1, root->c[1]);
        root->c[1]->up();
        root->up();
        // debug();
    }
    /*
    0 5 3
    ADD(ABD)
    ADD(XXX)
    ADD(FDA)
    ROTATE
    ADD(wuyi)
     */
    void Del_root() { // delete the root
        node* t = root;
        if (t->c[1] != null) {
            root = t->c[1];
            RTO(1, null);
            root->c[0] = t->c[0];
            if (root->c[0] != null)
                root->c[0]->fa = root;
        } else
            root = root->c[0];
        root->fa = null;
        if (root != null)
            root->up();
    }
    void vist(node *x) {
        if (x != null) {
            printf("节点：%2d ： 左儿子： %2d  右儿子：  %2d  sz: %2d val: %s\n",
                   x->id, x->c[0]->id, x->c[1]->id, x->sz, x->name);
            vist(x->c[0]);
            vist(x->c[1]);
        }
    }
    void debug() {
        puts("************");
        vist(root);
        puts("\n*****************");
    }
    char num[maxn][5];
} spt;

void prepare() {
    top = 0;
    null->id = 0;
    null->c[0] = null->c[1] = null->fa = NULL;
    null->sz = 0;
    null->flip = false;
    strcpy(null->name, "***");
}

int main() {
    prepare();
    while (~scanf("%d%d%d", &n, &m, &k)) {
        spt.init(n);
        char op[20];
        for (int i = 0; i < m; i++) {
            scanf("%s", op);
            if (strcmp(op, "ROTATE") == 0) {
                spt.ROTATE(k);
            } else {
                int len = strlen(op);
                char ta[10];
                int head = 0;
                for(int i = 4; i < len - 1; i++) {
                    ta[head++] = op[i];
                }
                ta[head] = 0;
                spt.ADD(ta);
            }
        }
        spt.print(spt.root);
    }
    return 0;
}
