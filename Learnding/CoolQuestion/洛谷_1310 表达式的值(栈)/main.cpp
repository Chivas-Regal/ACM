//栈+dp
//有两种运算符，和括号，求有多少种方案可以是式子的值为0
//和模拟四则运算一样，可以利用栈来解决这个问题，括号可以
//利用递归来解决，对于*号和+号，利用公式可以递推一下当前部分
//的值，直到递归结束，只剩下一个值，就是结果 
//其实可以全部利用栈来做，更清晰方便
//题目链接：https://www.luogu.org/problem/P1310 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 400100;
const int mod = 10007;
struct node{
	LL x, y;
	node(){}
	node(LL a, LL b):x(a),y(b){}
};
int i, l;
char str[maxn], s[maxn];
node solve();

int main()
{
	int j;
	scanf("%d", &l);
	if(l == 0)printf("1\n");
	else{
		scanf(" %s", str);
		node p = solve();
		printf("%lld\n", p.x);
	}
	return 0;
}

node solve()
{
	//dbg(i);
	stack<node> st;
	//如果当前首位是括号，则向下递进，并将返回的结果放入栈 
	if(str[i] == '(')
		++i, st.push(solve());
	//如果当前是+或*，则放入计数结点 
	else
		st.push(node(1LL, 1LL));
	while(i<l)
	{
		//如果是符号，如果符号右边有括号，则补括号里的式子的值
		//如果没有可以直接补一个新结点 
		if(str[i] == '+' && str[i+1] != '(')
			st.push(node(1LL,1LL)), i++;
		else if(str[i] == '*' && str[i+1] != '(')
		{
			node q, p = st.top();st.pop();
			q.x = q.y = 0;
			q.x = (2*p.x+p.y)%mod;
			q.y = p.y%mod;
			st.push(q);
			i++;
		}
		else if(str[i] == '*' && str[i+1] == '(')
		{
			int k = i; 
			i+=2;st.push(solve());
			node p = st.top();st.pop();
			node q = st.top();st.pop();
			node z;
			z.x = p.x*q.x%mod+p.x*q.y%mod+p.y*q.x%mod;
			z.y = p.y*q.y%mod;
			st.push(node(z.x%mod, z.y%mod));
		}
		else if(str[i] == '(')
			++i, st.push(solve());
		else if(str[i] == ')'){
			++i;break;
		}
		else i++;
	}
	//st内存放所有数进行+运算，求计算结果 
	while(st.size()>1){
		node p = st.top();st.pop();
		node q = st.top();st.pop();
		//printf("%lld %lld %lld %lld\n", p.x, p.y, q.x, q.y);
		node z;
		z.x = p.x*q.x%mod;
		z.y = p.x*q.y%mod+p.y*(q.x+q.y)%mod;
		st.push(node(z.x, z.y%mod)); 
	}
	//printf("I:%d %lld %lld\n", i, st.top().x, st.top().y);
	return st.top();
}

/*
20
(+(*))+(+(*))+(+(*))
13
+(*(+(*)+)+)+
9
+(*(*)+)+
*/
