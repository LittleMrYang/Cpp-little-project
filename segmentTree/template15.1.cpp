#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rs id<<1|1
#define ls id<<1
using namespace std;
const int N=100000+10;
struct node
{
    int left,right,sumr,suml;
}tree[N*4];
int n,m;
void build(int id,int l,int r)
{
    tree[id].left=l,tree[id].right=r;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
}
void update(int id,int x)//修改起点
{
    if(tree[id].left==tree[id].right)
    {
        tree[id].suml++;return;
    }
    if(x>tree[ls].right)update(rs,x);
    else update(ls,x);
    tree[id].suml=tree[ls].suml+tree[rs].suml;
}
void update2(int id,int x)//修改终点
{
    if(tree[id].left==tree[id].right)
    {
        tree[id].sumr++;return;
    }
    if(x>tree[ls].right)update2(rs,x);
    else update2(ls,x);
    tree[id].sumr=tree[ls].sumr+tree[rs].sumr;
}
int query(int id,int l,int r)//查询起点
{
    if(r<tree[id].left || tree[id].right<l)return 0;
    if(l<=tree[id].left&&tree[id].right<=r)return tree[id].suml;
    return query(ls,l,r)+query(rs,l,r);
}
int query2(int id,int l,int r)//查询终点
{
    if(tree[id].left>r||tree[id].right<l)return 0;
    if(tree[id].left>=l&&tree[id].right<=r)return tree[id].sumr;
    return query2(ls,l,r)+query2(rs,l,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);//建树
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(x==1)
        {
            update(1,y);update2(1,z);
        }
        if(x==2)
        {
            int s=query(1,1,z);
            int t=query2(1,1,y-1);
            printf("%d\n",s-t);//终点的sum-起点的sum
        }
    }
}
