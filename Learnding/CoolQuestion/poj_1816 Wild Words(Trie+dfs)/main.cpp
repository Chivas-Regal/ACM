//trie��+dfs
//��n��ģʽ����m���ַ������ʶ���ÿ���ַ�������ƥ��
//��Щģʽ��
//��ģʽ�����ֵ���(��Ҫ���ַ���������ʱ�临�Ӷ�̫��)
//Ȼ�����ÿ���ַ����������Ͻ���ƥ�䣬����¼��ƥ�䵽��
//ģʽ��
//ע�⣺�ַ���ƥ�䵽ĩβ����ֱ�ӷ��أ���Ҫ�ж�����
//�����Ƿ���*�ŵĽ��
//������1 1 the* the
//���ֱ�ӷ���������Not match
//��Ŀ���ӣ� http://poj.org/problem?id=1816
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
	//��ģʽ�����ֵ��� 
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
		//���������*�ţ�����Լ���ƥ��
		//��Ϊ*���Դ���0���ַ� 
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
		//���α���*����n���ַ�������������
		//ƥ�䵽��β 
		for(int i=0;i+step<=len;i++)
			dfs(p->nex[27], step+i, len, str);
	}
	
		
}

int getid(char ch){
	if(ch == '?')return 26;
	else if(ch == '*')return 27;
	else return ch-'a';
}
