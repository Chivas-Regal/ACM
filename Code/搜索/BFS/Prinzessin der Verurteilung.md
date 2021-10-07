# 🔗
<a href="https://codeforces.com/problemset/problem/1536/B"><img src="https://img-blog.csdnimg.cn/20210607110235819.png?"></a>

# 💡
首先明白  
如果一个个字符串按顺序向后搜索查找  
我们搜到的字符串数量不会超过$26 * log_{26}(1000)$  
这是根据容斥出来的最坏情况  
  
这么看来可以用搜索，但是DFS是一条路径向后找，会有很多不必要搜的字符串  
所以我们用BFS  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
struct cmp{
        bool operator ()(string a, string b){//保证两个字符串是先按长度再按字典序排序
                if(a.size() != b.size()) return a.size() > b.size();
                return a > b;
        }
};
string in;//输入字符串
string none;//空字符串

inline void BFS(){
        priority_queue<string, vector<string>, cmp> pque;
        for(char i = 'a'; i <= 'z'; i ++) pque.push(none + i);//先都初始化为一个字符
        while(pque.size()){
                string cur = pque.top(); pque.pop();
                if(in.find(cur) == in.npos){//找不到了就输出
                        cout << cur << endl;
                        return;
                }
                for(char i = 'a'; i <= 'z'; i ++) pque.push(cur + i);
        }
}

inline void solve(){
        int n; cin >> n >> in;
        BFS();
}

CHIVAS_{
        int cass;
        EACH_CASE(cass){
                solve();
        }
        _REGAL;
}
```
