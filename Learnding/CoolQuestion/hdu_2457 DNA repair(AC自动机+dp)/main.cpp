//AC�Զ���+dp
//���������ַ������ٸĶ���������ʹ�䲻����������ģʽ��
//��AC�Զ������ڵ㱣�棬Ȼ��dp[i][j]��ʾ����Ϊ�ڵ�
//i+1��λ�ô��ڽڵ�j��ʱ��������Ҫ���ļ���
//---------------------------------------------------- 
//�ο�����:https://www.cnblogs.com/HDUjackyan/p/9043255.html
//http://acm.hdu.edu.cn/showproblem.php?pid=2457
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
struct node
{
	int nex[4], fail, num;
};
node p[1010];
char str[1010];
int l, root, dp[1020][1020];
int creat();
void insert(char str[]);
void getfail();
int isn(char ch);

int main()
{
	int n, ans, i, j, k, z = 1;
	while(scanf("%d", &n), n)
	{
		l = 0;
		root = creat();
		for(i=0;i<n;i++)
		{
			char str1[50];
			scanf(" %s", str1);
			insert(str1);
		}
		getfail();
		scanf(" %s", str);
		int len = strlen(str);
		//��ʼ��dp���飬 
		for(i=0;i<=len;i++)
			for(j=0;j<l;j++)
				dp[i][j] = INF;
		dp[0][0] = 0;
		//i��ʾ���ڵ�i��λ�ã����ڵ�j���ڵ� 
		for(i=0;i<len;i++)
			for(j=0;j<l;j++)
			{	//dp[i][j]<INF��ʾ����ת�Ƶ���λ�� 
				if(dp[i][j] < INF)
				{
					//printf("\ni:%d\n", i);
					//��A��C��G��Tת�� 
					for(k=0;k<4;k++)
					{
						int nows = p[j].nex[k];
						//���ΪΣ�սڵ㣬���� 
						if(p[nows].num)continue;
						int x = isn(str[i]), add;
						//printf("x:%d %d ", x, k);
						if(x != k)add=1;
						else add=0;
						//printf("add:%d\n", add); 
						dp[i+1][nows]=min(dp[i+1][nows], add+dp[i][j]);
					}
				}
			}
		/*for(i=0;i<=len;i++)
		{
			for(j=0;j<l;j++)
				printf("%d ", dp[i][j]);
			printf("\n");
		}*/
		ans = INF;
		for(j=0;j<l;j++)
		{
			ans = min(ans, dp[len][j]);
			//printf("%d %d\n", ans, dp[len][j]);
		}
		if(ans == INF)
			printf("Case %d: -1\n", z);
		else
			printf("Case %d: %d\n", z, ans);
		z++;
	}
	return 0;
}

int isn(char ch)
{
	if(ch == 'A')
		return 0;
	else if(ch == 'C')
		return 1;
	else if(ch == 'G')
		return 2;
	else if(ch == 'T')
		return 3;
}
int creat()
{
	for(int i=0;i<4;i++)
		p[l].nex[i] = -1;
	p[l].fail = -1;
	p[l].num = 0;
	l++;
	return l-1;
}

void insert(char str[])
{
	int s = 0;
	for(int i=0;str[i];i++)
	{
		int x = isn(str[i]);
		if(p[s].nex[x] == -1)
			p[s].nex[x] = creat();
		s = p[s].nex[x];
	}
	p[s].num=1;
}

void getfail()
{
	queue<int> que;
	que.push(0);
	p[0].fail = 0;
	while(!que.empty())
	{
		int s = que.front();
		que.pop();
		for(int i=0;i<4;i++)
		{
			if(p[s].nex[i] != -1)
			{
				if(s == 0)
					p[p[s].nex[i]].fail = 0;
				else
				{
					int q = p[s].fail;
					while(q != -1)
					{
						if(p[q].nex[i] != -1)
						{
							p[p[s].nex[i]].fail = p[q].nex[i];
							break;
						}
						q = p[q].fail;
					}
					if(q == -1)
						p[p[s].nex[i]].fail = 0;
					if(q != -1 && p[p[q].nex[i]].num == 1)
						p[p[s].nex[i]].num = 1;
				}
				que.push(p[s].nex[i]);
			}
			else
				p[s].nex[i] = s==0?0:p[p[s].fail].nex[i];
		}
	}
}
