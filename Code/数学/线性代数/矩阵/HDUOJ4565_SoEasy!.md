# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=4565"><img src="https://i.loli.net/2021/08/17/qobTNGrjvJEdPDs.png"></a>  
	
# 💡
根据二项式定理，可以设计两个式子  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}(a&plus;\sqrt{b})^n=An&plus;B_n\sqrt{b}\\(a-\sqrt{b})^n=A_n-B_n\sqrt{b}\end{aligned}&space;" title="\begin{aligned}(a+\sqrt{b})^n=An+B_n\sqrt{b}\\(a-\sqrt{b})^n=A_n-B_n\sqrt{b}\end{aligned} " />  
通过转化来的式子合并一下  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}(a&plus;\sqrt{b})^n&plus;(a-\sqrt{b})^n=2A_n\\(a&plus;\sqrt{b})^n=2A_n-(a-\sqrt{b})^n\end{aligned}&space;" title="\begin{aligned}(a+\sqrt{b})^n+(a-\sqrt{b})^n=2A_n\\(a+\sqrt{b})^n=2A_n-(a-\sqrt{b})^n\end{aligned} " />  
利用限制条件有  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}&space;&space;&space;\because&space;a-1<\sqrt[]{b}<a\\\therefore&space;0<a-\sqrt[]{b}<0\\\therefore&space;(a&plus;\sqrt[]{b})^n=2A_n&space;&space;-(a-\sqrt[]{b})^n\left\{\begin{aligned}&<2A_n\\&>2A_n-1\end{aligned}\right.&space;\Rightarrow\lceil(a&plus;\sqrt[]{b})^n\rceil=2A_n&space;\end{aligned}" title="\begin{aligned} \because a-1<\sqrt[]{b}<a\\\therefore 0<a-\sqrt[]{b}<0\\\therefore (a+\sqrt[]{b})^n=2A_n -(a-\sqrt[]{b})^n\left\{\begin{aligned}&<2A_n\\&>2A_n-1\end{aligned}\right. \Rightarrow\lceil(a+\sqrt[]{b})^n\rceil=2A_n \end{aligned}" />  
得到新式  
<img src="https://latex.codecogs.com/svg.image?\lceil&space;(a&plus;\sqrt[]{b})^n\rceil&space;=2A_n=(a&plus;\sqrt[]{b})^n&plus;(a-\sqrt{b})^n&space;&space;" title="\lceil (a+\sqrt[]{b})^n\rceil =2A_n=(a+\sqrt[]{b})^n+(a-\sqrt{b})^n " />  
令<img src="https://latex.codecogs.com/svg.image?x=a&plus;\sqrt[]{b},\quad&space;y=a-\sqrt[]{b}&space;&space;" title="x=a+\sqrt[]{b},\quad y=a-\sqrt[]{b} " />  
则<img src="https://latex.codecogs.com/svg.image?(a&plus;\sqrt[]{b})^n&plus;(a-\sqrt[]{b})^n=x^n&plus;y^n=(x&plus;y)(x^{n-1}&plus;y^{n-1})-xy(x^{n-2}&plus;y^{n-2})&space;&space;" title="(a+\sqrt[]{b})^n+(a-\sqrt[]{b})^n=x^n+y^n=(x+y)(x^{n-1}+y^{n-1})-xy(x^{n-2}+y^{n-2}) " />  
得到函数式<img src="https://latex.codecogs.com/svg.image?g(n)=x^n&plus;y^n,\quad&space;x&plus;y=2a,\quad&space;xy=a^2-b" title="g(n)=x^n+y^n,\quad x+y=2a,\quad xy=a^2-b" />  
同时有递推  
<img src="https://latex.codecogs.com/svg.image?g(n)=2a*g(n-1)-(a^2-b^2)*g(n-2)" title="g(n)=2a*g(n-1)-(a^2-b^2)*g(n-2)" />  
利用求得的递推式构建矩阵ksm即可，但要防止爆数据类型，可以使用大数


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```java
import java.util.*;
import java.math.*;

public class Main {
	static BigInteger a, b, n, mod;
	static Mat res;
	public static void main ( String[] args ) {
		Scanner input = new Scanner(System.in);
		while ( input.hasNext() ) {
			a = input.nextBigInteger();
			b = input.nextBigInteger();
			n = input.nextBigInteger();
			mod = input.nextBigInteger();
			
			res = new Mat(0);
			res.m[0][0] = a.multiply(BigInteger.valueOf(2)).mod(mod); res.m[0][1] = b.subtract(a.multiply(a)).mod(mod);
			res.m[1][0] = BigInteger.ONE;             res.m[1][1] = BigInteger.ZERO;
			res = res.ksm(res, n.subtract(BigInteger.ONE));
			System.out.println(res.m[0][0].multiply(BigInteger.valueOf(2)).mod(mod).multiply(a).mod(mod).add(res.m[0][1].multiply(BigInteger.valueOf(2)).mod(mod)).mod(mod).add(mod).mod(mod));
		}
		input.close();
	}
}

class Mat {
	BigInteger[][] m = new BigInteger[3][3];
	Mat ( int flag ) {
		for ( int i = 0; i < 3; i ++ ) 
			for ( int j = 0; j < 3; j ++ ) {
				if ( i == j ) m[i][j] = BigInteger.valueOf(flag);
				else m[i][j] = BigInteger.ZERO;
			}
	}
	Mat Mul ( Mat a, Mat b ) {
		Mat res = new Mat(0);
		for ( int i = 0; i < 3; i ++ ) 
			for ( int j = 0 ;j < 3; j ++ ) 
				for ( int k = 0; k < 3; k ++ ) 
					res.m[i][j] = res.m[i][j].add(a.m[i][k].multiply(b.m[k][j]).mod(Main.mod)).mod(Main.mod);
		return res;
	}
	Mat ksm ( Mat a, BigInteger b ) {
		Mat res = new Mat(1);
		while ( b.compareTo(BigInteger.ZERO) == 1 ) {
			if ( b.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE) == 0 ) res = Mul(res, a);
			a = Mul(a, a);
			b = b.divide(BigInteger.valueOf(2));
		}
		return res;
	}
};
```
