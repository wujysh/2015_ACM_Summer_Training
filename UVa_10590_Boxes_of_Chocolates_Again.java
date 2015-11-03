import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	static Scanner cin = new Scanner(System.in);

	public static void main(String[] args) {
		BigInteger[] a = new BigInteger[5010];
		a[0] = BigInteger.ONE;
		for (int i = 1; i <= 5000; i++) {
			a[i] = BigInteger.ZERO;
		}

		for (int i = 1; i <= 5000; i++) {
			for (int j = i; j <= 5000; j++) {
				a[j] = a[j].add(a[j-i]);
			}
		}

		while (cin.hasNext()) {
			int n = cin.nextInt();
			System.out.println(a[n]);
		}
	}

}
