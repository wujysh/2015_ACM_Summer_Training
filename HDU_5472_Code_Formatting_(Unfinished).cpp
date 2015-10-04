#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

int nCase, cCase, pos, last_pos;
string line;

string get_type() {
    while (line[pos] == ' ') pos++;
    last_pos = pos;

    if (line.substr(pos, 3) == "int") {
        pos += 3;
        return "int";
    } else if (line.substr(pos, 4) == "void") {
        pos += 4;
        return "void";
    } else if (line.substr(pos, 4) == "char") {
        pos += 4;
        return "char";
    } else if (line.substr(pos, 4) == "bool") {
        pos += 4;
        return "bool";
    } else if (line.substr(pos, 6) == "double") {
        pos += 6;
        return "double";
    }
    return "-1";
}

string get_name() {
    while (line[pos] == ' ') pos++;
    last_pos = pos;

    string name = "";
    while (isalnum(line[pos]) || line[pos] == '_') {
        name += line[pos];
        pos++;
    }
    return name;
}

char get_operator() {
    while (line[pos] == ' ') pos++;
    last_pos = pos;

    char ch = line[pos];
    pos++;
    return ch;
}

bool formatHeader() {
    char op = get_operator();
    if (op != '#') {
        pos = last_pos;
        return false;
    } else {
        string name = get_name();
        op = get_operator();
        string file = get_name();
        op = get_operator();
        cout << "#" << name << " <" << file << ">" << endl;
        return true;
    }
}

void formatFunction(int);

bool formatStatement(int deep) {
    string type = get_type();
    if (type == "-1") {
        if (get_operator() == '}') {
            pos = last_pos;
            return false;
        } else {
            pos = last_pos;
        }

        for (int i = 0; i < deep; i++) {
            cout << "  ";
        }

        string fun = get_name();
        if (fun == "if") {
            get_operator();  // (
            string str;
            while (pos < line.size() && line[pos] != ')') {
                str += line[pos];  // TODO:
                pos++;
            }pos++;
            cout << "if (" << str << ")" << endl;
            formatFunction(deep + 1);
        } else if (fun == "for") {
            get_operator();  // (
            string x, y, z;
            while (pos < line.size() && line[pos] != ';') {
                x += line[pos];  // TODO:
                pos++;
            }pos++;
            while (pos < line.size() && line[pos] != ';') {
                y += line[pos];  // TODO:
                pos++;
            }pos++;
            while (pos < line.size() && line[pos] != ')') {
                z += line[pos];  // TODO:
                pos++;
            }pos++;
            cout << "for (" << x << ", " << y << ", " << z << ")" << endl;
            formatFunction(deep + 1);
        } else if (fun == "printf") {
            get_operator();  // (
            get_operator();  // "
            string x, y, z;
            while (pos < line.size() && line[pos] != '"' && line[pos-1] != '\\') {
                x += line[pos];  // TODO:
                pos++;
            }pos++;cout << "!!!!" << endl;
            while (pos < line.size() && line[pos] != ')') {
                y += line[pos];  // TODO:
                pos++;
            }pos++;
            get_operator();  // ;
            cout << "printf(\"" << x << "\", " << y << ");" << endl;
        } else if (fun == "scanf") {
            get_operator();  // (
            get_operator();  // "
            string x, y, z;
            while (pos < line.size() && line[pos] != '"') {
                x += line[pos];  // TODO:
                pos++;
            }pos++;
            while (pos < line.size() && line[pos] != ')') {
                y += line[pos];  // TODO:
                pos++;
            }pos++;
            get_operator();  // ;
            cout << "scanf(\"" << x << "\", " << y << ");" << endl;
        } else {
            get_operator();  // (
            string x, y, z;
            while (pos < line.size() && line[pos] != ')') {
                x += line[pos];  // TODO:
                pos++;
            }pos++;
            get_operator();  // ;
            cout << fun << "(\"" << x << ");" << endl;
        }
        return true;
    } else {  // variable declaration
        for (int i = 0; i < deep; i++) {
            cout << "  ";
        }

        string name = get_name();
        cout << type << " " << name;
        char op = get_operator();
        if (op == ',') {
            do {
                name = get_name();
                cout << ", " << name;
                op = get_operator();
            } while (op == ',');
        }
        if (op == ';') {
            cout << ";" << endl;
            return true;
        }
    }
}

void formatFunction(int deep) {
    for (int i = 0; i < deep-1; i++) {
        cout << "  ";
    }
    cout << "{" << endl;
    char op = get_operator();
    if (op != '{') {
        pos = last_pos;

        formatStatement(deep);  // only one statement;

    } else {
        while (pos < line.size() && formatStatement(deep)) {}
        while (pos < line.size() && get_operator() != '}');
    }
    for (int i = 0; i < deep-1; i++) {
        cout << "  ";
    }
    cout << "}" << endl;
}

void solve() {
    cout << "Case #" << ++cCase << ":" << endl;

    pos = 0;
    while (pos < line.size() && formatHeader()) {}
    cout << endl;

    while (pos < line.size()) {
        // header file

        // variable declaration | function
        string type = get_type();
        if (type != "-1") {
            string name = get_name();
            cout << type << " " << name;
            char op = get_operator();
            if (op == ',') {
                do {
                    name = get_name();
                    cout << ", " << name;
                    op = get_operator();
                } while (op == ',');
            }
            if (op == ';') {
                cout << ";" << endl;
            } else if (op == '(') {
                cout << "(";
                type = get_type();
                if (type != "-1") {
                    name = get_name();
                    cout << type << " " << name;
                    op = get_operator();
                    if (op == ',') {
                        do {
                            type = get_type();
                            name = get_name();
                            cout << ", " << type << " " << name;
                            op = get_operator();
                        } while (op == ',');
                    }
                } else {
                    op = get_operator();
                }
                if (op == ')') {
                    cout << ")" << endl;
                    formatFunction(1);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    getline(cin, line);
    while (nCase--) {
        getline(cin, line);
        solve();
    }
    return 0;
}
