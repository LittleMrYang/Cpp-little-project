#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

typedef const int cint;
cint MAXN=1e6+5;
int n,m,c;
int a[MAXN];
struct node
{
	int l,r,minv,maxv;//minv保存区间最小值，maxv保存区间最大值
}tree[MAXN<<2];

void build(cint now,cint l,cint r)//模板
{
	tree[now].l=l;tree[now].r=r;
	if(l==r)
	{
		tree[now].minv=tree[now].maxv=a[l];
		return;
	}
	cint mid=(l+r)>>1,lson=now<<1,rson=now<<1|1;
	build(lson,l,mid);
	build(rson,mid+1,r);
    	tree[now].maxv=max(tree[lson].maxv,tree[rson].maxv);//维护最大值
	tree[now].minv=min(tree[lson].minv,tree[rson].minv);//维护最小值
}

int query_min(cint now,cint l,cint r)//查询区间最小值
{
	if(l<=tree[now].l && tree[now].r<=r)
	 return tree[now].minv;
	cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
	int ans=INT_MAX;
	if(l<=mid)	ans=min(ans,query_min(lson,l,r));
	if(mid<r)	ans=min(ans,query_min(rson,l,r));
	return ans;
}

int query_max(cint now,cint l,cint r)//查询区间最大值
{
	if(l<=tree[now].l && tree[now].r<=r)
	 return tree[now].maxv;
	cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
	int ans=INT_MIN;
	if(l<=mid)	ans=max(ans,query_max(lson,l,r));
	if(mid<r)	ans=max(ans,query_max(rson,l,r));
	return ans;
}

void input(void)
{
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)
	 cin>>a[i];
}

void solve(void)
{
	build(1,1,n);
	bool f=false;//标记是否需要输出NONE
	for(int i=1;i+m-1<=n;i++)//注意边界
	 if(query_max(1,i,i+m-1)-query_min(1,i,i+m-1)<=c)
	 {
	 	cout<<i<<endl;
		f=true;
	 }
	if(!f)
	 puts("NONE");
}

int main()
{
	ios_base::sync_with_stdio(false);//优化输入速度
	input();
	solve();
	return 0;
}
