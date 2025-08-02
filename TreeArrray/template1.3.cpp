#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+10;//数据范围通常为5e5，+10防止越界

ll n,m;
ll tree[N];//树状数组（下标从1开始）

inline ll lowbit(ll x)//计算最低位的1，如lowbit(6)=2（二进制110的最低位10）
{
    return x&-x;
}

void update(ll x,ll val)//单点更新：在位置x上增加val，并向上更新父节点
{
    while(x<=n)//从叶子节点向上更新到根
	{
        tree[x]+=val; //当前节点增加val
        x+=lowbit(x);//移动到父节点（当前下标+最低位）
    }
}

ll query(ll x)//查询前缀和：计算前x项的和
{
    ll sum=0;
    while(x>0)//从当前节点向左上回溯
	{
        sum+=tree[x]; //累加路径上的节点值
        x-=lowbit(x);//移动到前一个区间（去掉最低位的1）
    }
    return sum;
}

int main()
{
    cin>>n>>m;//初始化树状数组（等效于单点插入）
    for(int i=1;i<=n;i++)
	{
        ll num;
        cin>>num;
        update(i,num);//将初始值逐个单点更新
    }
    while(m--)//处理m次操作
	{
        ll op,x,y;
        cin>>op>>x>>y;
        if(op==1)update(x,y);//单点修改：在x位置加y
        else cout<<query(y)-query(x-1)<<endl;//区间查询：[x,y]的和 = 前y项和 - 前x-1项和
    }
    return 0;
}

