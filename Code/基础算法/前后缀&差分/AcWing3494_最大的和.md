# 🔗
<a href="https://www.acwing.com/problem/content/3496/"><img src="https://img-blog.csdnimg.cn/2021061811560530.png"></a>

# 💡
我们想获取区间内选了之后的sum变化，即选取能让答案增加最多的区间  
因此我们就需要两个数值来对比  
  
可以使用两个前缀和  
一个是只记录选了1的数的前缀和，一个是记录全选的前缀和  
两个前缀和在k的区间内的差值，就是这k个数从只选1到全选之后所能做出的贡献  
记录贡献最大值，然后加上第一个前缀和[n]  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e5 + 10;

ll n, k;
ll a[N], b[N], sum1[N], sum2[N];
ll res;

int main(){
    read(n); read(k);
    for(int i = 1; i <= n; i ++) read(a[i]);
    for(int i = 1; i <= n; i ++) read(b[i]), 
    	sum1[i] = sum1[i - 1] + a[i] * b[i], 
    	sum2[i] = sum2[i - 1] + a[i];

    for(int i = k; i <= n; i ++) 
    	res = MAX(res, (sum2[i] - sum2[i - k]) - (sum1[i] - sum1[i - k]));
    res += sum1[n];
    
    write(res);
    return 0;
}
```
