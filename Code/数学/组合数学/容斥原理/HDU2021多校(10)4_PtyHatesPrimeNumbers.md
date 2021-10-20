# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7080"><img src="https://i.loli.net/2021/10/20/eH9yNx3BRCOqoMV.png"></a>

# 💡
问题可以转化一下，由于自己也是自己的因数，所以就是问[1, n]内有多少个数不是前k个素数的倍数  
这类计数问题很快联想到容斥  
  
16个数，但是有1e5组数据  
那么2^16 * 1e5就很难办了  
但是2^8还是很好过的，那么可以对质数的组合乘积情况打表vec  
对于前k个质数，k<=8，我们打1~8的容斥表  
对于k>8，我们打9~16的容斥表  
(由于容斥表中含1，即都不选，那么我们不需要使用n-vec[i]来计算不是前k素数倍数的个数）   
  
**k<=8**  
我们直接就容斥地`res +-= n / vec[i]`就行了  
**k>8**  
我们还要做一些处理  
前八个素数的乘积是9699690  
有个显然的性质就是：如果一个数x不是前八个素数的倍数，x%9699690也不会是前八个素数的倍数（同余  
而9699690也不是非常大，所以我们可以继续预处理一下9699690以内不是前八个数的倍数的个数（前缀地处理  
然后我们可以利用我们处理出来的信息，容斥x=“在n以内不是vec[i]的倍数的数中，也不是前8个数的倍数的情况”  
  
这里我们可以采用枚举倍数的方式  
n / vec[i]表示的是n以内从1开始的vec[i]的倍数  
对这些倍数，[1, ..]相当于拆解完vec[i]这个质因数之后残余的数，且从1开始连续  
这些数中我们可以求一下N的周期个数，每个周期有sum[N]个满足条件的数    
然后剩余n / vec[i] % N，这里面有sum[n / vec[i] % N]个满足条件的数  
  
容斥这些数就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 9699690;
int prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}; // 前16个质数
vector<ll> a[20], b[20]; // 01枚举后，奇数个数的乘积情况和偶数哥的乘积情况
int sum[N + 10]; // sum[i] = [1, i]中不能被前八个质数整除的个数

inline void DFS ( int id, ll res, int cnt, int k ) { // 构造容斥数组（塞入1，不用取反数了
        if ( id > k ) {
                if ( cnt & 1 ) a[k].emplace_back(res);
                else           b[k].emplace_back(res);
                return; 
        }
        DFS ( id + 1, res * prime[id], cnt + 1, k );
        DFS ( id + 1, res,             cnt,     k );
}
inline void Pre () { // 预处理sum与容斥数组
        for ( int k = 1; k <= 16; k ++ ) {
                if ( k <= 8 ) DFS ( 1, 1, 0, k );
                else          DFS ( 9, 1, 0, k );
        }
        for ( int i = 1; i <= 8; i ++ ) for ( int j = prime[i]; j <= N; j += prime[i] ) sum[j] = 1; // 埃氏筛
        for ( int i = 1; i <= N; i ++ ) sum[i] = sum[i - 1] + (sum[i] == 0);
}
int main () {
        ios::sync_with_stdio(false); Pre();
        int cass; cin >> cass; while ( cass -- ) {
                ll n, k, res = 0;
                cin >> n >> k;
                if ( k <= 8 ) {
                        for ( auto i : a[k] ) res -= n / i; // 普通的容斥原理
                        for ( auto i : b[k] ) res += n / i;
                } else {
                        for ( auto i : a[k] ) res -= n / i / N * sum[N] + sum[n / i % N]; // 相当于枚举倍数，倍数有 n / i 个，在[1, n / i]中找N的周期与模N之后剩余的个数
                        for ( auto i : b[k] ) res += n / i / N * sum[N] + sum[n / i % N];
                }
                cout << res << endl;
        }
}
```
