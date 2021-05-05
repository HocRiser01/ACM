#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=600100,M=300000*2*25;
char ch;
int n,m,nd,x,l,r,b[N],a[N],rt[N],c[M][2],sm[M];

void ins(int y,int &x,int k){
    int tmp=++nd; x=nd;
    for (int i=23; ~i; i--){
        c[x][0]=c[y][0]; c[x][1]=c[y][1]; sm[x]=sm[y]+1;
        int t=(k>>i)&1; c[x][t]=++nd; x=c[x][t]; y=c[y][t];
    }
    sm[x]=sm[y]+1; x=tmp;
}

int que(int l,int r,int k){
    int res=0;
    for (int i=23; ~i; i--){
        int t=(k>>i)&1;
        if (sm[c[r][t^1]]-sm[c[l][t^1]]) res+=1<<i,r=c[r][t^1],l=c[l][t^1];
            else r=c[r][t],l=c[l][t];
    }
    return res;
}

int main(){
    freopen("bzoj3261.in","r",stdin);
    freopen("bzoj3261.out","w",stdout);
    scanf("%d%d",&n,&m); n++; ins(rt[0],rt[1],0);
    rep(i,2,n) scanf("%d",&a[i]),b[i]=b[i-1]^a[i],ins(rt[i-1],rt[i],b[i]);
    rep(i,1,m){
        scanf(" %c",&ch);
        if (ch=='A') scanf("%d",&x),n++,b[n]=b[n-1]^x,ins(rt[n-1],rt[n],b[n]);
                    else scanf("%d%d%d",&l,&r,&x),printf("%d\n",que(rt[l-1],rt[r],b[n]^x));
    }
    return 0;
}
