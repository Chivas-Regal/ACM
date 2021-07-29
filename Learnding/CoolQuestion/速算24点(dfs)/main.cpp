//DFS
//������+��-��*��/���ֲ����Լ����ţ���next_permutation����
//������������Ȼ�������� 
//http://acm.hdu.edu.cn/showproblem.php?pid=1427
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
int a[9], ans;
void dfs(int sum, int nex, int t);
 
int main()
{
    int i, l;
    char str[1020];
    while(gets(str))
    {
        ans = l = 0;
        //���������ĸ��ת��Ϊ���� 
        for(i=0;str[i];i++)
        {
            if(str[i] == 'A')
                a[l++] = 1;
            else if(str[i] == '1')
                a[l++] = 10;
            else if(str[i] == 'J')
                a[l++] = 11;
            else if(str[i] == 'Q')
                a[l++] = 12;
            else if(str[i] == 'K')
                a[l++] = 13;
            else if(str[i] >= '2' && str[i] <= '9')
                a[l++] = str[i]-'0';
        }
        //����ȫ���� 
        sort(a, a+4);
        do
        {
            dfs(a[0], a[1], 1);
        }while(next_permutation(a, a+4));
        if(ans)
            printf("Y\n");
        else
            printf("N\n");
    }
    return 0;
 }
//sum����ǰֵ��nex��ʾ������ֵ 
void dfs(int sum, int nex, int t)
{
    if(sum <0 || nex<0)return;
    if(t == 3)
    {
        if(sum + nex == 24 || sum-nex==24 || sum*nex == 24)
            ans = 1;
        if(nex != 0 && sum%nex==0 && sum / nex == 24)
            ans = 1;
        return;
    }
    //��������->�ͽ�nex�������в������ӽ�ȥ 
    dfs(sum+nex, a[t+1], t+1);
    dfs(sum-nex, a[t+1], t+1);
    dfs(sum*nex, a[t+1], t+1);
    if(nex!=0 && sum%nex==0)
        dfs(sum/nex, a[t+1], t+1);
    //������->�ͽ�Ŀǰ������nex�н��в��� 
    dfs(sum, nex+a[t+1], t+1);
    dfs(sum, nex-a[t+1], t+1);
    dfs(sum, nex*a[t+1], t+1);
    if(a[t+1] != 0 && nex % a[t+1] == 0)
        dfs(sum, nex/a[t+1], t+1);
}
