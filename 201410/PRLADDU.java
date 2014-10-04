import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

// iSea @ 2014-10-04 16:37

class Task {
	public void solve(int testNumber, InputReader in, PrintWriter out) {
		int n = in.nextInt();
		int[] num = new int[n];
		for (int i = 0; i < n; ++i) {
			num[i] = in.nextInt();
		}
		long ret = 0;
		int p1 = 0, p2 = 0;
		while (p1 < n) {
			while (p1 < n && num[p1] > 0) {
				p1 += 1;
			}
			if (p1 == n) {
				break;
			}
			int need = -num[p1];
			while (need > 0) {
				while (p2 < n && num[p2] < 0) {
					p2 += 1;
				}
				int match = Math.min(need, num[p2]);
				ret += match * Math.abs(p1 - p2);
				num[p2] -= match;
				need -= match;
				if (num[p2] == 0) {
					p2 += 1;
				}
			}
			num[p1++] = 0;
		}
		out.println(ret);
	}
}

public class PRLADDU {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));

		Task solver = new Task();
		int testCount = in.nextInt();
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