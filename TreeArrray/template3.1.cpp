#include <bits/stdc++.h>
using namespace std;
int n,a[10000001],c[10000001],m;
int lowbit(int i){
    return i&(-i);
}
int getSum(int x){//求和
    int sum=0;
    for(int i=x;i>0;i-=lowbit(i))//树状数组的前缀和
        sum+=c[i];
    return sum;
}
void modify(int x,int delta){//改变数据
    for(int i=x;i<=n;i+=lowbit(i)) //因为前缀和是一个一个推的，所以一个儿子节点改变了，所有父亲节点也要改变 
        c[i]+=delta;
}
int main(){
    cin>>n;
    cin>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>c;
        if(c==1){
            cin>>a;
            cout<<getSum(a)<<endl;//树状数组前缀和得到单点查询
        }
        else {
            cin>>a>>b;
            modify(a,1);//差分，因为a~b加1就相当于左边的加1右边的减1（差分博客里详细讲解了差分用法）
            modify(b+1,-1);
        }
    }
    return 0;
}
