import java.lang.System;
import java.util.Scanner;

class SubarrayDivisibility {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int[] occ = new int[n];
		long ans = 0;
		int sum = 0;
		occ[0] = 1;
		for (int i = 0; i < n; ++i) {
			int x = scanner.nextInt();
			sum = (((sum + x) % n) + n) % n;
			ans += occ[sum];
			occ[sum]++;
		}
		System.out.println(ans);
	}
}
