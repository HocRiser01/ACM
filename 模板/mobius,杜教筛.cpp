//Mobius bzoj2301 O(N+Q*sqrt(N))
LL solve(int n,int m){
	LL res=0;
	if (n>m) swap(n,m);
	for (int i=1,l=0; i<=n; i=l+1){
		l=min(n/(n/i),m/(m/i));
		res+=1ll*(sum[l]-sum[i-1])*(n/i)*(m/i);
	}
	return res;
}

int main(){
	Mobius();
	for (scanf("%d",&T); T--; ){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		LL ans=solve(b/k,d/k)-solve((a-1)/k,d/k)-solve(b/k,(c-1)/k)+solve((a-1)/k,(c-1)/k);
		printf("%lld\n",ans);
	}
	return 0;
}

//杜教筛：http://www.cnblogs.com/y-clever/p/6514901.html
//O(Q*N^3/4),预处理O(Q*N^2/3)
//n^2/3粗略计算方法：b^2/3=a -> a^3/2=b -> (sqrt(a))^3=b
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long ll;
using namespace std;

const int N=2000100,M=100100;
int cas,n,m,cnt,c[N];
ll phi[N],mu[N],p[M],q[M];
bool vis[M];

ll get_p(int x){ return (x<=m) ? phi[x] : p[n/x]; }
ll get_q(int x){ return (x<=m) ? mu[x] : q[n/x]; }

void solve(int x){
	if (x<=m) return;
	int i,j=1,t=n/x;
	if (vis[t]) return;
	vis[t]=1; p[t]=((ll)x+1)*x>>1; q[t]=1;
	while (j<x){
		i=j+1; j=x/(x/i); solve(x/i);
		p[t]-=get_p(x/i)*(j-i+1); q[t]-=get_q(x/i)*(j-i+1);
	}
}

int main(){
	scanf("%d",&cas); m=2000000;
	int i,j; phi[1]=mu[1]=1;
	for (i=2; i<=m; i++){
		if (!phi[i]) phi[i]=i-1,mu[i]=-1,c[++cnt]=i;
		for (j=1; j<=cnt && i*c[j]<=m; j++)
			if (i%c[j]) phi[i*c[j]]=phi[i]*(c[j]-1),mu[i*c[j]]=-mu[i];
			else{ phi[i*c[j]]=phi[i]*c[j]; mu[i*c[j]]=0; break; }
	}
	for (i=2; i<=m; i++) phi[i]+=phi[i-1],mu[i]+=mu[i-1];
	while (cas--){
		scanf("%d",&n); memset(vis,0,sizeof(vis));
		if (n<=m) printf("%lld %lld\n",phi[n],mu[n]);
			else solve(1ll*n),printf("%lld %lld\n",p[1],q[1]);
	}
	return 0;
}

//记忆化
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long ll;
using namespace std;

const int N=5000010;
ll T,n,d,l,r,m,tot,p[N],miu[N],phi[N];
bool b[N];
map<ll,ll>mpM,mpP;

void init(ll n){
	miu[1]=phi[1]=1;
	rep(i,2,n){
		if (!b[i]) p[++tot]=i,miu[i]=-1,phi[i]=i-1;
		for (ll j=1; j<=tot && i*p[j]<=n; j++){
			b[i*p[j]]=1;
			if (i%p[j]) miu[i*p[j]]=-miu[i],phi[i*p[j]]=phi[i]*(p[j]-1);
				else { miu[i*p[j]]=0; phi[i*p[j]]=phi[i]*p[j]; break; }
		}
	}
	rep(i,2,n) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

ll Miu(ll x){
	if (x<=m) return miu[x];
	if (mpM.count(x)) return mpM[x];
	ll lst,res=1;
	for (ll i=2; i<=x; i=lst+1)
		lst=x/(x/i),res=res-Miu(x/i)*(lst-i+1);
	return mpM[x]=res;
}

ll Phi(ll x){
	if (x<=m) return phi[x];
	if (mpP.count(x)) return mpP[x];
	ll lst,res=1ll*x*(x+1)>>1;
	for (ll i=2; i<=x; i=lst+1)
		lst=x/(x/i),res=res-Phi(x/i)*(lst-i+1);
	return mpP[x]=res;
}

int main(){
	freopen("du.in","r",stdin);
	freopen("du.out","w",stdout);
	m=5000000; init(m);
	for (scanf("%lld",&T); T--; )
		scanf("%lld",&n),printf("%lld %lld\n",Phi(n),Miu(n));
	return 0;
}
