# 🔗
<a href="https://codeforces.com/contest/1594/problem/E1"><img src="https://i.loli.net/2021/10/09/D1sUwZuREFK5rkV.png"></a>

# 💡
首先应该能很快想到，只有祖先节点有6种颜色可以选，那么对于每个有父节点的节点，他们都只能选四个  
一共有<img src="https://latex.codecogs.com/svg.image?2^k-1" title="2^k-1" />个节点  
那么答案公式就是<img src="https://latex.codecogs.com/svg.image?6\times&space;4^{2^k-2}" title="6\times 4^{2^k-2}" />  
  
此时k不过60所以我们也没有必要用快速幂求指数  
如果非要用的话，模数要选择<img src="https://latex.codecogs.com/svg.image?10^9&plus;6" title="10^9+6" />，因为根据欧拉定理，指数取模时在<img src="https://latex.codecogs.com/svg.image?gcd(up,&space;mod)=1" title="gcd(up, mod)=1" />时要取<img src="https://latex.codecogs.com/svg.image?\phi(mod)" title="\phi(mod)" />

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int mod = 1e9 + 7;

inline ll ksm ( ll a, ll b ) {
	ll res = 1;
	while ( b ) {
		if ( b & 1 ) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int main () {
	ll n; cin >> n;
	cout << 6 * ksm(4, (1ll << n) - 2) % mod << endl;
        return 0;
}
```
