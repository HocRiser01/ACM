//POJ2104 静态主席树
var
	i,l,r,x,m,n,sz,tot:longint;
	root,a,num,hash:array[0..100100] of longint;
	lc,rc,s:array[0..2000100] of longint;

procedure qsort(l,r:longint);
var i,j,k,t:longint;
begin
	i:=l; j:=r; k:=num[(l+r)>>1];
	repeat
		while num[i]<k do inc(i);
		while num[j]>k do dec(j);
		if i<=j then
			begin
				t:=num[i]; num[i]:=num[j]; num[j]:=t;
				inc(i); dec(j);
			end;
	until i>j;
	if l<j then qsort(l,j);
	if i<r then qsort(i,r);
end;

function find(x:longint):longint;
var l,r,mid:longint;
begin
	l:=1; r:=tot;
	while l<=r do
		begin
			mid:=(l+r)>>1;
			if hash[mid]<x then l:=mid+1 else r:=mid-1;
		end;
	exit(l);
end;

procedure insert(l,r,x:longint; var y:longint; v:longint);
var mid:longint;
begin
	inc(sz); y:=sz; s[y]:=s[x]+1;
	if l=r then exit;
	lc[y]:=lc[x]; rc[y]:=rc[x];
	mid:=(l+r)>>1;
	if v<=mid then insert(l,mid,lc[x],lc[y],v)
	else insert(mid+1,r,rc[x],rc[y],v);
end;

function ask(l,r,x,y,k:longint):longint;
var mid:longint;
begin
	if l=r then exit(l);
	mid:=(l+r)>>1;
	if s[lc[y]]-s[lc[x]]>=k then exit(ask(l,mid,lc[x],lc[y],k))
	else exit(ask(mid+1,r,rc[x],rc[y],k-(s[lc[y]]-s[lc[x]])));
end;

begin
	readln(n,m);
	for i:=1 to n do read(a[i]);
	for i:=1 to n do num[i]:=a[i];
	qsort(1,n); tot:=1; hash[tot]:=num[1];
	for i:=2 to n do
		if num[i]<>num[i-1] then
			begin inc(tot); hash[tot]:=num[i]; end;
	for i:=1 to n do insert(1,tot,root[i-1],root[i],find(a[i]));
	for i:=1 to m do
		begin
			readln(l,r,x);
			writeln(hash[ask(1,tot,root[l-1],root[r],x)]);
		end;
end.

//cogs257
#include<cstdio>
#include<algorithm>
#include<cstring>
#define mid ((L+R)>>1)
#define mem(a) memset(a,0,sizeof(a))
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=100010,M=8000010;
char s[10];
int n,m,top,nd,l[30],r[30],a,b;
int T,v[N],num[N],f[N],A[N],B[N],K[N],rt[N],sum[M],ls[M],rs[M];

void upd(int y,int &x,int L,int R,int pos,int k){
     x=++nd; sum[x]=sum[y]+k; ls[x]=ls[y]; rs[x]=rs[y];
     if (L==R) return;
     if (pos<=mid) upd(ls[x],ls[x],L,mid,pos,k); else upd(rs[x],rs[x],mid+1,R,pos,k);
}

int que(int L,int R,int k){
    if (L==R) return L;
    int sl=0,sr=0;
    rep(i,1,a) sl+=sum[ls[l[i]]];
    rep(i,1,b) sr+=sum[ls[r[i]]];
    if (sr-sl>=k){
        rep(i,1,a) l[i]=ls[l[i]];
        rep(i,1,b) r[i]=ls[r[i]];
        return que(L,mid,k);
    }else{
          rep(i,1,a) l[i]=rs[l[i]];
          rep(i,1,b) r[i]=rs[r[i]];
          return que(mid+1,R,k-(sr-sl));
    }
}

int main(){
    freopen("dynrank.in","r",stdin);
    freopen("dynrank.out","w",stdout);
    for (scanf("%d",&T); T--; ){
        top=0; nd=0; mem(f); mem(ls); mem(rs);
        scanf("%d%d",&n,&m);
        rep(i,1,n) scanf("%d",v+i),num[++top]=v[i];
        rep(i,1,m){
            scanf("%s",s); scanf("%d%d",A+i,B+i);
            if (s[0]=='Q') scanf("%d",K+i),f[i]=1; else num[++top]=B[i];
        }
        sort(num+1,num+top+1); top=unique(num+1,num+top+1)-num-1;
        rep(i,1,n){
            int t=lower_bound(num+1,num+top+1,v[i])-num;
            for (int j=i; j<=n; j+=j&-j) upd(rt[j],rt[j],1,top,t,1);
        }
        rep(i,1,m) if (f[i]){
            a=0; b=0; A[i]--;
            for (int j=A[i]; j; j-=j&-j) l[++a]=rt[j];
            for (int j=B[i]; j; j-=j&-j) r[++b]=rt[j];
            printf("%d\n",num[que(1,top,K[i])]);
        }else{
              int t=lower_bound(num+1,num+top+1,v[A[i]])-num;
              for (int j=A[i]; j<=n; j+=j&-j) upd(rt[j],rt[j],1,top,t,-1);
              v[A[i]]=B[i]; t=lower_bound(num+1,num+top+1,B[i])-num;
              for (int j=A[i]; j<=n; j+=j&-j) upd(rt[j],rt[j],1,top,t,1);
        }
    }
    return 0;
}
