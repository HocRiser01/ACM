//https://www.cnblogs.com/luckycode/p/5255656.html
//∏Óµ„”Î«≈:
var
	i,m,n,x,y,time,cnt:longint;
	a,g,ne,dfn,low,father:array[0..10000]of longint;
	b:array[0..10000]of boolean;
function min(x,y:longint):longint;
begin
	if x<y then exit(x) else exit(y);
end;
procedure add(x,y:longint);
begin
	inc(cnt); g[cnt]:=y; ne[cnt]:=a[x]; a[x]:=cnt;
end;
procedure tarjan(u,fa:longint);
var i,v:longint;
begin
	father[u]:=fa; inc(time);
	low[u]:=time; dfn[u]:=time; i:=a[u];
	while i<>0 do
		begin
			v:=g[i];
			if dfn[v]=0 then
				begin
					tarjan(v,u); low[u]:=min(low[u],low[v]);
				end
			else
				if fa<>v then low[u]:=min(low[u],dfn[v]);
			i:=ne[i];
		end;
end;
procedure count;
var sum,i,v:longint;
begin
	tarjan(1,0); sum:=0;
	for i:=2 to n do
		begin
			v:=father[i];
			if v=1 then inc(sum)
			else
				if dfn[v]<=low[i] then b[v]:=true;
		end;
	if sum>1 then b[1]:=true;
	for i:=1 to n do
		if b[i] then write(i,'  '); writeln;
	for i:=2 to n do
		begin
			v:=father[i];
			if dfn[v]<low[i] then writeln(v,',',i);
		end;
end;
begin
	readln(n,m); time:=0;
	for i:=1 to m do
		begin
			readln(x,y); add(x,y); add(y,x);
		end;
	count;
end.

//µ„DCC:
var
	time,top,cnt,x,y,n,m,i,e:longint;
	dfn,low,stack,father,g,ne,a:array[0..10000]of longint;
procedure add(x,y:longint);
begin
	inc(e); g[e]:=y; ne[e]:=a[x]; a[x]:=e;
end;
procedure dfs(u:longint);
var i,v,k:longint;
begin
	inc(time); dfn[u]:=time; low[u]:=time;
	inc(top); stack[top]:=u; i:=a[u];
	while i<>0 do
		begin
			v:=g[i];
			if dfn[v]=0 then
				begin
					father[v]:=u; dfs(v);
					if low[v]<low[u] then low[u]:=low[v];
					if low[v]>=dfn[u] then
						begin
							inc(cnt); write(cnt,' ');
							repeat
								k:=stack[top]; dec(top); write(' ',k);
							until v=k;
							writeln(' ',u);
						end;
				end
			else
				if (v<>father[u])and(dfn[v]<low[u]) then low[u]:=dfn[v];
			i:=ne[i];
		end;
end;
begin
	assign(input,'DCC.in'); reset(input);
	assign(output,'DCC.out'); rewrite(output);
	readln(n,m); cnt:=0; time:=0; top:=0; e:=0;
	for i:=1 to m do
		begin
			readln(x,y); add(x,y); add(y,x);
		end;
	dfs(1); close(input); close(output);
end.

//±ﬂDCC:
var
	i,m,n,x,y,time,cnt,sum:longint;
	a,g,ne,dfn,low,id:array[0..10000]of longint;
	b:array[0..10000]of boolean;
function min(x,y:longint):longint;
begin
	if x<y then exit(x) else exit(y);
end;
procedure add(x,y:longint);
begin
	inc(cnt); g[cnt]:=y; ne[cnt]:=a[x]; a[x]:=cnt;
end;
procedure tarjan(u,fa:longint);
var i,v:longint;
begin
	inc(time);
	low[u]:=time; dfn[u]:=time; i:=a[u];
	while i<>0 do
		begin
			v:=g[i];
			if dfn[v]=0 then
				begin
					tarjan(v,u); low[u]:=min(low[u],low[v]);
					if dfn[u]<low[v] then b[i]:=false;
				end
			else
				if fa<>v then low[u]:=min(low[u],dfn[v]);
			i:=ne[i];
		end;
end;
procedure dfs(x:longint);
var i,k:longint;
begin
	id[x]:=sum; write(' ',x); i:=a[x];
	while i<>0 do
		begin
			k:=g[i]; if (b[i])and(id[k]=0) then dfs(k); i:=ne[i];
		end;
end;
procedure work;
var i:longint;
begin
	tarjan(1,0); sum:=0;
	for i:=1 to n do
		if id[i]=0 then
			begin inc(sum); write(sum); dfs(i); writeln; end;
end;
begin
	assign(input,'edgeDCC.in'); reset(input);
	assign(output,'edgeDCC.out'); rewrite(output);
	readln(n,m); time:=0; fillchar(b,sizeof(b),true);
	for i:=1 to m do
		begin
			readln(x,y); add(x,y); add(y,x);
		end;
	work;
	close(input); close(output);
end.

//tarjan:
var
	i,m,n,cnt,top,tot,x,y:longint;
	low,time,stack,ne,a,g,belong:array[0..1000]of longint;
	instack:array[0..1000]of boolean;
procedure tarjan(x:longint);
var i,k:longint;
begin
	inc(cnt); time[x]:=cnt; low[x]:=cnt;
	instack[x]:=true; inc(top); stack[top]:=x; i:=a[x];
	while i<>0 do
		begin
			k:=g[i];
			if time[k]=0 then
				begin
					tarjan(k);
					if low[k]<low[x] then low[x]:=low[k];
				end
			else
				if (instack[k])and(time[k]<low[x]) then low[x]:=time[k];
			i:=ne[i];
		end;
	if time[x]=low[x] then
		begin
			inc(tot);
			repeat
				i:=stack[top]; dec(top);
				instack[i]:=false;
				belong[i]:=tot;
			until i=x;
		end;
end;

void tarjan(int u){
   low[u]=dfn[u]=++times;
   sta[++top]=u;
   for(int i=head[u];~i;i=e[i].next){
      int v=e[i].to;
      if(!dfn[v]){ tarjan(v); low[u]=min(low[u],low[v]); }
      else if(!bleg[v]) low[u]=min(low[u],dfn[v]);
   }
   if(dfn[u]==low[u]){
      bleg[0]++; cnt[bleg[0]]=0;
      do{
         bleg[sta[top]]=bleg[0];
         cnt[bleg[0]]+=(sta[top]<=ncnt);
      }while(sta[top--]!=u);
   }
}

begin
	readln(n,m); top:=0; tot:=0; cnt:=0;
	fillchar(a,sizeof(a),0); fillchar(time,sizeof(time),0);
	for i:=1 to m do
		begin
			readln(x,y); g[i]:=y; ne[i]:=a[x]; a[x]:=i;
		end;
	for i:=1 to n do
		if time[i]=0 then tarjan(i);
	writeln(i);
	for i:=1 to n do
		writeln('The ',i,'th node belongs to the Strongly Connected Component ',belong[i]);
end.
