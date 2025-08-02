#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=1e5+10;
struct SGT{
  int l,r,sum,mul,add;
};
Tree tr[N << 2];

int n , Q , opt , p , x , y , k , a[N];
inline void pushup(int u){
  tr[u].sum=(tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}

inline void pushdown(int u){
  tr[u << 1].sum = (tr[u].mul * tr[u << 1].sum + (tr[u << 1].r - tr[u << 1].l + 1)*tr[u].add%p)%p;
  tr[u << 1 | 1].sum=(tr[u].mul * tr[u << 1 | 1].sum + (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1)*tr[u].add%p)%p;
  tr[u << 1].mul = (tr[u].mul * tr[u << 1].mul) % p;
  tr[u << 1 | 1].mul = (tr[u].mul * tr[u << 1 | 1].mul) % p;
  tr[u << 1].add=(tr[u].add + tr[u].mul * tr[u << 1].add) % p;
  tr[u << 1 | 1].add = (tr[u].add + tr[u].mul * tr[u << 1 | 1].add) % p;
  tr[u].add=0;tr[u].mul = 1;
}

inline void build(int u,int l,int r){
  tr[u].l=l;tr[u].r=r;tr[u].mul=1;
  if(l==r){
    tr[u].sum=a[l]%p;
    return;
  }
  int mid = ((l + r) >> 1);
  build(u << 1 , l , mid);
  build(u << 1 | 1 , mid + 1 , r);
  pushup(u);
}

inline void muls(int u,int L,int R,int d){//乘法操作。
  int l=tr[u].l , r = tr[u].r , mid = ((l + r) >> 1);
  if(l >= L && r <= R){
    tr[u].add = tr[u].add * d % p;
    tr[u].mul = tr[u].mul * d % p;
    tr[u].sum = tr[u].sum * d % p;//修改方式都 * d，add 和 sum 是因为结合律。（
    return;
  }
  pushdown(u);
  if(L <= mid) muls (u << 1 , L , R , d);
  if(mid < R) muls (u << 1 | 1 , L , R , d);
  pushup(u);
}

inline void adds(int u , int L , int R , int d){
  int l = tr[u].l , r = tr[u].r , mid = ((l + r) >> 1);
  if(l >= L && r <= R){
    tr[u].add = (tr[u].add + d) % p;
    tr[u].sum = (tr[u].sum + (tr[u].r - tr[u].l + 1) * k) % p;
    return;
  }
  pushdown(u);
  if(L <= mid) adds(u << 1 , L , R , d);
  if(mid < R) adds(u << 1 | 1, L , R , d);
  pushup(u);
}

inline int query(int u , int L , int R){
  int l = tr[u].l , r = tr[u].r , mid = ((l + r) >> 1);
  if(l >= L && r <= R) return tr[u].sum;
  pushdown(u);
  int val = 0;
  if(L <= mid) val = (val + query ( u << 1 , L , R) % p ) % p;
  if(mid < R) val = (val + query ( u << 1 | 1, L , R) % p ) % p;
  return val;
}

signed main(){
  n=read();Q=read();p=read();
  rep(i,1,n) a[i]=read();
  build(1,1,n);
  
  while(Q--){
    opt=read();x=read();y=read();
    if(opt == 1){
      k = read();
      muls (1 , x , y , k);
    }
    else if(opt == 2){
      k = read();
      adds (1 , x , y , k);
    }
    else pr("%lld\n" , query (1 , x , y));
  }
  return 0;
}
