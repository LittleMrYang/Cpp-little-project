#include <bits/stdc++.h>
using namespace std; 

const int N = 5e5 + 5; 

int a, c[N], n, m; 

int lowbit (int x) {
	return x & -x; 
}

void update (int i, int x) {
	for (; i <= n; i += lowbit(i)) {
		c[i] += x; 
	}
}

int sum (int x) {
	int ans = 0; 
	while (x != 0) {
		ans += c[x]; 
		x -= lowbit(x); 
	}
	return ans; 
}

int main () {
	
	scanf("%d%d", &n, &m); 
	int last = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a); 
		update(i, a - last); 
		last = a; 
	}
	int op, x, y, k; 
	for (int i = 0; i < m; i++) {
		scanf("%d", &op); 
		if (op == 1) {
            scanf("%d%d%d", &x, &y, &k);
            update(y + 1, -k); // 差分思想
            update(x, k);
        } else {
            scanf("%d", &x);
            printf("%d\n", sum(x)); // 求差分数组 [1,x] 的和
        }
	}
	return 0; 
}
