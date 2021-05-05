//exCRT
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (ll i=(l); i<=(r); i++)
typedef long long ll;
using namespace std;

const int N=100010;
int n;
ll a[N],b[N];

ll gcd(ll a,ll b){ return b ? gcd(b,a%b) : a; }

ll mul(ll a,ll b,ll mod){
	ll res=0;
	for (; b; a=(a+a)%mod,b>>=1)
		if (b & 1) res=(res+a)%mod;
	return res;
}

void exgcd(ll a,ll b,ll &x,ll &y){
    if (!b){ x=1; y=0; return; }
    exgcd(b,a%b,y,x); y-=(a/b)*x;
}

ll inv(ll a,ll b){ ll x,y; exgcd(a,b,x,y); x=(x%b+b)%b; return x; }

void merge(ll c1,ll c2,ll m1,ll m2,ll &c3,ll &m3){
    ll d=gcd(m1,m2); m3=m1/d*m2;
    if (c2<c1) swap(c1,c2),swap(m1,m2);
    if ((c2-c1)%d) { puts("No solution"); exit(0); }
    c3=(mul(mul(inv(m1/d,m2/d),(c2-c1)/d,m2/d),m1,m3)+c1)%m3;
}

int main(){
    scanf("%d",&n);
    rep(i,1,n) scanf("%lld%lld",&a[i],&b[i]);
    rep(i,2,n) merge(b[i-1],b[i],a[i-1],a[i],b[i],a[i]);
    printf("%lld\n",b[n]);
    return 0;
}

//exLucas
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long ll;
using namespace std;

const int N=110;
ll mod,n,m,w[10],ans,x,y,Mod[N],sm[100010],st[N],r[N],num;

ll ksm(ll a,ll b,ll p){
    ll res;
    for (res=1; b; a=a*a%p,b>>=1)
        if (b&1) res=res*a%p;
    return res;
}

void exgcd(ll a,ll b,ll &x,ll &y){
    if (!b) x=1,y=0; else exgcd(b,a%b,y,x),y-=a/b*x;
}

ll inv(ll a,ll b){ ll x,y; exgcd(a,b,x,y); return (x%b+b)%b; }

ll F(ll n,ll pi,ll pk){
    return n ? ksm(sm[pk],n/pk,pk)*sm[n%pk]%pk*F(n/pi,pi,pk)%pk : 1;
}

ll exlucas(ll n,ll m,ll pi,ll pk){
    if (m>n) return 0;
    sm[0]=sm[1]=1; rep(i,2,pk) sm[i]=sm[i-1]*((i%pi)?i:1)%pk;
    ll a=F(n,pi,pk),b=F(m,pi,pk),c=F(n-m,pi,pk),k=0;
    for (ll i=n; i; i/=pi) k+=i/pi;
    for (ll i=m; i; i/=pi) k-=i/pi;
    for (ll i=n-m; i; i/=pi) k-=i/pi;
    return a*inv(b,pk)%pk*inv(c,pk)%pk*ksm(pi,k,pk)%pk;
}

ll CRT(ll n,ll r[],ll m[]){
    ll res=0;
    rep(i,1,n) res=(res+(mod/m[i])*inv(mod/m[i],m[i])*r[i])%mod;
    return res;
}

ll par(ll n,ll m[],ll st[]){
    ll num=0;
    for (ll i=2; i*i<=n; i++) if (n%i==0){
        ll pk=1;
        while (n%i==0) pk*=i,n/=i;
        m[++num]=pk; st[num]=i;
    }
    if (n>1) m[++num]=n,st[num]=n;
    return num;
}

ll excomb(ll n,ll m){
    rep(i,1,num) r[i]=exlucas(n,m,st[i],Mod[i]);
    return CRT(num,r,Mod);
}

int main(){
    scanf("%lld\n",&mod); scanf("%lld%lld",&n,&m);
    ll sum=0; rep(i,1,m) scanf("%lld",&w[i]),sum+=w[i];
    if (n<sum){ puts("Impossible"); return 0; }
    num=par(mod,Mod,st); ans=1;
    rep(i,1,m) n-=w[i-1],ans=ans*excomb(n,w[i])%mod;
    printf("%lld\n",ans);
    return 0;
}
