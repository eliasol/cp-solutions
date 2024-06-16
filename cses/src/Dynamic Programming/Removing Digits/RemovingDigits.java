import java.lang.System;
import java.nio.charset.StandardCharsets;

public class RemovingDigits {
	public static void main(String[] args) throws Exception {
		int n = Integer.parseInt(new String(System.in.readAllBytes(), StandardCharsets.UTF_8).strip());
		int[] dp = new int[n + 1];
		for (int i = 1; i <= n; ++i) {
			int x = i;
			dp[i] = i;
			while (x > 0) {
				if (dp[i - x % 10] + 1 < dp[i])
					dp[i] = dp[i - x % 10] + 1;
				x /= 10;
			}
		}
		System.out.println(dp[n]);
	}
}
