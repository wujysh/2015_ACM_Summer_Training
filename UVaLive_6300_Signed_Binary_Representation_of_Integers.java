import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	static Scanner scanner = new Scanner(System.in);
	
	public static void main(String args[]) {
		while (scanner.hasNext()) {
			BigInteger x = scanner.nextBigInteger();
			if (x.equals(BigInteger.ZERO)) break;
			
			char[] xx = x.toString(2).toCharArray();
		
			int cnt1 = 0, cnt2 = 0;
			for (int i = 0; i < xx.length; i++) {
				if (xx[i] == '1') {
					cnt1++;
				}
			}

			int i = xx.length-1;
			while (i >= 0) {
				if (xx[i] == '1') {
					i--;
					boolean flag = false;
					while (i >= 0 && xx[i] == '1') {
						i--;
						flag = true;
					}
					if (flag) {
						if (i == -1) {
							cnt2++;
						}
					}
					cnt2++;
					
					if (i >= 0 && flag) {
						xx[i] = '1';
					}
				} else {
					i--;
				}
			}
			
			System.out.println(cnt1 + " " + cnt2);
		}
		
	}
	
}

