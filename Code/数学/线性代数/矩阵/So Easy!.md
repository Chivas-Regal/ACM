# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=4565"><img src="https://i.loli.net/2021/08/17/qobTNGrjvJEdPDs.png"></a>  

# 💡
<img src="https://i.loli.net/2021/08/17/8slyrGq6WCKVxc4.jpg">  
根据推导之后的结果递推式构建矩阵ksm即可  
（要大数防止爆ll）

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
