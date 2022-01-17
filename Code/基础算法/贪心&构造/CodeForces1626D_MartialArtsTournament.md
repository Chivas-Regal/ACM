# 🔗
<a href="https://codeforces.com/contest/1626/problem/D"><img src="https://s2.loli.net/2022/01/18/knzbK32pWmPlXBZ.png"></a>

# 💡
我们对  <img src="https://latex.codecogs.com/svg.image?\inline&space;1\rightarrow&space;n" title="\inline 1\rightarrow&space;n" /> 的所有体重记录一个出现的次数  <img src="https://latex.codecogs.com/svg.image?\inline&space;cnt" title="\inline cnt" />   
然后枚举第一段和第二段的期望长度  <img src="https://latex.codecogs.com/svg.image?\inline&space;l1,l2" title="\inline l1,l2" />   
遍历  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 到  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" /> 看看每段在不超过自身预期的前提下，最多能存在多少个运动员  
预期和实际的差即是我们要扩招的人数  
对于第三段，我们看看枚举完 <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  后面的人中，向上的第一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;2" title="\inline 2" /> 的整数幂，就是第三段预期的人数  
这三个相加，对于每一个枚举的前两段长度，我们维护一下我们要扩招的人的最小值即可    

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int cnt[200005];
int n;
 
inline int calc ( int L1, int L2 ) { int L3 = 1; // 预期人数
        int res = 0;
        
        int i = 1, sum; // 实际人数
 
        sum = 0;
        for (; i <= n; i ++ ) {
                if ( sum + cnt[i] > L1 ) break;
                sum += cnt[i];
        }
        res += L1 - sum;
        sum = 0;
        for (; i <= n; i ++ ) {
                if ( sum + cnt[i] > L2 ) break;
                sum += cnt[i];
        }
        res += L2 - sum;
        sum = 0;
        for (; i <= n; i ++ ) sum += cnt[i];
        while ( L3 < sum ) L3 <<= 1;
        res += L3 - sum;
 
        return res;
}
 
inline void Solve () {
        scanf("%d", &n);
        for ( int i = 1; i <= n; i ++ ) cnt[i] = 0;
        for ( int i = 0; i < n; i ++ ) {
                int x; scanf("%d", &x);
                cnt[x] ++;
        }
        int res = 0x3f3f3f3f;
        for ( int len1 = 1; len1 <= n; len1 <<= 1 ) {
                for ( int len2 = 1; len2 <= n; len2 <<= 1 ) {
                        res = min(res, calc(len1, len2));
                }
        }
        printf("%d\n", res);
}
 
int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
