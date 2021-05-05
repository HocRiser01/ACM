#include<cstdio>
#include<vector>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/assoc_container.hpp>

struct Cmp{
	int operator() (const int &a,const int &b) { return a>b; }
};

using namespace std;
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<int,Cmp,pairing_heap_tag > Que;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Tree;

Que a,d;
Que::point_iterator p=a.push(0);
Tree b,c;
Tree::const_iterator it;

int main(){

	puts("");
	puts("---------using namespace __gnu_pbds---------");
	puts("");
	
	puts("---Include<ext/pb_ds/assoc_container.hpp> for 'tree'---");
	puts("");
	
	it=b.insert(200).first;
	puts("Insert(int x) returns pair<iterator,bool>");
	printf("b.insert(200).first:%d\n\n",*it);
	
	b.insert(100);
	puts("Find_by_order(int x) returns the x+1 least element const_iterator");
	printf("b(100,200).find_by_order(1):%d\n\n",*b.find_by_order(1));
	
	puts("Order_of_key(int x) returns the rank-1 of element'x'");
	printf("b(100,200).order_of_key(100):%d\n\n",b.order_of_key(100));
	
	b.split(100,c);
	puts("Split(int key,Tree C)clear C at first,and move the element larger than key into C");
	printf("b(100,200).split(100,c),     c.begin():%d\n\n",*c.begin());
	
	puts("---Include<.../priority_queue.hpp> for 'priority_queue'---");
	puts("");
	
	puts("push(int x) returns the inserted point_iterator");
	printf("a.push(0) , *p=*a.push(0):%d\n\n",*p);
	
	a.push(1); a.push(3); a.modify(p,2);
	puts("Modify(iterator,int) change the value of (*p),this heap is maintained automatically");
	printf("a.modify(p,2) , *p:%d\n\n",*p);
	
	a.erase(p);
	puts("Erase(iterator) delete this element,this iterator dies");
	printf("a.erase(p) , a.top():%d\n",a.top());
	a.pop(); printf("a.pop() , a.top():%d\n\n",a.top());
	
	d.push(-1); a.join(d);
	puts("a.join(d) join d into a , and then maintain a,clear d");
	printf("d.push(-1) , a.join(d) ,a.top():%d\n\n",a.top());
	
	puts("----Other functions are not normally used in contests----");
	return 0;
}
