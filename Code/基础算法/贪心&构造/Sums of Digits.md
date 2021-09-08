# 🔗
<a href="https://codeforces.com/problemset/problem/509/C"><img src="https://i.loli.net/2021/09/08/EvOT9GAor6aHkbS.png"></a>

# 💡
如果新开一个字符串重新构造，那么要考虑的太多  
既然题目要求我们每一个数都是递增的，那么我们可以直接在上一步求得的数上进行更改  
1.如果给的数相等，就从最低位向前进一位即可  
2.如果给的a[i]比上一步大，那么就从最低位看看有没有哪一位没到9，往上加就行  
3.如果当前给的a[i]比上一步的小，那么就模仿加运算，从最低位向前进位，直到a[i]>a[i-1]，然后在进行第二步  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	cin >> n;
	for ( int i = 1; i <= n; i ++ )  cin >> a[i];
	for ( int i = 1; i <= 1000; i ++ ) res[0] += "0";

	for ( int i = 1; i <= n; i ++ ) {
		int d = a[i] - a[i - 1];
		int j = res[i - 1].size() - 1;
		res[i] = res[i - 1]; 
		if ( d == 0 ) { // 相等
			int jj = j;
			d += res[i][jj] - '0' - 1;
			res[i][jj] = '0';
			res[i][jj - 1] ++;
			jj --;
            		while ( res[i][jj] == '0' + 10 )
                    		d += res[i][jj] - '0' - 1,
                    		res[i][jj] = '0',
                    		res[i][jj - 1] ++,
                    		jj --;
		}
		bool flag = false;
		while ( d > 0 ) { // 如果大了就操作一次就不管了
			flag = true;
			if ( d > '9' - res[i][j] ) 
				d -= '9' - res[i][j],
				res[i][j] = '9';
			else 
				res[i][j] += d,
				d = 0;
			j --;
		}
		if ( flag ) continue;

		while ( d < 0 )  { // 如果小于上一步
			if ( res[i][j] != '0' ) {
				d += res[i][j] - '0' - 1,
				res[i][j] = '0',
				res[i][j - 1] ++;
			}
			j --;
			while ( res[i][j] == '0' + 10 )
				d += res[i][j] - '0' - 1,
				res[i][j] = '0',
				res[i][j - 1] ++,
				j --;
		}
		j = res[i].size() - 1;
		while ( d > 0 ) {
			if ( d > '9' - res[i][j] )
				d -= '9' - res[i][j],
				res[i][j] = '9';
			else
				res[i][j] += d,
				d = 0;
			j --;
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		int j = 0;
		while ( res[i][j] == '0' ) j ++;
		for ( ; j < res[i].size(); j ++ ) cout << res[i][j];
		cout << endl;
	}
	return 0;
}
```
