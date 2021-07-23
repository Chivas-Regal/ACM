# Question : 如何判断一个数组是否单调
<b>Answer :</b>   
用两个单调栈（一个递增一个递减）操作一下数组  
然后判断是否有一个满足 “size = n” 即可
```cpp
int n = inputInt();
int a[n + 10], Want = 1;
for ( int i = 1; i <= n; i ++ ) a[i] = inputInt();

stack<int> stk1, stk2;
for ( int i = 1; i <= n; i ++ ) {
        while ( stk1.size() && stk1.top() < a[i] ) stk1.pop();
        stk1.push(a[i]);
}
for ( int i = 1; i <= n; i ++ ) {
        while ( stk2.size() && stk2.top() > a[i] ) stk2.pop();
        stk2.push(a[i]);
}
        
if( MAX(stk1.size(), stk2.size()) == n ) cout << "YES" << endl;
else                                     cout << "NO" << endl;
```

# Question : 如何判断是否可以用一个栈对整个数组排序 
<b>Answer :</b>   
设置一个想要的从 min ~ max 的数  
  
在压栈的过程中，如果当前遍历到了一个我们想要的，就直接出来  
否则压入  
  
压入完后，开始了抛栈顶的过程  
如果栈顶一直是我们想要的，那就可以满足
如果中间停了（也就是最后不是空的）那就不能满足  
```cpp
int n = inputInt();
int a[n + 10], Want = 1;
for ( int i = 1; i <= n; i ++ ) a[i] = inputInt();

stack<int> stk;
//压栈
for ( int i = 1; i <= n; i ++ ) {
        if ( a[i] != Want ) stk.push(a[i]);
        else Want ++;
}
//抛栈
while ( stk.size() && stk.top() == Want ) Want ++, stk.pop();

cout << (stk.empty()? "YES" : "NO") << endl;
```
