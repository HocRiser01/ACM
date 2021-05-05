(EX)BSGS:
void BSGS(){
	mp.clear();
	if (a==0 && b==0) { puts("1"); return; }
	if (b==0) { puts("no solution"); return; }
	ll m=ceil(sqrt(p)); ll now=1; mp[b]=0;
	rep(i,1,m) now=(now*a)%p,mp[(b*now)%p]=i;
	ll t=pow(a,m); now=1;
	rep(i,1,m){
		now=(now*t)%p;
		if (mp[now]) { printf("%lld\n",i*m-mp[now]); return; }
	}
	puts("no solution");
}

ll exbsgs(){
	if (b==1) return 0;
	ll t,d=1,k=0;
	while ((t=gcd(a,p))!=1){
		if (b%t) return -1;
		k++; b/=t; p/=t; d=d*(a/t)%p;
		if (b==d) return k;
	}
	mp.clear();
	ll m=ceil(sqrt(p)),now=b; t=pow(a,m);
	rep(j,1,m) now=(now*a)%p,mp[now]=j;
	rep(i,1,m){
		d=d*t%p;
		if (mp[d]) return i*m-mp[d]+k;
	}
	return -1;
}
