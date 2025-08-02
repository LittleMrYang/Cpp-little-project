#include <bits/stdc++.h>
using namespace std;
const int maxn = 5 * 1e5 + 5;
int n, m, t[maxn];
int lowbit(int x) {
    return x & -x;
}
void update(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i))
        t[i] += k;
}
int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += t[i];
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    int tmp = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        update(i, x - tmp);
        tmp = x;
    }
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            update(x, k);
            update(y + 1, -k);
        } else {
            int x;
            cin >> x;
            cout << query(x) << "\n";
        }
    }
}
