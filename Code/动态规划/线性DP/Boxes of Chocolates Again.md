# 🔗
https://vjudge.net/problem/UVA-10590

# 💡
本题是一道经典的DP题目  
我们可以用dp[i][j] 表示在最大的数不超过 j 的前提下，形成了和为 i 的方案数目  
那么构建出 dp[i][j] ，我们可以通过两种情况获得：  
1.最后一个数不超过j-1，即dp[i][j - 1]  
2.最后一个数等于j，即dp[i - j][j]  
那么得到状态转移方程：dp[i][j] = dp[i][j - 1] + dp[i - j][j]  
由于我们是以前面那一维实现的，所以构造出滚动数组剪掉后面一维从而压缩空间即可  

PS：数据过大，使用高精或者java、python大数库（逃  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```java
import java.math.BigInteger;
import java.util.*;

public class Main {
        public static void main(String[] args) {
                int N = 5005;
                Scanner input = new Scanner(System.in);
                BigInteger[] dp = new BigInteger[N];

                dp[0] = BigInteger.ONE;
                for ( int i = 1; i < N; i ++ ) dp[i] = BigInteger.ZERO;
                for ( int j = 1; j < N; j ++ ) {
                        for ( int i = j; i < N; i ++ ) dp[i] = dp[i].add(dp[i - j]);
                }

                while( input.hasNext() ) System.out.println(dp[input.nextInt()]);
        }
}

```




