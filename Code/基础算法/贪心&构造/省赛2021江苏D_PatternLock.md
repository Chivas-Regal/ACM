# 🔗
<a href="https://codeforces.com/gym/103495/problem/D"><img src="https://s2.loli.net/2022/01/08/WZ9tnXdUjiHbmG1.png"></a>

# 💡
从样例获得启发  
我们可以  <img src="https://latex.codecogs.com/svg.image?\inline&space;Z" title="\inline Z" /> 字形构造，但是多行翻来翻去会很麻烦，所以我们变一下  
<img src="https://s2.loli.net/2022/01/08/HJnDCWoTd9LlcYE.jpg">  
横向就这样画  
那么可以看到这种画法是不看列数的，但是行数要满足偶数  
而我们对于列数是偶数的，可以把这种画法竖过来就可以了  
所以行和列有一个是偶数我们就可以按这种画法把图填满  
  
那么问题来了，如果都是奇数的话  
那么我们可以思考一下，这种画法横着摆不看列数，竖着摆不看行数，而他们也同时都受到偶数的限制  
也就是说，我们先横着摆，留三行从左到右竖着摆，那么最后还是会摆不完  
那么我们依旧可以留三行，那么就在左下角形成了一个边长为  <img src="https://latex.codecogs.com/svg.image?\inline&space;3" title="\inline 3" /> 的正方形点阵，这个随便造就可以了  
  
例如：  
<img src="https://s2.loli.net/2022/01/08/Ra1suYGgLP329tO.jpg">  
可以看出，右下角这么搞是安全的

>注意：一条线不能穿过已经走过的点  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int main () {
        ios::sync_with_stdio(false);
        int n, m; cin >> n >> m;
        if ( n == 1 && m == 1 ) { // 特判
                cout << 1 << " " << 1 << endl;
                return 0;
        } 
        if ( (n & 1) && (m & 1) ) {
                for ( int i = 1; i <= n - 3; i += 2 ) { // 横 Z
                        cout << i << " " << 1 << endl;
                        for ( int j = 1; j < m; j ++ ) { 
                                cout << i << " " << j + 1 << endl << i + 1 << " " << j << endl;
                        }
                        cout << i + 1 <<  " " << m << endl;
                }
                // 3*3点阵
                cout << n - 2 << " " << m - 2 << endl;
                cout << n - 1 << " " << m - 1 << endl;
                cout << n - 2 << " " << m - 1 << endl;
                cout << n - 1 << " " << m << endl;
                cout << n - 2 << " " << m << endl;
                cout << n << " " << m - 1 << endl;
                cout << n << " " << m << endl;
                cout << n - 1 << " " << m - 2 << endl;
                cout << n << " " << m - 2 << endl;
                // 竖 Z
                for ( int j = m - 3; j >= 1; j -= 2 ) {
                        cout << n - 2 << " " << j << endl;
                        cout << n - 1 << " " << j << endl;
                        cout << n - 2 << " " << j - 1 << endl;
                        cout << n << " " << j << endl;
                        cout << n - 1 << " " << j - 1 << endl;
                        cout << n << " " << j - 1 << endl;
                }
        } else if ( n & 1 ) { // 竖 Z
                for ( int j = 1; j <= m; j += 2 ) {
                        cout << 1 << " " << j << endl;
                        for ( int i = 1; i < n; i ++ ) {
                                cout << i + 1 << " " << j << endl;
                                cout << i << " " << j + 1 << endl;
                        }
                        cout << n << " " << j + 1 << endl;
                }
        } else { // 横 Z
                for ( int i = 1; i <= n; i += 2 ) {
                        cout << i << " " << 1 << endl;
                        for ( int j = 1; j < m; j ++ ) { 
                                cout << i << " " << j + 1 << endl << i + 1 << " " << j << endl;
                        }
                        cout << i + 1 <<  " " << m << endl;
                }
        }
}
```
