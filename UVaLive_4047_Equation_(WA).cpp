#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <stack>
using namespace std;

struct Number {
    int fz, fm;
    Number() {}
    Number(int _fz, int _fm) : fz(_fz), fm(_fm) {}
    friend Number operator + (const Number &a, const Number &b) {
        return Number(a.fz * b.fm + b.fz * a.fm, a.fm * b.fm);
    }
    friend Number operator - (const Number &a, const Number &b) {
        return Number(a.fz * b.fm - b.fz * a.fm, a.fm * b.fm);
    }
    friend Number operator * (const Number &a, const Number &b) {
        return Number(a.fz * b.fz, a.fm * b.fm);
    }
    friend Number operator / (const Number &a, const Number &b) {
        return Number(a.fz * b.fm, a.fm * b.fz);
    }
};

struct Result {  // ax + b, f: 0 - x, 1 - 1/x
    Number x, y;
    bool flag;
    Result() {}
    Result(Number _x, Number _y, bool _flag) : x(_x), y(_y), flag(_flag) {}
    friend Result operator + (const Result &a, const Result &b) {
        return Result(a.x + b.x, a.y + b.y, a.flag || b.flag);
    }
    friend Result operator - (const Result &a, const Result &b) {
        return Result(a.x - b.x, a.y - b.y, a.flag || b.flag);
    }
    friend Result operator * (const Result &a, const Result &b) {
        return Result(a.x*b.y + a.y*b.x, a.y * b.y, a.flag || b.flag);
    }
    friend Result operator / (const Result &a, const Result &b) {
        if (b.x.fz == 0) {
            return Result(a.x / b.y, a.y / b.y, a.flag);
        } else if (a.x.fz == 0) {
            //return Result(x.c / y.a, )
        }
    }
};

stack<Result> st;
string line;

void init() {
    while (!st.empty()) {
        st.pop();
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}

void solve() {
    stringstream ss(line);
    string str;

    while (ss >> str) {
        if (str == "X") {
            st.push(Result(Number(1, 1), Number(0, 1), 0));
        } else if (str == "+" || str == "-" || str == "*" || str == "/") {
            Result result2 = st.top();
            st.pop();
            Result result1 = st.top();
            st.pop();
//            cout << result1.x.fz << "/" << result1.x.fm << " " << result1.y.fz << "/" << result1.y.fm << " " << result1.flag << endl;
//            cout << result2.x.fz << "/" << result2.x.fm << " " << result2.y.fz << "/" << result2.y.fm << " " << result1.flag << endl;
            if (str == "+") {
                Result result = result1 + result2;
//                cout << result.x.fz << "/" << result.x.fm << " " << result.y.fz << "/" << result.y.fm << " " << result.flag << endl;
                st.push(result);
            } else if (str == "-") {
                Result result = result1 - result2;
//                cout << result.x.fz << "/" << result.x.fm << " " << result.y.fz << "/" << result.y.fm << " " << result.flag << endl;
                st.push(result);
            } else if (str == "*") {
                Result result = result1 * result2;
//                cout << result.x.fz << "/" << result.x.fm << " " << result.y.fz << "/" << result.y.fm << " " << result.flag << endl;
                st.push(result);
            } else if (str == "/") {
                Result result = result1 / result2;
//                cout << result.x.fz << "/" << result.x.fm << " " << result.y.fz << "/" << result.y.fm << " " << result.flag << endl;
                st.push(result);
            }
        } else {
            int x = atoi(str.c_str());
            st.push(Result(Number(0, 1), Number(x, 1), 0));
        }
        //cout << "---------------" << endl;
    }

    Result result = st.top();
    st.pop();

//    cout << result.x.fz << "/" << result.x.fm << " " << result.y.fz << "/" << result.y.fm << " " << result.flag << endl;

    if (result.x.fz == 0) {
        if (result.y.fz == 0) {
            cout << "MULTIPLE" << endl;
        } else {
            cout << "NONE" << endl;
        }
    } else {
        Number x = result.y * Number(-1, 1) / result.x;
        if (x.fm == 1) {
            cout << "X = " << x.fz << endl;
        } else {
            int g = gcd(abs(x.fz), abs(x.fm));
            cout << "X = " << x.fz / g << "/" << x.fm / g << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        init();
        solve();
    }
    return 0;
}
