//codeforces1186C
//��01��a,b��cΪa������b��ȵ��Ӵ�
//f(b,c)Ϊ������Ӧλ�ò���ȵ�λ������
//�磺f(00110,01100)=2,f(00110,11000)=4
//��f(b,c)Ϊż���ĸ���
//�ٷ���⣺���b,c��1�ĸ���ͬ��ż����f(b,c)Ϊż��
//���������ν��"��֤":
//�����㹻����£�b����d��1��c����e��1
//��1λ�ö�Ӧ������Ϊf���򲻶�Ӧ���������
//(d-f)+(e-f)=d+e-2f����2fΪż����������Ҫ
//d+eΪż��������d��eӦ��ͬ��ͬż
//ps:ʵ����ֻ����Ҫ0��1����ͬ��ż���У���һ����1
//��Ŀ���ӣ� http://codeforces.com/problemset/problem/1186/C
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000010;
int s1[maxn], s2[maxn];
char str1[maxn], str2[maxn];

int main()
{
	int len1, len2, i, j;
	scanf("%s %s", str1+1, str2+1);
	len1 = strlen(str1+1), len2 = strlen(str2+1);
	//����ǰ׺��ͳ����ż��
	//s1[i]=str1[1]^str1[2]^....^str1[i]
	//����0^0=0,���1������Ϊ������s1[i]=1
	//����s[i]=0; 
	for(i=1;i<=len1;i++)
		s1[i] = (str1[i]-'0')^s1[i-1];
	for(i=1;i<=len2;i++)
		s2[i] = (str2[i]-'0')^s2[i-1];
	int ans = 0;
	for(i=len2;i<=len1;i++)
		if(!(s2[len2]^s1[i]^s1[i-len2]))++ans;
	printf("%d\n", ans);
	return 0;
}
