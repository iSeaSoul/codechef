import java.io.*;
import java.util.*;
import java.util.Map.Entry;
import java.text.*;
import java.math.*;
import java.util.regex.*;

// iSea @ 2014-09-05 21:58

class Task {
	public void solve(int testNumber, InputReader in, PrintWriter out) {
		int n = in.nextInt(), m = in.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; ++i) {
			a[i] = in.nextInt();
		}

		HashMap<Integer, Integer> dif = new HashMap<Integer, Integer>();
		if (n > 100) {
			for (int i = 0; i < 100; ++i) {
				if (dif.containsKey(a[i + 1] - a[i])) {
					dif.put(a[i + 1] - a[i], dif.get(a[i + 1] - a[i]) + 1);
				} else {
					dif.put(a[i + 1] - a[i], 1);
				}
			}
			int d = getMaximumD(dif);
			dif.clear();
			for (int i = 0; i <= 100; ++i) {
				if (dif.containsKey(a[i] - i * d)) {
					dif.put(a[i] - i * d, dif.get(a[i] - i * d) + 1);
				} else {
					dif.put(a[i] - i * d, 1);
				}
			}
			int a0 = getMaximumD(dif);
			// String ans = "";
			for (int i = 0; i < n; ++i) {
				out.print(a0 + d * i);
				if (i < n - 1) out.print(' ');
			}
			out.println("");
			return ;
		}

		double ans_a0 = 0.0, ans_d = 0.0;
		boolean found = false;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				double d = ((double)a[j] - a[i]) / (j - i);
				double a0 = a[i] - i * d;
				if (match(a0, d, a, n, m)) {
					if (!found) {
						ans_a0 = a0; ans_d = d;
						found = true;
					} else {
						if (sgn(ans_a0 - a0) > 0 || (sgn(ans_a0 - a0) == 0 && sgn(ans_d - d) > 0)) {
							ans_a0 = a0; ans_d = d;
						}
					}
				}
			}
		}
		// String ans = "";
		for (int i = 0; i < n; ++i) {
			// if (i > 0) ans += " ";
			// ans += String.format("%.0f", ans_a0 + ans_d * i);
			out.print(String.format("%.0f", ans_a0 + ans_d * i));
			if (i < n - 1) out.print(' ');
		}
		out.println("");
	}

	int sgn(double x) {
		if (x > 1e-8) return 1;
		if (x < -1e-8) return -1;
		return 0;
	}

	boolean match(double a0, double d, int[] a, int n, int k) {
		int unmatch = 0;
		for (int i = 0; i < n; ++i) {
			if (sgn(a0 + d * i - a[i]) != 0) {
				if (++unmatch > k) {
					return false;
				}
			}
		}
		return true;
	}

	int getMaximumD(HashMap<Integer, Integer> dif) {
		int maxt = 0, maxd = 0;
		for (Entry<Integer, Integer> entry: dif.entrySet()) {
			if (entry.getValue() > maxt) {
				maxt = entry.getValue();
				maxd = entry.getKey();
			}
		}
		return maxd;
	}
}

public class UASEQ {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));

		Task solver = new Task();
		int testCount = 1;
		for (int T = 1; T <= testCount; ++T) {
			solver.solve(T, in, out);
		}
		out.close();
	}
}

class InputReader {
	BufferedReader br;
	StringTokenizer st;

	public InputReader(File f) {
		try {
			br = new BufferedReader(new FileReader(f));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	public InputReader(InputStream f) {
		br = new BufferedReader(new InputStreamReader(f));
	}

	String next() {
		while (st == null || !st.hasMoreTokens()) {
			String s = null;
			try {
				s = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			if (s == null)
				return null;
			st = new StringTokenizer(s);
		}
		return st.nextToken();
	}

	boolean hasMoreTokens() {
		while (st == null || !st.hasMoreTokens()) {
			String s = null;
			try {
				s = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			if (s == null)
				return false;
			st = new StringTokenizer(s);
		}
		return true;
	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	double nextDouble() {
		return Double.parseDouble(next());
	}
}
