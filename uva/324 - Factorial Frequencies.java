import java.util.Scanner;
import java.math.BigInteger;

/* Very simple with BigInteger. */

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			int x = sc.nextInt();
			if (x == 0) break;
			BigInteger b = BigInteger.ONE;
			for (int i = 1; i <= x; ++i)
				b = b.multiply(BigInteger.valueOf(i));

			int[] frequencies = new int[10];
			for (char c : b.toString().toCharArray())
				++frequencies[c - '0'];
			
			System.out.println(x + "! --");
			for (int i = 0; i <= 9; ++i) {				
				System.out.print("    (" + i + ")    " + frequencies[i]);	
				if (i == 4 || i == 9) System.out.println();
			}			

		}
	}
}