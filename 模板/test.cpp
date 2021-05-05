//1:
for i in $(seq 1 10); do
echo ----------$i------------
cp a$i.in a.in
time ./a
if !(diff -w a.out a$i.ans); then echo WA!!!; exit; fi
read
done

//2:
g++ std.cpp -o std -g -Wall
g++ brute.cpp -o brute -g -Wall
fpc -g make
while true; do
echo -----------------
./make
time ./std<std.in>std.out
time ./brute<std.in>brute.out
if !(diff -w std.out brute.out); then echo WA!!!; exit; fi
read
done

//3:
int main(int argc,char* argv[]){}
//argc非传入参数，它存储一共传入了几个字符串参数。
//e.g. time ./sy 1 3 5 7
//则argc=5,argv[0]="./sy",argv[1]="1",argv[2]="3",argv[3]="5",argv[4]="7".

//4:
#include<cstdio>
#include<algorithm>
#include<sys/timeb.h>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

void insd(){
	struct timeb tp; ftime(&tp); 
	srand(tp.time*1000+tp.millitm); 
}

int sj(int l,int r){ return rand()%(r-l+1)+l; }

int main(){
	freopen("a.in","w",stdout);
	insd(); int n=sj(1,100); printf("%d\n",n);
	return 0;
}

//5:
#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for (int i=l; i<=r; i++)
using namespace std;

int main(){
	system("g++ make.cpp -o make -g -Wall");
	system("g++ a.cpp -o a -g -Wall");
	system("g++ b.cpp -o b -g -Wall");
	do{
		system("make.exe");
		system("a.exe");
		system("b.exe");
	}while (!system("fc a.out b.out"));
	return 0;
}

//6:
@echo off
g++ a.cpp -o a -g -Wall -std=c++11
g++ a2.cpp -o a2 -g -Wall -std=c++11
g++ make.cpp -o make -g -Wall -std=c++11
:loop
	make.exe
	a.exe
	a2.exe
	fc a.out a2.out
	if not errorlevel 1 goto loop
echo WA!!!
pause