//TJOI2016序列
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=100100;
int n,m,x,y,ans,c[N],f[N];
struct P{ int a,mn,mx,x,y,id; }q[N],p[N];

bool cmp(P a,P b){ return (a.x==b.x)?(a.y==b.y)?a.id<b.id:a.y<b.y:a.x<b.x; }

void add(int x,int k){ for (; x<=100000; x+=x&-x) c[x]=k?max(c[x],k):0; }
int que(int x){ int res=0; for (; x; x-=x&-x) res=max(res,c[x]); return res; }

void solve(int l,int r){
    if (l==r){ f[l]=max(f[l],1); return; }
    int mid=(l+r)>>1; solve(l,mid);
    rep(i,l,r)
        if (q[i].id<=mid) p[i].x=q[i].a,p[i].y=q[i].mx,p[i].id=q[i].id;
                        else p[i].x=q[i].mn,p[i].y=q[i].a,p[i].id=q[i].id;
    sort(p+l,p+r+1,cmp);
    rep(i,l,r) if (p[i].id<=mid) add(p[i].y,f[p[i].id]); else f[p[i].id]=max(f[p[i].id],que(p[i].y)+1);
    rep(i,l,r) if (p[i].id<=mid) add(p[i].y,0);
    solve(mid+1,r);
}

int main(){
    freopen("bzoj4553.in","r",stdin);
    freopen("bzoj4553.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d",&q[i].a),q[i].mn=q[i].mx=q[i].a,q[i].id=i;
    rep(i,1,m) scanf("%d%d",&x,&y),q[x].mn=min(q[x].mn,y),q[x].mx=max(q[x].mx,y);
    solve(1,n);
    rep(i,1,n) ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}

//动态区间第k小（整体二分）：(ranking)
//比线段树套treap快5倍,比动态主席树快10倍
type
	query=record
		x,y,k,s,opt,cur:longint;
	end;
var
	ch:char;
	i,m,n,num,cnt,x,y,z:longint;
	q,q1,q2:array[0..100100]of query;
	a,ans,tmp,t:array[0..100100]of longint;

function lowbit(x:longint):longint;
begin
	exit(x and (-x));
end;

procedure add(x,y:longint);
begin
	while x<=n do
		begin inc(t[x],y); inc(x,lowbit(x)); end;
end;

function ask(x:longint):longint;
var k:longint=0;
begin
	while x>0 do
		begin inc(k,t[x]); dec(x,lowbit(x)); end;
	exit(k);
end;

procedure divide(head,tail,l,r:longint);
var i,mid,l1,l2:longint;
begin
	if head>tail then exit;
	if l=r then
		begin
			for i:=head to tail do
				if q[i].opt=3 then ans[q[i].s]:=l;
			exit;
		end;
	mid:=(l+r)>>1;
	for i:=head to tail do
		begin
			if (q[i].opt=1)and(q[i].y<=mid) then add(q[i].x,1);
			if (q[i].opt=2)and(q[i].y<=mid) then add(q[i].x,-1);
			if q[i].opt=3 then tmp[i]:=ask(q[i].y)-ask(q[i].x-1);
		end;
	for i:=head to tail do
		begin
			if (q[i].opt=1)and(q[i].y<=mid) then add(q[i].x,-1);
			if (q[i].opt=2)and(q[i].y<=mid) then add(q[i].x,1);
		end;
	l1:=0; l2:=0;
	for i:=head to tail do
		if q[i].opt=3 then
			if q[i].cur+tmp[i]>=q[i].k then
				begin inc(l1); q1[l1]:=q[i]; end
			else
				begin
					inc(q[i].cur,tmp[i]); inc(l2); q2[l2]:=q[i];
				end
		else
			if q[i].y<=mid then
				begin inc(l1); q1[l1]:=q[i]; end
			else
				begin inc(l2); q2[l2]:=q[i]; end;
	for i:=1 to l1 do q[head+i-1]:=q1[i];
	for i:=1 to l2 do q[head+l1+i-1]:=q2[i];
	divide(head,head+l1-1,l,mid);
	divide(head+l1,tail,mid+1,r);
end;

begin
	assign(input,'ranking.in'); reset(input);
	assign(output,'ranking.out'); rewrite(output);
	readln(n,m); cnt:=0; num:=0;
	for i:=1 to n do
		begin
			read(a[i]); inc(num);
			q[num].x:=i; q[num].y:=a[i];
			q[num].opt:=1; q[num].s:=0;
		end;
	readln;
	for i:=1 to m do
		begin
			read(ch);
			if ch='Q' then
				begin
					read(ch); readln(x,y,z); inc(num);
					q[num].x:=x; q[num].y:=y; q[num].k:=z;
					q[num].opt:=3; inc(cnt); q[num].s:=cnt;
				end
			else
				begin
					read(ch); readln(x,y); inc(num);
					q[num].x:=x; q[num].y:=a[x];
					q[num].opt:=2; q[num].s:=0;
					inc(num); q[num].x:=x; q[num].y:=y;
					q[num].opt:=1; q[num].s:=0;
					a[x]:=y;
				end;
		end;
	divide(1,num,0,1000000000);
	for i:=1 to cnt do writeln(ans[i]);
	close(input); close(output);
end.
