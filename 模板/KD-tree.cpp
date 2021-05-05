#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define lson ls[x],L,mid
#define rson rs[x],mid+1,R
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const double A=0.75;
const int N=5000000,M=1000000000;
int ans,D,lst,n,q,x,y,k,top,tot,need,dd,nd,nd1,X1,Y1,X2,Y2,op,Rt,ls[N],rs[N],rt[N],stk[N],w[N];

struct P{
    int d[2],mn[2],mx[2],l,r,sz;
    int& operator [](int x){ return d[x]; }
    friend bool operator <(P a,P b){ return a[D]<b[D]; }
    void clear(){ d[0]=d[1]=mn[0]=mn[1]=mx[0]=mx[1]=l=r=sz=0; }
}t[N],p[N],T;

int get(){ if (top) return x=stk[top--]; else return ++nd; }
void del(int x){ t[x].clear(); stk[++top]=x; }

void upd(int x){
   int l=t[x].l,r=t[x].r; t[x].sz=1;
   if (l) t[x].sz+=t[l].sz;
   if (r) t[x].sz+=t[r].sz;
   rep(i,0,1){
       t[x].mn[i]=t[x].mx[i]=t[x][i];
       if (l) t[x].mn[i]=min(t[x].mn[i],t[l].mn[i]),t[x].mx[i]=max(t[x].mx[i],t[l].mx[i]);
       if (r) t[x].mn[i]=min(t[x].mn[i],t[r].mn[i]),t[x].mx[i]=max(t[x].mx[i],t[r].mx[i]);
     }
}

int build(int l,int r,int k){
    if (l>r) return 0;
    D=k; int mid=(l+r)>>1,x=get();
    nth_element(p+l,p+mid,p+r+1); t[x]=p[mid];
    t[x].l=build(l,mid-1,k^1); t[x].r=build(mid+1,r,k^1);
    upd(x); return x;
}

bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{ return x1<=X1 && X2<=x2 && y1<=Y1 && Y2<=y2;}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{ return x1>X2 || x2<X1 || y1>Y2 || y2<Y1; }
int dfs(int x){ if (t[x].l) dfs(t[x].l); p[++tot]=t[x]; if (t[x].r) dfs(t[x].r); del(x);}

void ins(int &x,int k){
    if (!x) { x=get(); t[x]=T; upd(x); return; }
    if (T[k]<t[x][k]) ins(t[x].l,k^1); else ins(t[x].r,k^1);
    if (t[t[x].l].sz>t[x].sz*A || t[t[x].r].sz>t[x].sz*A) need=x,dd=k;
    upd(x);
}

void ins1(int &rt){
    need=0; ins(rt,0);
    if (need) tot=0,dfs(need),need=build(1,tot,dd);
}

void que(int x,int k){
    if (!x || out(X1,Y1,X2,Y2,t[x].mn[0],t[x].mn[1],t[x].mx[0],t[x].mx[1])) return;
    if (in(X1,Y1,X2,Y2,t[x].mn[0],t[x].mn[1],t[x].mx[0],t[x].mx[1])) { ans+=t[x].sz; return; }
    if (in(X1,Y1,X2,Y2,t[x][0],t[x][1],t[x][0],t[x][1])) ans++;
    que(t[x].l,k^1); que(t[x].r,k^1);
}

void insert(int &x,int L,int R,int v){
    if (!x) x=++nd1;
    ins1(rt[x]); int mid=(L+R)>>1;
    if (L==R) return;
    if (v<=mid) insert(lson,v); else insert(rson,v);
}

int query(int x,int L,int R,int k){
    if (L==R) return L;
    ans=0; if (rs[x]) que(rt[rs[x]],0); int mid=(L+R)>>1;
    if (k>ans) return query(lson,k-ans); else return query(rson,k);
}

int main(){
    scanf("%d%d",&n,&q);
    rep(i,1,N-1) w[i]=10000;
    rep(i,1,q){
        scanf("%d",&op);
        if (op==1) scanf("%d%d%d",&x,&y,&k),x^=lst,y^=lst,k^=lst,T[0]=x,T[1]=y,insert(Rt,1,M,k);
              else{
                   scanf("%d%d%d%d%d",&X1,&Y1,&X2,&Y2,&k);
                   X1^=lst; Y1^=lst; X2^=lst; Y2^=lst; k^=lst;
                   ans=0; que(rt[Rt],0);
                   if (ans<k) { puts("NAIVE!ORZzyz."); lst=0; continue; }
                   printf("%d\n",lst=query(Rt,1,M,k));
              }
    }
    return 0;
}
