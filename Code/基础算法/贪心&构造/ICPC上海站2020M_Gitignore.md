# 🔗
<a href="https://codeforces.com/gym/102900/problem/M"><img src="https://s2.loli.net/2022/01/02/Qnus9vBJf4zgCG1.png"></a>

# 💡
题目是给出我们  <img src="https://latex.codecogs.com/svg.image?\inline&space;n+m" title="\inline n+m" /> 个文件路径，让我们保留最后  <img src="https://latex.codecogs.com/svg.image?\inline&space;m" title="\inline m" /> 个，删掉别的所有文件需要的最少次数  
  
这就是个资源管理器，它就像一棵树，每个文件路径都是树上深度为  <img src="https://latex.codecogs.com/svg.image?\inline&space;0" title="\inline 0" /> 的点到一个叶子结点的树链  
我们可以对这条树链的每一个前缀路径都标为  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> ，默认是  <img src="https://latex.codecogs.com/svg.image?\inline&space;0" title="\inline 0" /> ，这样我们就可以确定哪些需要删哪些不能删，删掉的标记为  <img src="https://latex.codecogs.com/svg.image?\inline&space;-1" title="\inline -1" /> 即可  
  
既然要删最少的次数，我们肯定更希望删去每条  <img src="https://latex.codecogs.com/svg.image?\inline&space;0" title="\inline 0" /> 链最上面的文件夹
  
从根结点向下走是一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;DFS" title="\inline DFS" /> 的过程，而我们这里可以直接采用遍历要删掉的  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" /> 个文件的路径即可  
为  <img src="https://latex.codecogs.com/svg.image?\inline&space;0" title="\inline 0" /> 的时候意味着要删去，我们标记  <img src="https://latex.codecogs.com/svg.image?\inline&space;-1" title="\inline -1" /> 然后将计数结果  <img src="https://latex.codecogs.com/svg.image?\inline&space;+1" title="\inline +1" /> 再 `break` 即可

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void Solve () {
        int n, m; cin >> n >> m;
        
        vector<string> del;
        for ( int i = 0; i < n; i ++ ) {
                string s; cin >> s; s += "/";
                del.push_back(s);
        }

        map<string, int> statu;
        for ( int i = 0; i < m; i ++ ) {
                string s; cin >> s; s += "/";
                string fl;
                for ( int j = 0; j < s.size(); j ++ ) {
                        fl += s[j];
                        if ( s[j] == '/' ) statu[fl] = 1;
                }
        }

        int res = 0;
        for ( int i = 0; i < n; i ++ ) {
                string s = del[i];
                string fl;
                for ( int j = 0; j < s.size(); j ++ ) {
                        fl += s[j];
                        if ( s[j] == '/' ) {
                                if ( !statu[fl] ) {
                                        statu[fl] = -1;
                                        res ++;
                                        break; 
                                } else if ( statu[fl] == -1 ) {
                                        break;
                                }
                        } 
                }
        }

        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
