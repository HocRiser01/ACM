#include<cstdio>
#include<vector>
#include<algorithm>
#define rep(i,l,r) for (int i=(l); i<=(r); i++)
typedef long long ll;
using namespace std;

vector<ll>ls;
ll T,e,n,c,d,y,p,r,w,mx;
ll Rand(ll l,ll r){ return (((ll)rand()<<31)+rand())%(r-l+1)+l; }
ll gcd(ll a,ll b){ return (b) ? gcd(b,a%b) : a; }

ll ksc(ll &a,ll b,ll mod){
	ll res=0;
	for (; b; a=(a<<1)%mod,b>>=1)
		if (b & 1) res=(res+a)%mod;
	return res;
}

ll ksm(ll a,ll b,ll mod){
	ll res=1;
	for (; b; a=ksc(a,a,mod),b>>=1)
		if (b & 1) res=ksc(res,a,mod);
	return res;
}

ll find(ll n,int c){
	ll i=1,k=2,x=Rand(0,n-1),y=x,d;
	while (1){
		i++; x=(ksc(x,x,n)+c)%n; d=gcd(abs(y-x),n);
		if (d>1 && d<n) return d;
		if (y==x) return -1;
		if (i==k) y=x,k<<=1;
	}
}

ll Rho(ll n,int c){ ll p=-1; while (p==-1) p=find(n,c--); return p; }

bool chk(ll a,ll n){
	ll m=n-1,x,y; int k=0;
	while (!(m&1)) m>>=1,k++;
	x=ksm(a,m,n);
	rep(i,1,k){
		y=ksm(x,2,n);
		if (y==1 && x!=1 && x!=n-1) return 1;
		x=y;
	}
	return y!=1;
}

bool Miller(ll n){
	if (n==2) return 1;
	if (!(n&1)) return 0;
	rep(i,1,3) if (chk(Rand(1,n-1),n)) return 0;
	return 1;
}

void Fac(ll x,int c){
	if (x==1) return;
	if (Miller(x)) { ls.push_back(x); return; }
	ll p=Rho(x,c); Fac(p,c);
	while (x%p==0) x/=p;
	Fac(x,c);
}

int main(){
	freopen("pollard.in","r",stdin);
	freopen("pollard.out","w",stdout);
	for (scanf("%lld",&T); T--; ){
		scanf("%lld",&n); ls.clear();
		if (Miller(n)) { puts("Prime"); continue; }
		Fac(n,19260817); mx=0;
		for (vector<ll>::iterator it=ls.begin(); it!=ls.end(); it++) mx=max(mx,*it);
		printf("%lld\n",mx);
	}
	return 0;
}
