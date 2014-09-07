import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

// iSea @ 2014-09-05 18:17

class Task {
	static int MOD = 1000000007;
	static int MAXN = 1000000 + 10;
	int[] fac = new int[MAXN];

	int mul(int x, int y) {
		return (int)((long)x * y % MOD);
	}

	public void pre() {
		fac[0] = 1;
		for (int i = 1; i < MAXN; ++i) {
			fac[i] = mul(fac[i - 1], i);
		}
	}

	public int fastMod(int a, int p) {
		int res = 1;
		while (p != 0) {
			if ((p & 1) == 1) res = mul(res, a);
			a = mul(a, a);
			p >>= 1;
		}
		return res;
	}

	public int getInv(int x) {
		return fastMod(x, MOD - 2);
	}

	public int getCom(int n, int m) {
		return mul(fac[n], mul(getInv(fac[m]), getInv(fac[n - m])));
	}

	public void solve(int testNumber, InputReader in, PrintWriter out) {
		int n = in.nextInt();
		int res = 0;
		for (int i = 2 - (n & 1); (n - i) / 2 >= 6; i += 2) {
			res += getCom((n - i) / 2 - 1, 5);
			if (res >= MOD) res -= MOD;
		}
		out.println(res);
	}
}

public class RAINBOWB {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));

		Task solver = new Task();
		solver.pre();

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
