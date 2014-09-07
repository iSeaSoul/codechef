import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

// iSea @ 2014-09-05 20:54

class Task {
	public int mod;
	
	int mul(long x, long y) {
		return (int)(x * y % mod);
	}

	int mul(long x, long y, int m) {
		return (int)(x * y % m);
	}

	int pow4(long x) {
		return mul(x, mul(x, mul(x, x)));
	}

	int pow4all(long x) {
		// sigma(x^4) = (3*x*x + 3*x - 1) * (2*x + 1) * (x + 1) * x / 30
		int cmod = 30 * mod;
		x %= cmod;

		int ret = mul(x, x + 1, cmod);
		ret = mul(ret, 1 + 2 * x, cmod);
		int tmp = (int)((x * x * 3 + x * 3 - 1) % cmod);
		if (tmp < 0) tmp += cmod;
		ret = mul(ret, tmp, cmod);

		return ret / 30;
	}

	int pow4range(long l, long r) {
		if (l > r) return 0;
		return (pow4all(r) + mod - pow4all(l - 1)) % mod;
	}

	public void solve(int testNumber, InputReader in, PrintWriter out) {
		long n = in.nextLong();
		mod = in.nextInt();

		long sqn = (long)(Math.sqrt(n * 1.0));
		int ret = 0;
		for (long i = 1; i <= sqn; ++i) {
			// i <= sqrt(n)
			ret += mul(pow4(i), n / i);
			if (ret >= mod) {
				ret -= mod;
			}

			// i <= N / x <= i + 1
			long l = n / (i + 1) + 1, r = n / i;
			if (r <= sqn) {
				continue ;
			}
			l = Math.max(sqn + 1, l);
			ret += mul(i, pow4range(l, r));
			if (ret >= mod) {
				ret -= mod;
			}
		}
		out.println(ret);
	}
}

public class FLOORI4 {
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
