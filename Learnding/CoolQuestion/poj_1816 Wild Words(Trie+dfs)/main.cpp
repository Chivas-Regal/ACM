//trie树+dfs
//有n个模式串，m个字符串，问对于每个字符串，能匹配
//那些模式串
//对模式串建字典树(不要对字符串建树，时间复杂度太高)
//然后对于每个字符串，在树上进行匹配，并记录能匹配到的
//模式串
//注意：字符串匹配到末尾不能直接返回，还要判断树的
//后面是否还有*号的结点
//如数据1 1 the* the
//如果直接返回则会输出Not match
//题目链接： http://poj.org/problem?id=1816
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1020;
struct node{
	vector<int> ed;
	node *nex[28];
};
node *root;
int vis[100020];
node *creat();
int getid(char ch);
void Insert(char str[], int id);
void dfs(node *p, int step, int len, char str[]);

int main()
{
	int n, m, i, j;
	char ins[50], str[12];
	root = creat();
	scanf("%d %d", &n, &m);
	//对模式串建字典树 
	for(i=0;i<n;i++){
		scanf(" %s", str);
		Insert(str, i);
	}
	for(i=0;i<m;i++){
		scanf(" %s", ins);
		int len = strlen(ins);
		memset(vis, 0, sizeof(vis));
		dfs(root, 0, len, ins);
		int num = 0;
		for(j=0;j<n;j++){
			if(!vis[j])continue;
			if(num)printf(" ");
			num++;
			printf("%d", j);
		}
		if(!num)printf("Not match");
		printf("\n");
	}
	return 0;
}

node *creat()
{
	node *p = new node;
	for(int i=0;i<28;i++)
		p->nex[i] = NULL;
	return p;
}

void Insert(char str[], int id)
{
	node *p = root;
	for(int i=0;str[i];i++)
	{
		int x = getid(str[i]);
		if(p->nex[x] == NULL)
			p->nex[x] = creat();
		p = p->nex[x];
	}
	(p->ed).push_back(id);
}

void dfs(node *p, int step, int len, char str[])
{
	if(!str[step]){
		for(int i=0;i<p->ed.size();i++)
		vis[p->ed[i]] = 1;
		//如果后面有*号，则可以继续匹配
		//因为*可以代表0个字符 
		if(p->nex[27]!=NULL)
			dfs(p->nex[27], step, len, str);
		return;
	}
	if(p->nex[str[step]-'a']!=NULL){
		dfs(p->nex[str[step]-'a'], step+1, len, str);
	}
	if(p->nex[26]!=NULL)
		dfs(p->nex[26], step+1, len, str);
	if(p->nex[27]!=NULL){
		//依次暴力*代表n个字符的情况，最多能
		//匹配到串尾 
		for(int i=0;i+step<=len;i++)
			dfs(p->nex[27], step+i, len, str);
	}
	
		
}

int getid(char ch){
	if(ch == '?')return 26;
	else if(ch == '*')return 27;
	else return ch-'a';
}
