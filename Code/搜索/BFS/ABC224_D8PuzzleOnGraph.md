# 🔗
<a href="https://atcoder.jp/contests/abc224/tasks/abc224_d?lang=en"><img src="https://i.loli.net/2021/10/24/l8aiYwO6rHdM1E9.png"></a>

# 💡
首先图上点个数只有9个，那么就模拟搜一下  
每次可以交换空位置和它相邻的节点  
那么按这种方式搜，记录状态保证不会重复搜索，看看能不能生成一个123456789  
最多也就9!次  
DFS太深了扛不下，使用BFS

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int n;
struct Egde {
        int nxt, to;
} edge[100];
int head[100], cnt;
map<string, int> num;
queue<string> que;



inline void add_Edge ( int from, int to ) {
        edge[ ++ cnt ] = { head[from], to };
        head[from] = cnt;
}

int main () {
        ios::sync_with_stdio(false);
        for ( int i = 0; i < 100; i ++ ) head[i] = -1;
        cin >> n;
        for ( int i = 0, x, y; i < n; i ++ ) {
                cin >> x >> y; x --, y --;
                add_Edge ( x, y );
                add_Edge ( y, x );
        }
        string s = "999999999";
        for ( int i = 1, x; i <= 8; i ++ )
                cin >> x, x --,
                s[x] = i + '0';
        que.push(s);
        num[s] = 0;
        while ( que.size() ) {
                s = que.front(); que.pop();
                if ( s == "123456789" ) break;
                int x; for ( int i = 0; i < 9; i ++ ) if ( s[i] == '9' ) x = i;
                for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                        int to = edge[i].to; 
                        string t = s;
                        swap ( t[x], t[to] ); 
                        if ( !num[t] )  
                                que.push(t), 
                                num[t] = num[s] + 1; 
                }
        }
        if ( !num.count("123456789") ) cout << "-1" << endl;
        else                           cout << num["123456789"] << endl;
}
```
