#include <iostream>
#define int long long
using namespace std;
int n,q,c[1000001];
void upd(int i,const int x) {
	for(;i<=n;i+=i&-i) c[i]+=x;
}
int query(int i) {
	int ret=0;
	for(;i;i-=i&-i) ret+=c[i];
	return ret;
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false),
	cout.tie(nullptr);
	cin>>n>>q;
	for(int a,i=1;i<=n;i++) {
		cin>>a;
		upd(i,a);
		upd(i+1,-a);
	}
	for(int op,l,r,x;q--;) {
		cin>>op;
		if(op==1) {
			cin>>l>>r>>x;
			upd(l,x);
			upd(r+1,-x);
		} else {
			cin>>x;
			cout<<query(x)<<'\n';
		}
	}
	return 0;
}
