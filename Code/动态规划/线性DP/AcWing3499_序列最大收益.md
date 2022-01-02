# 🔗
<a href="https://www.acwing.com/problem/content/3502/"><img src="https://img-blog.csdnimg.cn/20210618154623284.png"></a>

<details>
  <summary align="center">查看题解</summary>
           
# 💡
是一个决策某个位置删不删的问题，所以DP可解  
我第一反应是区间DP，但是我们需要一维去记录删掉多少个元素  
所以我们用一维表示枚举的位数，一维表示删除多少个元素  
就变成了一道线性DP  
  
发现这个几乎可以用[LIS问题的方法](https://blog.csdn.net/SnopzYz/article/details/117997834?spm=1001.2014.3001.5501)写，相比较于LIS问题  
少了个大小的限制，但多了个对删除多少个元素的限制  
同时把a[i]接到a[j]后面的收益从1变成了w[a[i]][a[j]]  
数据量200，明显是让我们加一重循环去维护第二维的    
  
所以问题就转化成了一个带一点变动的LIS问题  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 210;
int w[N][N], a[N];
int dp[N][N];//dp[i][j]表示到第i位删去了j个元素后的最优解
int n, k, m;
int res;

int main(){
    read(n); read(k); read(m);
    for(int i = 1; i <= m; i ++) read(a[i]);
    for(int i = 1; i <= n; i ++) for(int j = 1; j <= n; j ++) read(w[i][j]);
    
    for(int i = 1; i <= m; i ++){			//推到了第几位
        for(int j = 0; j <= k; j ++){		//枚举到第i位删去多少个
            for(int o = 1; o < i; o ++){	//枚举第i位以前的o位，并代表 (i, o) 的元素是我们跳过的
                if(j >= i - o - 1)			//检查一下第i位要删去的这j个元素够不够跳跃 (i, o) 这么多个元素
                 	//第i位删了 o 个，所以第o个位置的状态是删去 j-(i-o+1) 个，拼到后面得到w[a[o]][a[i]]
                    dp[i][j] = MAX(dp[i][j], dp[o][j - (i - o - 1)] + w[a[o]][a[i]]),
                    res = MAX(dp[i][j], res);//维护最大值
            }
        }
    }write(dp[m][k]);
}
```
