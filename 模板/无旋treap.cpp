//无旋treap:
#include<cstdio>
#include<algorithm>
#define P pair<int,int>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=200100,inf=1000000000;
int T,nd,rt,op,ans,x,ls[N],rs[N],h[N],sz[N],v[N];

void upd(int x){ sz[x]=sz[ls[x]]+sz[rs[x]]+1; }
int get(int x){ v[++nd]=x; sz[nd]=1; h[nd]=rand(); return nd; }

int merge(int x,int y){
	if (!x || !y) return x+y;
	if (h[x]<h[y]) { rs[x]=merge(rs[x],y); upd(x); return x; }
				else { ls[y]=merge(x,ls[y]); upd(y); return y; }
}

P split(int x,int k){
	if (!x) return P(0,0);
	P tmp;
	if (k<=sz[ls[x]]) tmp=split(ls[x],k),ls[x]=tmp.second,upd(x),tmp=P(tmp.first,x);
					 else tmp=split(rs[x],k-sz[ls[x]]-1),rs[x]=tmp.first,upd(x),tmp=P(x,tmp.second);
	return tmp;
}

int rank(int x,int k){
	if (!x) return 0;
	if (v[x]>=k) return rank(ls[x],k); else return rank(rs[x],k)+sz[ls[x]]+1;
}

int find(int x,int k){
	if (!x) return 0;
	if (k==sz[ls[x]]+1) return x;
	if (k<=sz[ls[x]]) return find(ls[x],k); else return find(rs[x],k-sz[ls[x]]-1);
}

void ins(int k){
	int v=rank(rt,k); P x=split(rt,v);
	rt=merge(merge(x.first,get(k)),x.second);
}

void del(int k){
	int v=rank(rt,k);
	P x=split(rt,v),y=split(x.second,1);
	rt=merge(x.first,y.second);
}

int main(){
	freopen("bzoj3224.in","r",stdin);
	freopen("bzoj3224.out","w",stdout);
	for (scanf("%d",&T); T--; ){
		scanf("%d%d",&op,&x);
		if (op==1) ins(x);
		if (op==2) del(x);
		if (op==3) printf("%d\n",rank(rt,x)+1);
		if (op==4) printf("%d\n",v[find(rt,x)]);
		if (op==5) printf("%d\n",v[find(rt,rank(rt,x))]);
		if (op==6) printf("%d\n",v[find(rt,rank(rt,x+1)+1)]);
	}
	return 0;
}

//可持久化treap:
#include "expr.h"
#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

struct Treap{ int l,r,size,rev,fix; Data val,sum; }t[30000005];
int root[20005],cnt,cur;
int newnode(int x){ t[++cnt]=t[x]; return cnt;}

void pushup(int x){
	t[x].size=t[t[x].l].size+t[t[x].r].size+1;
	if(t[x].fix<=100 && t[x].l && t[x].r) t[x].sum=F(t[t[x].l].sum,t[t[x].r].sum,t[x].fix);
		else t[x].sum=t[x].val;
}

void rever(int &x){
	if (!x) return;
	int now=newnode(x); t[now].rev^=1;
	swap(t[now].l,t[now].r); x=now;
}

void pushdown(int x){
	if (!t[x].rev) return; t[x].rev=0;
	rever(t[x].l); rever(t[x].r);
}

bool cmp(int x,int y){
	if (t[x].fix==t[y].fix) return rand()%(t[x].size+t[y].size)<t[x].size;
	return t[x].fix<t[y].fix;
}

int merge(int x,int y){
	if (!x || !y) return x+y;
	pushdown(x); pushdown(y); int now;
	if (cmp(x,y)) now=newnode(x),t[now].r=merge(t[now].r,y);
	else now=newnode(y),t[now].l=merge(x,t[now].l);
	pushup(now); return now;
}

P split(int x,int k){
	if (!x) return P(0,0);
	pushdown(x);
	int now=newnode(x); P tmp;
	if(k<=t[t[now].l].size){
		tmp=split(t[now].l,k);
		t[now].l=tmp.second; pushup(now);
		tmp=P(tmp.first,now);
	}
	else{
		tmp=split(t[now].r,k-t[t[now].l].size-1);
		t[now].r=tmp.first;pushup(now);
		tmp=P(now,tmp.second);
	}
	return tmp;
}

void init(int test_id,int n,int m,int k,const Data *a,const int *ops){
	Data tmp=a[0]; int x;
	for(int i=n-1; i>=0; i--){
		x=newnode(0);
		t[x].val=t[x].sum=a[i]; t[x].fix=101; t[x].size=1;
		root[0]=merge(x,root[0]);
		if (i){
			x=newnode(0);
			t[x].val=t[x].sum=tmp; t[x].fix=ops[i]; t[x].size=1;
			root[0]=merge(x,root[0]);
		}
	}
}

Data modify_data(int id,int pos,Data x){
	root[++cur]=root[id];
	P a=split(root[cur],2*pos+1),b=split(a.first,2*pos);
	int now=newnode(b.second); t[now].val=t[now].sum=x;
	root[cur]=merge(merge(b.first,now),a.second);
	return t[root[cur]].sum;
}

Data modify_op(int id,int pos,int new_op){
	root[++cur]=root[id];
	P a=split(root[cur],2*pos),b=split(a.first,2*pos-1);
	int now=newnode(b.second); t[now].fix=new_op; pushup(now);
	root[cur]=merge(merge(b.first,now),a.second);
	return t[root[cur]].sum;
}

Data reverse(int id,int l,int r){
	root[++cur]=root[id];
	P a=split(root[cur],2*r+1),b=split(a.first,2*l);
	rever(b.second);
	root[cur]=merge(merge(b.first,b.second),a.second);
	return t[root[cur]].sum;
}