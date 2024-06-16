import java.lang.System;
import java.lang.StringBuilder;
import java.nio.charset.StandardCharsets;

public class PalindromeReorder {
	public static void main(String[] args) throws Exception {
		String s = new String(System.in.readAllBytes(), StandardCharsets.UTF_8).strip();
		int[] occ = new int['Z' - 'A' + 1];
		for (int i = 0; i < s.length(); ++i)
			++occ[s.charAt(i) - 'A'];
		int disp = -1;
		StringBuilder output = new StringBuilder();
		for (int i = 0; i < occ.length; ++i) {
			if (occ[i] % 2 != 0) {
				if (disp != -1) {
					System.out.println("NO SOLUTION");
					return;
				}
				disp = i;
				--occ[i];
			}
			occ[i] /= 2;
			output.append(new String(new char[occ[i]]).replace('\0', (char) (i + 'A')));
		}
		StringBuilder tmp = new StringBuilder(output);
		tmp.reverse();
		if (disp != -1)
			output.append((char) (disp + 'A'));
		System.out.println(output.toString() + tmp.toString());
	}
}
