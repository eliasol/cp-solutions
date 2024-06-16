import java.lang.System;
import java.lang.String;
import java.util.StringTokenizer;
import java.lang.StringBuilder;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class Subordinates {
	private static ArrayList<ArrayList<Integer>> g;
	private static int[] dp;

	public static void main(String[] args) throws Exception {
		StringTokenizer tok = new StringTokenizer(new String(System.in.readAllBytes(), StandardCharsets.UTF_8));
		int n = Integer.parseInt(tok.nextToken());
		g = new ArrayList<>(n + 1);
		dp = new int[n + 1];
		for (int i = 0; i <= n; ++i)
			g.add(new ArrayList<>());
		for (int i = 2; i <= n; ++i) {
			int x = Integer.parseInt(tok.nextToken());
			g.get(x).add(i);
		}

		int[] queue = new int[n];
		int sus1 = 0;
		int sus2 = 0;

		queue[0] = 1;
		sus2++;

		while (sus1 < sus2) {
			int x = queue[sus1];
			sus1++;

			for (int c : g.get(x))
				queue[sus2++] = c;
		}

		--sus2;
		for (; sus2 >= 0; --sus2) {
			for (int c : g.get(queue[sus2]))
				dp[queue[sus2]] += 1 + dp[c];
		}

		StringBuilder output = new StringBuilder();
		for (int i = 1; i <= n; ++i)
			output.append(dp[i] + " ");
		System.out.println(output.toString());
	}
}
