//两个节点所代表的right集合若非包含关系则不相交
//一个节点所代表的最短串长度mn[x]=mx[fa[x]]+1
//走son即左端集合不变（可能增加），最大被包含，走fa即右端集合不变，最小包含。
//sigma(y|fa[y]==x)即x的右端点集合完全合并。
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mem(a) memset(a,0,sizeof(a))
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=40010;
int n,lst,cnt,ans,l[N],r[N],mx[N],fa[N],a[N],son[N][180],q[N],v[N];

void init(){
	memset(l,127,sizeof(l));
	mem(r); mem(v); mem(mx); mem(fa); mem(son);
	lst=cnt=1; ans=0;
}

void ext(int c){
	int p=lst,np=lst=++cnt; mx[np]=mx[p]+1;
	l[np]=r[np]=mx[np];
	while (!son[p][c] && p) son[p][c]=np,p=fa[p];
	if (!p) fa[np]=1;
	else{
		int q=son[p][c];
		if (mx[p]+1==mx[q]) fa[np]=q;
		else{
			int nq=++cnt; mx[nq]=mx[p]+1;
			memcpy(son[nq],son[q],sizeof(son[q]));
			fa[nq]=fa[q]; fa[np]=fa[q]=nq;
			while (son[p][c]==q) son[p][c]=nq,p=fa[p];
		}
	}
}

void solve(){
	rep(i,1,cnt) v[mx[i]]++;
	rep(i,1,n) v[i]+=v[i-1];
	for (int i=cnt; i; i--) q[v[mx[i]]--]=i;
	for (int i=cnt; i; i--){
	    int p=q[i];
	    l[fa[p]]=min(l[fa[p]],l[p]); r[fa[p]]=max(r[fa[p]],r[p]);
	}
	rep(i,1,cnt) ans=max(ans,min(mx[i],r[i]-l[i]));
	if (ans<4) puts("0"); else printf("%d\n",ans+1);
}

int main(){
    freopen("poj1743.in","r",stdin);
    freopen("poj1743.out","w",stdout);
    while (scanf("%d",&n)){
		if (!n) break;
		rep(i,1,n) scanf("%d",a+i); n--;
		rep(i,1,n) a[i]=a[i+1]-a[i]+88;
		init(); rep(i,1,n) ext(a[i]); solve();
    }
    return 0;
}
