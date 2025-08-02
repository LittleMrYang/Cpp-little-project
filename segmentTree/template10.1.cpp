#include<bits/stdc++.h>
#define N 2000010
using namespace std;
struct node{
	int l,r,w,f;
}tree[N*2+1];
int x,y,z,i,a[N],n,m;
void build(int k,int t,int w)
{ int mid;
	if (t>w) return;
	if (t==w)
	  {
	  	tree[k].l=t;tree[k].r=w;
	  	tree[k].w=a[t];
	  	return;
	  }
	mid=(t+w)/2;
	build(k*2,t,mid);
	build(k*2+1,mid+1,w);
	tree[k].l=t;tree[k].r=w;
	tree[k].w=min(tree[k*2].w,tree[k*2+1].w);
}
int ask(int k,int t,int w)
{ int mid;
if (t>w) return 0;
	if (x<=t&&w<=y)
	  {
	  	return tree[k].w;
	  }
	mid=(t+w)/2;
	int sum=INT_MAX;
	if (x<=mid)sum=min(sum,ask(k*2,t,mid));
	if (y>mid)sum=min(sum,ask(k*2+1,mid+1,w));
	return sum;
}
int read(int &x)
{
	char c=getchar();int f=1;
	x=0;
	while (c<'0'||c>'9')
	  {
	  if (c=='-') f=-1;
	  c=getchar();
      }
	while (c>='0'&&c<='9')
      {
      	x=x*10+(int)c-48;
      	c=getchar();
	  }
	return x*f;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(n);m=read(m);
	memset(a,INT_MAX,sizeof(a));
	for (int i=1;i<=n;i++) a[i]=read(a[i]);
	build(1,1,n);
	for (int i=1;i<=n;i++)
	  { int c;
	  	x=i-m;y=i-1;
	  	if (x<=0) x=1;
	  	if (x>y) 
	  	  {
	  	  	printf("0\n");
	  	  	continue;
			}
	  	printf("%d\n",ask(1,1,n));
	  }
	
}
