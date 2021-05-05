//匈牙利O(n^3):
var
	i,x,y,e,n,s:longint;
	map:array[1..1010,1..1010]of boolean;//记录读入的边
	mark:array[1..1010]of boolean;//标记在一个点是否在增广路中
	lk:array[1..1010]of longint;//不是记录增广路，而是记录匹配边
function find(x:longint):boolean;
var i:longint;
begin
	for i:=1 to n do
		if (map[x,i])and(not(mark[i])) then
   		begin
   			mark[i]:=true;
   			if (lk[i]=0)or(find(lk[i])) then
   				begin lk[i]:=x; exit(true); end;
			end;
	exit(false);//表示找不到合适的边，该增广路不合理。
end;
begin
	fillchar(map,sizeof(map),0);
	readln(n,e);
	for i:=1 to e do
		begin
			readln(x,y); map[x,y]:=true;//邻接表储存
		end;
	s:=0;
	for i:=1 to n do
		begin
			fillchar(mark,sizeof(mark),false);
			if find(i) then inc(s);
		end;
	writeln(s);
end.

//KM算法O(n^3) hdu2255:
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=310,inf=0x3f3f3f3f;
int n,lk[N],lx[N],ly[N],vx[N],vy[N],s[N],w[N][N];

int dfs(int x){
    vx[x]=1;
    rep(y,1,n){
        if (vy[y]) continue;
        int t=lx[x]+ly[y]-w[x][y];
        if (t==0){
            vy[y]=1;
            if (lk[y]==-1 || dfs(lk[y])) { lk[y]=x; return 1;}
        }else s[y]=min(s[y],t);
    }
    return 0;
}

int KM(){
    memset(lk,-1,sizeof(lk));
    memset(lx,-inf,sizeof(lx));
    memset(ly,0,sizeof(ly));
    rep(i,1,n) rep(j,1,n) if (w[i][j]>lx[i]) lx[i]=w[i][j];
    rep(x,1,n){
        rep(i,1,n) s[i]=inf;
        while (1){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if (dfs(x)) break;
            int d=inf;
            rep(i,1,n) if (!vy[i] && d>s[i]) d=s[i];
            rep(i,1,n) if (vx[i]) lx[i]-=d;
            rep(i,1,n) if (vy[i]) ly[i]+=d; else s[i]-=d;
        }
    }
    int res=0;
    rep(i,1,n) if (lk[i]!=-1) res+=w[lk[i]][i];
    return res;
}
