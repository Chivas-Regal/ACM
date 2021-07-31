# 🔗
https://pintia.cn/problem-sets/1384757951243542528/problems/1384758301778305038

# 💡
使用STL库函数快速模拟栈的存储过程


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#define G 10.0
#define LNF 1e18
#define eps 1e-6
#define PI acos(-1.0)
#define ll long long
#define INF 0x7FFFFFFF
#define Regal exit(0)
#define Chivas int main()
#define pb(x) push_back(x)
#define SP system("pause")
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define IOS ios::sync_with_stdio(false)
#define mm(a, b) memset(a, b, sizeof(a))
#define each_cass(cass) for (cin>>cass; cass; cass--)
#define test(a) cout << "---------" << a << "---------" << '\n'
 
using namespace std;

inline void solve(){
    int n;
    cin>>n;
    vector<int>vec;
    vector<int>stvc;
    //priority_queue<int>up;
    //priority_queue<int,vector<int>,greater<int> >down;
    while(n--){
        string s;
        cin>>s;
        if(s=="Pop"){
            if(vec.size()==0){
                cout<<"Invalid"<<endl;
            }else{
                cout<<vec.back()<<endl;
                int id = lower_bound(stvc.begin(),stvc.end(),vec.back())-stvc.begin();
                stvc.erase(stvc.begin()+id,stvc.begin()+id+1);
                vec.pop_back();
            }
        }else if(s=="Push"){
            int x;
            cin>>x;
            vec.push_back(x);
            if(stvc.size()){
                if(x>=stvc[stvc.size()-1]) stvc.push_back(x);
                else{
                    int id=lower_bound(stvc.begin(),stvc.end(),x)-stvc.begin();
                    stvc.insert(stvc.begin()+id,x);
                }
            }
            else{
                stvc.push_back(x);
            }
        }else{
            if(vec.size()==0){
                cout<<"Invalid"<<endl;
                continue;
            }else{
                if(stvc.size() & 1) cout<<stvc[stvc.size()/2]<<endl;
                else cout<<stvc[stvc.size()/2-1]<<endl;
            }
        }
    }
}

Chivas{
    solve();
    Regal;
}
```
