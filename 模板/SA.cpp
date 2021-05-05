#include<cstdio>
#include<cstring>
#include<algorithm>
#define LCP(x,y) SA.que(x,y)
#define LCS(x,y) SA1.que(n-y+1,n-x+1)
#define rep(i,l,r) for (int i=l; i<=r; i++)
const int N=30010;
typedef long long LL;
using namespace std;
int n,T,log[N],f[N],g[N];
char s[N]; LL ans;

struct sa_array{
   int sa[N],rk[N],h[N],st[N][16],x[N],y[N],c[N]; char S[N];
   int Cmp(int a,int b,int l){ return y[a]==y[b] && y[a+l]==y[b+l]; }
   
   void build_sa(int m){
      memset(y,0,sizeof(y));
      rep(i,0,m) c[i]=0;
      rep(i,1,n) c[x[i]=S[i]-'a'+1]++;
      rep(i,1,m) c[i]+=c[i-1];
      for (int i=n; i; i--) sa[c[x[i]]--]=i;
      for (int k=1,p=0; p<n; k<<=1,m=p){
         p=0;
         rep(i,n-k+1,n) y[++p]=i;
         rep(i,1,n) if (sa[i]>k) y[++p]=sa[i]-k;
         rep(i,0,m) c[i]=0;
         rep(i,1,n) c[x[y[i]]]++;
         rep(i,1,m) c[i]+=c[i-1];
         for (int i=n; i; i--) sa[c[x[y[i]]]--]=y[i];
         rep(i,1,n) y[i]=x[i]; p=1; x[sa[1]]=1;
         rep(i,2,n) x[sa[i]]=Cmp(sa[i-1],sa[i],k) ? p : ++p;
      }
   }
   
   void get(){
   	int k=0;
      rep(i,1,n) rk[sa[i]]=i;
      rep(i,1,n){
         for (int j=sa[rk[i]-1]; i+k<=n && j+k<=n && S[i+k]==S[j+k]; k++);
         h[rk[i]]=k; if (k) k--;
      }
   }
   
   void rmq(){
      rep(i,1,n) st[i][0]=h[i];
      rep(i,1,log[n])
      rep(j,1,n-(1<<i)+1) st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
   }
   
   int ask(int l,int r){
      l++; int t=log[r-l+1];
      return min(st[l][t],st[r-(1<<t)+1][t]);
   }
   
   int que(int x,int y){ return ask(min(rk[x],rk[y]),max(rk[x],rk[y]));}
   
}SA,SA1;

void solve(){
   memset(f,0,sizeof(f)); memset(g,0,sizeof(g));
   for (int len=1,x,y,l,r; 2*len<=n; len++)
      for (int i=1,j=len+1; j<=n; i+=len,j+=len)
         if (s[i]==s[j]){
            x=LCS(i,j); y=LCP(i,j);
            l=max(i,i-x+len); r=min(i+y,j);
            if (r>l){
               f[l+len]++; f[r+len]--;
               g[l-len+1]++; g[r-len+1]--;
            }
         }
   rep(i,2,n) f[i]+=f[i-1],g[i]+=g[i-1];
   rep(i,1,n-1) ans+=(LL)f[i]*g[i+1];
}

int main(){
   freopen("excellent.in","r",stdin);
   freopen("excellent.out","w",stdout);
   log[1]=0; rep(i,2,N) log[i]=log[i>>1]+1;
   scanf("%d",&T);
   while (T--){
      scanf("%s",s+1); n=strlen(s+1);
      rep(i,1,n) SA.S[i]=SA1.S[n-i+1]=s[i];
      SA.build_sa(30); SA.get(); SA.rmq();
      SA1.build_sa(30); SA1.get(); SA1.rmq();
      ans=0; solve(); printf("%lld\n",ans);
   }
   return 0;
}
