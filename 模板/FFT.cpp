//FFT
#include<cstdio>
#include<complex>       
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

typedef complex<double> C;
const int N=262145;
const double pi=acos(-1.);
int n,m,L,x,rev[N];
C a[N],b[N];

void DFT(C a[],int f){
    rep(i,0,n-1) if (i<rev[i]) swap(a[i],a[rev[i]]);
    for (int i=1; i<n; i<<=1){
        C wn(cos(pi/i),f*sin(pi/i));
        for (int p=i<<1,j=0; j<n; j+=p){
            C w(1,0);
            for (int k=0; k<i; k++,w*=wn){
                C x=a[j+k],y=w*a[i+j+k]; a[j+k]=x+y; a[i+j+k]=x-y;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    rep(i,0,n) scanf("%d",&x),a[i]=x;
    rep(i,0,m) scanf("%d",&x),b[i]=x;
    m=n+m; for (n=1; n<=m; n<<=1) L++;
    rep(i,0,n-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
    DFT(a,1); DFT(b,1);
    rep(i,0,n-1) a[i]=a[i]*b[i];
    DFT(a,-1);
    rep(i,0,m) printf("%d ",(int)(a[i].real()/n+0.5));
    return 0;
}

//NTT
#include<cstdio>
#include<complex>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=262145,md=(119<<23)+1,G=3;//998244353
int n,m,L,x,rev[N],a[N],b[N];

int ksm(int a,int b){
   int res;
   for (res=1; b; a=(1ll*a*a)%md,b>>=1)
      if (b & 1) res=(1ll*res*a)%md;
   return res;
}

void FFT(int a[],int f){
   rep(i,0,n-1) if (i<rev[i]) swap(a[i],a[rev[i]]);
   for (int i=1; i<n; i<<=1){
      int wn=ksm(G,(f==1) ? (md-1)/(i<<1) : (md-1)-(md-1)/(i<<1));
      for (int p=i<<1,j=0; j<n; j+=p){
         int w=1;
         for (int k=0; k<i; k++,w=1ll*w*wn%md){
            int x=a[j+k],y=1ll*w*a[i+j+k]%md;
            a[j+k]=(x+y)%md; a[i+j+k]=(x-y+md)%md;
         }
      }
   }
   if (f==1) return;
   int inv=ksm(n,md-2);
   rep(i,0,n-1) a[i]=1ll*a[i]*inv%md;
}

int main(){
   scanf("%d%d",&n,&m);
   rep(i,0,n) scanf("%d",&x),a[i]=x;
   rep(i,0,m) scanf("%d",&x),b[i]=x;
   m=n+m; for (n=1; n<=m; n<<=1) L++;
   rep(i,0,n-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
   FFT(a,1); FFT(b,1);
   rep(i,0,n-1) a[i]=1ll*a[i]*b[i]%md;
   FFT(a,-1);
   rep(i,0,m) printf("%d ",a[i]);
   return 0;
}
