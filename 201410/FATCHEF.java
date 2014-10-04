import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

// iSea @ 2014-10-04 16:50

class Task {
	static int mod = 1000000009;

	public void solve(int testNumber, InputReader in, PrintWriter out) {
		int n = in.nextInt(), m = in.nextInt();
		char[] cols = new char[n];
		Arrays.fill(cols, '\0');
		for (int i = 0; i < m; ++i) {
			char col = in.next().charAt(0);
			int pos = in.nextInt() - 1;
			cols[pos] = col;
		}
		long ret = 1;
		int prev = -1;
		for (int i = 0; i < n; ++i) {
			if (cols[i] != '\0') {
				if (prev != -1 && cols[prev] != cols[i]) {
					ret = (ret * (i - prev)) % mod;
				}
				prev = i;
			}
		}
		out.println(ret);
	}
}

public class FATCHEF {
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
