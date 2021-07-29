//dp
//��������Ȼ˵�������ޣ���Ϊ��������ĳ������С������
//�ĳ��Ϳ�����ʵ����ֻ��Ҫ����������ͬ������������
//�ͻ�Ϊ01���������ˡ�
//n�����30����100Ӧ�þ��㹻����ʵ����1020�Ŀռ�
//��֪Ϊ���Ի�wrong answer 
//http://acm.hdu.edu.cn/showproblem.php?pid=1069
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#define INF 0x3f3f3f3f
  
using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
typedef struct
{
	int x, y, z;
}node;
node p[5020];
int num; 
void add(int x, int y, int z);
bool cmp(node a, node b);

int main()
{
    int n, i, j, z = 1, maxx, dp[5020];
    while(scanf("%d", &n), n!=0)
    {
    	memset(dp, 0, sizeof(dp));
    	num = maxx = 0;
    	for(i=0;i<n;i++)
    	{
    		int a[4]; 
    		scanf("%d %d %d", &a[1], &a[2], &a[3]);
    		//�����ݽ������򣬱�֤�����ڵ��ڿ� 
    		sort(a+1, a+4);
    		add(a[1], a[2], a[3]);
    		add(a[2], a[3], a[1]);
    		add(a[1], a[3], a[2]);
		}
		//���������򣬳��Ƚϴ�Ŀ�ǰ 
		sort(p, p+num, cmp);
    	for(i=0;i<num;i++)
    	{
    		//ֻ����i���Ϊp[i].z
    		dp[i] = p[i].z;
    		for(j=i-1;j>=0;j--)
    		{
    			//����˷�����Էŵ�ǰ��ķ����� 
    			if(p[i].x < p[j].x && p[i].y < p[j].y)
    			{
    				//j��i��ʼ�𽥼�С��dp[j]Ϊֻ���ǵ�
					//��j����������ֵ������ܷ����磬��
					//�Ƚ�����ֵ�ͷ��ڴ������ֵ 
    				dp[i] = max(dp[i], dp[j]+p[i].z);
				}
			}
			maxx = max(maxx, dp[i]);
		}
		printf("Case %d: maximum height = %d\n", z, maxx);
		z++;
	}
	return 0;
}

void add(int x, int y, int z)
{
	p[num].x = x;
	p[num].y = y;
	p[num].z = z;
	num++;
}

bool cmp(node a, node b)
{
	if(a.x == b.x)
		return a.y > b.y;
	return a.x > b.x;
}
