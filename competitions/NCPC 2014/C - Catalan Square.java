import java.util.Scanner;
import java.math.BigInteger;
import java.util.ArrayList;

class Main {		
	public static BigInteger Binom(int n, int k) {
		BigInteger ans = BigInteger.ONE;
		if (k > n-k) k = n-k;
		for (int i = 0; i < k; ++i) {
			ans = ans.multiply(BigInteger.valueOf(n-i));
			ans = ans.divide(BigInteger.valueOf(i+1));
		}
		return ans;
	}
	
	public static BigInteger Catalan(int x) {
		if (x <= 1) return BigInteger.ONE;
		BigInteger c = Binom(2*x, x);
		return c.divide(BigInteger.valueOf(x+1));
	}
	
	public static void main(String[] args) {		
		Scanner sc = new Scanner(System.in);
		
		int x = sc.nextInt();
		System.out.println(Catalan(x+1).toString());		
	}
}