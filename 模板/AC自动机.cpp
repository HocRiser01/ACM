#include<cstdio>
#include<algorithm>
#include<cstring>
#define rep(i,l,r) for (register int i=l; i<=r; ++i)
using namespace std;

const int N=6010,M=110,md=10007;
int q[N],ch[N][27],f[M][N],fail[N],cnt,n,m;
char s[M],w[N];

void clear(int x){ memset(ch[x],0,sizeof(ch[x])); fail[x]=0; }

void ins(char s[]){
	int l=strlen(s),x=0;
	rep(i,0,l-1){
		int t=s[i]-'A'+1;
		if (!ch[x][t]) clear(++cnt),ch[x][t]=cnt;
		x=ch[x][t];
	}
	w[x]=1;
}

void build(){
	int st=1,ed=0;
	rep(i,1,26) if (ch[0][i]) q[++ed]=ch[0][i];
	while (st!=ed+1){
		int x=q[st++];
		rep(i,1,26)
			if (ch[x][i]) q[++ed]=ch[x][i],fail[ch[x][i]]=ch[fail[x]][i];
						else ch[x][i]=ch[fail[x]][i];
		w[x]|=w[fail[x]];
	}
}

void work(){
	int ans1=1,ans2=0; f[0][0]=1;
	rep(i,1,m) rep(j,0,cnt) if (!w[j])
		rep(k,1,26) f[i][ch[j][k]]=(f[i][ch[j][k]]+f[i-1][j])%md;
	rep(i,0,cnt) if (!w[i]) ans2+=f[m][i];
	rep(i,1,m) ans1=ans1*26%md;
	printf("%d\n",((ans1-ans2)%md+md)%md);
}

int main(){
	freopen("bzoj1030.in","r",stdin);
	freopen("bzoj1030.out","w",stdout);
	scanf("%d%d",&n,&m); rep(i,1,n) scanf("%s",s),ins(s);
	build(); work();
	return 0;
}

//bzoj2434
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (register int i=l; i<=r; ++i)
#define For(i,x) for (int i=h[x]; i; i=e[i].nxt)
using namespace std;
 
const int N=100100;
int cnt,tim,tot,now,len,k,nd,st,ed,m,n;
int ch[N][27],c[N],h[N],l[N],r[N],fa[N],pos[N],q[N],fail[N],ans[N];
char s[N];
struct P{ int x,y,id; }a[N];
struct E{ int to,nxt; }e[N];
void add(int u,int v){ e[++cnt]=(E){v,h[u]}; h[u]=cnt; }
 
void ins(int x,int k){ for (int i=x; i<=tim; i+=i & -i) c[i]+=k; }
int que(int x){ int res=0; for (int i=x; i; i-=i & -i) res+=c[i]; return res; }
 
void dfs(int x){
    l[x]=r[x]=++tim;
    For(i,x) dfs(e[i].to),r[x]=r[e[i].to];
}
 
void work(){
    int t=0; now=0; k=1;
    rep(i,1,len){
        if (s[i]=='B') { ins(l[now],-1); now=fa[now]; continue; }
        if (s[i]=='P') {
            for (t++; a[k].y==t && k<=m; k++) ans[a[k].id]=que(r[pos[a[k].x]])-que(l[pos[a[k].x]]-1); continue;
        }
        now=ch[now][s[i]-'a']; ins(l[now],1);
    }
}
 
int cmp(P a,P b){ return a.y<b.y; }
 
int main(){
    scanf("%s",s+1); len=strlen(s+1); now=0;
    rep(i,1,len){
        if (s[i]=='B') { now=fa[now]; continue; }
        if (s[i]=='P') { pos[++tot]=now; continue; }
        int t=s[i]-'a'; if (ch[now][t]) now=ch[now][t]; else ch[now][t]=++nd,fa[nd]=now,now=nd;
    }
    st=1; ed=0;
    rep(i,0,25) if (ch[0][i]) q[++ed]=ch[0][i];
    while (st!=ed+1){
        int x=q[st++];
        rep(i,0,25)
            if (ch[x][i]) q[++ed]=ch[x][i],fail[ch[x][i]]=ch[fail[x]][i];
                        else ch[x][i]=ch[fail[x]][i];
    }
    rep(i,1,nd) add(fail[i],i);
    dfs(0); scanf("%d",&m);
    rep(i,1,m) scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i;
    sort(a+1,a+m+1,cmp); work();
    rep(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
