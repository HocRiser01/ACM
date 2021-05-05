#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
typedef long long ll;
using namespace std;

const int N=(1<<18)+5,mod=998244353,rev=499122177;
int n,m,len,s[N],t[N],a[N],b[N];

void FWT(int a[],int n,int f,int op){
	for (int i=1; i<n; i<<=1)
		for (int p=i<<1,j=0; j<n; j+=p)
			for (int k=0; k<i; k++){
				int x=a[j+k],y=a[i+j+k];
				if (op==1){//or
					if (f==1) a[i+j+k]=(x+y)%mod; else a[i+j+k]=(y-x+mod)%mod;
				}
				if (op==2){//and
					if (f==1) a[j+k]=(x+y)%mod; else a[j+k]=(x-y+mod)%mod;
				}
				if (op==3){//xor
					if (f==1) a[j+k]=(x+y)%mod,a[i+j+k]=(x-y+mod)%mod;
						else a[j+k]=1ll*(x+y)*rev%mod,a[i+j+k]=((1ll*(x-y)*rev)%mod+mod)%mod;
				}
	}
}

int main(){
	freopen("FWT.in","r",stdin);
	freopen("FWT.out","w",stdout);
	scanf("%d",&n); n=1<<n; len=n+n;
	for (int i=0; i<n; i++) scanf("%d",&s[i]);
	for (int i=0; i<n; i++) scanf("%d",&t[i]);
	rep(op,1,3){
		for (int i=0; i<len; i++) a[i]=s[i],b[i]=t[i];
		FWT(a,len,1,op); FWT(b,len,1,op);
		for (int i=0; i<len; i++) a[i]=1ll*a[i]*b[i]%mod;
		FWT(a,len,-1,op);
		for (int i=0; i<n; i++) printf("%d ",a[i]); puts("");
	}
	return 0;
}