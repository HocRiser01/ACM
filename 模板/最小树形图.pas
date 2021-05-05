const inf=10000000;
type
	rec=record
		u,v,w:longint;
	end;
var
	i,m,n,ans,ansi,sum:longint;
	e:array[0..1000100]of rec;
	ind,vis,id,pre:array[0..1010]of longint;

function zhuliu(rt,n,m:longint):longint;
var u,v,i,cnt,tn:longint;
begin
	cnt:=0;
	while true do
		begin
			tn:=0;
			for i:=1 to n do ind[i]:=inf;
			for i:=1 to m do
				begin
					u:=e[i].u; v:=e[i].v;
					if (e[i].w<ind[v])and(u<>v) then
						begin
							pre[v]:=u; ind[v]:=e[i].w;
							if u=rt then ansi:=i;
						end;
				end;
			for i:=1 to n do
				if (i<>rt)and(ind[i]=inf) then exit(-1);
			for i:=1 to n do
				begin vis[i]:=-1; id[i]:=-1; end;
			ind[rt]:=0;
			for i:=1 to n do
				begin
					inc(cnt,ind[i]); v:=i;
					while (vis[v]<>i)and(id[v]=-1)and(v<>rt) do
						begin vis[v]:=i; v:=pre[v]; end;
					if (v<>rt)and(id[v]=-1) then
						begin
							u:=pre[v]; inc(tn);
							while u<>v do
								begin id[u]:=tn; u:=pre[u]; end;
							id[v]:=tn;
						end;
				end;
			if tn=0 then break;
			for i:=1 to n do
				if id[i]=-1 then
					begin inc(tn); id[i]:=tn; end;
			for i:=1 to m do
				begin
					v:=e[i].v;
					e[i].u:=id[e[i].u]; e[i].v:=id[e[i].v];
					if e[i].u<>e[i].v then dec(e[i].w,ind[v]);
				end;
			n:=tn; rt:=id[rt];
		end;
	exit(cnt);
end;

begin
	while not(eof) do
		begin
			sum:=0; readln(n,m);
			for i:=1 to m do
				begin
					readln(e[i].u,e[i].v,e[i].w);
					inc(e[i].u); inc(e[i].v); inc(sum,e[i].w);
				end;
			inc(sum);
			for i:=m+1 to m+n do
				begin
					e[i].u:=n+1; e[i].v:=i-m; e[i].w:=sum;
				end;
			ans:=zhuliu(n+1,n+1,n+m);
			if (ans=-1)or(ans>=2*sum) then writeln('impossible')
											else writeln(ans-sum,' ',ansi-m-1);
			writeln; readln;
		end;
end.
