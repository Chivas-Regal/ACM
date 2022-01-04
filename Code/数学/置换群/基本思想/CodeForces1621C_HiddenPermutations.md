# 🔗
<a href="https://codeforces.com/contest/1621/problem/C"><img src="https://s2.loli.net/2022/01/04/xvuWZqjySsNdp4B.png"></a>

# 💡
这个题里面有一个置换群思想的应用  
就是置换群本身的**不交轮换积**  
  
即反复的  <img src="https://latex.codecogs.com/svg.image?\inline&space;q=q_{p_i}" title="\inline q=q_{p_i}" /> 下来，每一列都会进行循环，并形成一条在  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;\begin{pmatrix}x_1&x_2&\dots&x_3&x_4\\x_a&x_b&\dots&x_c&x_d\end{pmatrix}" title="\inline \begin{pmatrix}x_1&x_2&\dots&x_3&x_4\\x_a&x_b&\dots&x_c&x_d\end{pmatrix}" />   
 下的  <img src="https://latex.codecogs.com/svg.image?\inline&space;x_1\rightarrow&space;x_a\rightarrow\dots\rightarrow&space;x_e\rightarrow&space;x_1" title="\inline x_1\rightarrow&space;x_a\rightarrow\dots\rightarrow&space;x_e\rightarrow&space;x_1" /> 这样的链  
 而其中表示的就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;p[x_1]=x_a,p[x_a]=\dots,p[x_e]=x_1" title="">  
   
所以我们设置一个 `set` 存储我们还不知道对应谁的数  
每次从 `*set.begin()` 这一列开始问我们就能得到一条有 `*set.begin()` 的关系链  
直到把所有链问完，我们的结果也就构造好了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int res[10005];

inline void Solve () {
        int n; cin >> n;
        set<int> st; for ( int i = 1; i <= n; i ++ ) st.insert(i);

        while ( st.size() ) {
                int ask = *st.begin();
                vector<int> lst; lst.push_back(ask);
                
                while ( 1 ) { // 先推到 ask 这个数
                        cout << "? " << ask << endl; cout.flush();
                        int rd; cin >> rd;
                        if ( rd == ask ) break;
                }
                while ( 1 ) { // 从这个数开始存链
                        cout << "? " << ask << endl; cout.flush();
                        int rd; cin >> rd; 
                        lst.push_back(rd);
                        if ( rd == ask ) break;
                }
                for ( int i = 0; i < lst.size() - 1; i ++ ) {
                        res[lst[i]] = lst[i + 1];
                        st.erase(lst[i]);
                }
        }
        cout << "!";
        for ( int i = 1; i <= n; i ++ ) cout << " " << res[i]; cout << endl; cout.flush();
}

int main () {       
        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
