#include<bits/stdc++.h>
using namespace std;

int num[500005];

int tr[500005];

int n,m;

int lowbit(int num)
{
	return num&(-num);
}

void add(int i,int num)
{
	int t=i;
	while(t<=n)
	{
		tr[t]+=num;
		t+=lowbit(t);
	}
	return;
}

int get_sum(int r)
{
	if(r==0)
		return 0;
	return tr[r]+get_sum(r-lowbit(r));
}

int get_num(int l,int r)
{
	return get_sum(r)-get_sum(l-1);
}

int main()
{
	memset(tr,0,sizeof(tr));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]); 
		
		add(i,num[i]);
	}
	
	int u,p,q;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&u);
		scanf("%d",&p);
		scanf("%d",&q);
		
		if(u==1)
		{
			add(p,q);
		}
		else
		{
			printf("%d\n",get_num(p,q));
		}
	}
	return 0;
}

