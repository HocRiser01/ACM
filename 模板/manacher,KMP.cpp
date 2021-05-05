//manacher:
uses math;
var
	i,n,id,maxid,maxl:longint;
	s:ansistring;
	s1:array[0..200100]of char;
	p:array[0..200100]of longint;
begin
	while not(eof) do
		begin
			readln(s); if s='' then continue;
			id:=0; maxid:=0; s1:=''; maxl:=0;
			for i:=1 to length(s) do
				begin
					s1[i<<1]:=s[i]; s1[(i<<1)+1]:='#';
				end;
			s1[0]:='$'; s1[1]:='#'; n:=(i<<1)+1;
			for i:=1 to n do
				begin
					if maxid>i then p[i]:=min(p[2*id-i],maxid-i)
								else p[i]:=1;
					while s1[i+p[i]]=s1[i-p[i]] do inc(p[i]);
					if p[i]+i>maxid then
						begin maxid:=p[i]+i; id:=i; end;
					if p[i]>maxl then maxl:=p[i];
				end;
			writeln(maxl-1);
		end;
end.

void get(){
	id=mx=mxl=0; len=strlen(s+1);
	rep(i,1,len) s1[i*2]=s[i],s1[i*2+1]='#';
	s1[0]='$'; s1[1]='#'; n=len*2+1;
	rep(i,1,n){
		p[i]=(mx>i) ? min(p[2*id-i],mx-i) : 1;
		while (s1[i+p[i]]==s1[i-p[i]]) p[i]++;
		if (p[i]+i>mx) mx=p[i]+i,id=i;
		mxl=max(mxl,p[i]);
	}
	printf("%d\n",mxl-1);
}

//KMP:
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

const int N=100010;
int n,p,nxt[N];
char s[N];

void getnxt(){
     int j=0; nxt[0]=nxt[1]=0;
     rep(i,2,n){
         while (j && s[j+1]!=s[i]) j=nxt[j];
         if (s[j+1]!=s[i]) nxt[i]=0; else nxt[i]=++j;
     }
}

int get(){
    int res=0,j=0;
    rep(i,2,n){
        while (j && s[j+1]!=s[i]) j=nxt[j];
        if (s[j+1]==s[i]) j++;
        if (j==p) res++,j=nxt[j];
    }
    return res;
}

int main(){
    scanf("%s",s+1); n=strlen(s+1);
    getnxt();
    for (p=nxt[n]; p && get()<2; p=nxt[p]);
    if (p==0) puts("Just a legend"); else rep(i,1,p) printf("%c",s[i]);
    return 0;
}
