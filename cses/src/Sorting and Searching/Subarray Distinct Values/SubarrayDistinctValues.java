import java.lang.System;
import java.util.StringTokenizer;
import java.util.HashMap;
import java.nio.charset.StandardCharsets;

public class SubarrayDistinctValues {
	public static void main(String[] args) throws Exception {
		StringTokenizer tok = new StringTokenizer(new String(System.in.readAllBytes(), StandardCharsets.UTF_8));
		int n = Integer.parseInt(tok.nextToken());
		int k = Integer.parseInt(tok.nextToken());
		int[] v = new int[n];
		for (int i = 0; i < n; ++i)
			v[i] = Integer.parseInt(tok.nextToken());
		long ans = 0;
		int l = 0, r = 0;
		int dist = 0;
		HashMap<Integer, Integer> sus = new HashMap<>();
		while (l < n) {
			while (r < n && (dist < k || sus.containsKey(v[r]))) {
				if (!sus.containsKey(v[r])) {
					++dist;
					sus.put(v[r], 1);
				} else {
					sus.replace(v[r], sus.get(v[r]) + 1);
				}
				++r;
			}
			ans += (r - l);
			int x = sus.get(v[l]);
			if (x == 1) {
				--dist;
				sus.remove(v[l]);
			} else {
				sus.replace(v[l], x - 1);
			}
			++l;
		}
		System.out.println(ans);
	}
}
