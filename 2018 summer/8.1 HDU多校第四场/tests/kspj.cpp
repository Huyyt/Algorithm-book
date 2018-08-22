#include <bits/stdc++.h>
using namespace std;

#define NO() {\
    cout << "NO" << endl;\
    goto END;\
}

#define OK() {\
    cout << "AC" << endl;\
}

bool isOp (char c) {
    return c == '+' || c == '*';
}

bool check (string a) {
    int aL = a.length();
    for (int i = 1; i < aL; ++i) {
        if (a[i] == '?' && a[i - 1] == '0' && (i == 1 || isOp(a[i - 2]))) a[i] = '+';
    }
    for (int i = 0; i < aL; ++i) {
        if (a[i] == '?') a[i] = '1';
    }
    int succ = 1;
    if (isOp(a[0]) || isOp(a[aL - 1])) succ = 0;
    for (int i = 0; i + 1 < aL; ++i) {
        if (isOp(a[i]) && isOp(a[i + 1])) succ = 0;
        if ((i == 0 || isOp(a[i - 1])) && a[i] == '0' && !isOp(a[i + 1])) succ = 0;
    }
    return succ;
}

int main (int argc, char* argv[]) {
    ifstream fin(argv[1]);
    int T; fin >> T;
    while (T--) {
        string a, b;
        fin >> a; cin >> b;
        int aL = a.length(), bL = b.length();
        if (b == "IMPOSSIBLE") {
            if (check(a)) NO();
            OK();
        } else {
            if (aL != bL) NO();
            for (int i = 0; i < aL; ++i) {
                if (!(isdigit(b[i]) || isOp(b[i]))) NO();
                if (a[i] != '?' && a[i] != b[i]) NO();
            }
            if (isOp(b[0]) || isOp(b[aL - 1])) NO();
            for (int i = 0; i + 1 < aL; ++i) {
                if (isOp(b[i]) && isOp(b[i + 1])) NO();
                if ((i == 0 || isOp(b[i - 1])) && b[i] == '0' && !isOp(b[i + 1])) NO();
            }
            OK();
        }
    }
END:
    fin.close();
    return 0;
}
