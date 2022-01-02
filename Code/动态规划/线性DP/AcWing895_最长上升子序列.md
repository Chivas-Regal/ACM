# 🔗
<a href="https://www.acwing.com/problem/content/897/"><img src="https://img-blog.csdnimg.cn/20210617171842630.png"></a>

<details>
  <summary align="center">查看题解</summary>
           
# 💡
数据量1000，可以用n^2的复杂度去解  
在上升子序列中，考虑每一位都必须比前面那一位要大  
我们设置dp[i]表示从第1位到第i位的最长上升子序列  
所以我们在枚举每一位(设为a[i])的时候  
都利用前面的dp最优解去查一下  
如果有一位(设为a[j])的值小于a[i]  
那么我们完全可以把$a[i]$放到a[j]后面，得到的这一种子序列dp[i]=dp[j]+1  
时间复杂度：O(n^2)  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1005;

int a[N];
int dp[N];
int res;

int main(){
    int n; read(n);
    for(int i = 1, x; i <= n; i ++)  read(a[i]);
    for(int i = 1; i <= n; i ++){ dp[i] = 1;//初始化为1，因为自己本身一个数就是一个LIS
        for(int j = 1; j < i; j ++) if(a[j] < a[i]) dp[i] = MAX(dp[j] + 1, dp[i]);//如果前面的某一位小于当前的这一位，完全可以把这一位接到前面那一位后面
        res = MAX(res, dp[i]);//维护一下最大答案
    }write(res);
    return 0;
}
```
