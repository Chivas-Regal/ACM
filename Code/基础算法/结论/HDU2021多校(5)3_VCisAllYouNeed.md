# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7014"><img src="https://i.loli.net/2021/10/14/TV1fX2RZ6wShgnI.png"></a>

# 💡
画一个图  
发现基础的二维控制在三个点以内就行  
后面每多一维其实是有给出一个边去分割  
此时也就是点数<=维度+1即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int main () {
        ios::sync_with_stdio(false);
        int cass;
        for ( cin >> cass; cass; cass -- ) {
                ll n, k; cin >> n >> k;
                if ( n - k < 2 ) cout << "Yes" << endl;
                else cout << "No" << endl;
        }
}
```
