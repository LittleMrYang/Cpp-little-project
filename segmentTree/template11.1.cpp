#include<bits/stdc++.h>
using namespace std;
int a[200001], tree[800001];
void pushup(int rt)
{
	tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}
void build(int rt, int l, int r)//建树
{
	if (l == r)
	{
		tree[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
void modify(int rt, int l, int r, int x, int y)//单点修改
{
	if (l == r)
	{
		if (tree[rt] < y) tree[rt] = y;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify(rt << 1, l, mid, x, y);
	else modify(rt << 1 | 1, mid + 1, r, x, y);//找询问的点在哪个节点上
	pushup(rt);
}
int query(int rt, int l, int r, int x, int y)//区间询问
{
	if (x <= l && r <= y) return tree[rt];
	int mid = (l + r) >> 1, ans = -1e9;
	if (x <= mid) ans = max(ans, query(rt << 1, l, mid, x, y));//询问的一部分在左儿子的管辖范围内
	if (y > mid) ans = max(ans, query(rt << 1 | 1, mid + 1, r, x, y));//一部分在右儿子范围内
	return ans;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		char ope[100];
		int x, y;
		scanf("%s%d%d", ope, &x, &y);
		if (ope[0] == 'Q') printf("%d\n", query(1, 1, n, x, y));
		else modify(1, 1, n, x, y);
	}
 } 


