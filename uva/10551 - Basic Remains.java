import java.util.Scanner;
import java.math.BigInteger;

/*
 * one of the BigInteger constructors takes a string and a base.
 * also, you can transform a BigInteger to a string in a given base.
 */

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			int base = sc.nextInt();
			if (base == 0) break;			
			BigInteger p = new BigInteger(sc.next(), base);
			BigInteger m = new BigInteger(sc.next(), base);
			System.out.println(p.mod(m).toString(base));
		}
	}
}