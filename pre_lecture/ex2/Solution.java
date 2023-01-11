package pre_lecture.ex2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Console;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Solution {
    public static final int BUFMAX = 100_000 + 10;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8), BUFMAX);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        String line = br.readLine();
        int t = Integer.parseInt(line);

        for (int test_case = 1; test_case <= t; ++test_case) {

            int codePoint = 0;
            StringBuilder str = new StringBuilder(BUFMAX);
            do {
                codePoint = br.read();
                str.appendCodePoint(codePoint);
            } while (codePoint != '\n');

            bw.write(String.format("length: %d%n", str.length()));
            bw.flush();
        }

        br.close();
        bw.flush();
        bw.close();
    }

    /**
     * 양의 정수 N (1 <= N <= 10^100_000) 이하의 정수 중 x, y (0 <= x < y <= 9) 만으로
     * 이루어진 가장 큰 정수를 구하시오. 만약 없다면 -1을 리턴하시오.
     */
    public static String solution(String n, char x, char y) {

        assert n.length() <= 100_001;
        assert ('0' <= x && x < y && y <= '9');

        StringBuilder str = new StringBuilder();

        for (int idx = 0; idx < n.length(); ++idx) {
            char cur = n.charAt(idx);
            if (y < cur) {// y로 도배할 것

                str.append(fill(y, n.length() - idx));
                break;
            } else if (cur == y) {

                str.append(y);
            } else if (x < cur) {// (x < cur < y) -> y로 도배할 것

                str.append(x);
                str.append(fill(y, n.length() - idx - 1));
                break;
            } else if (cur == x) {

                str.append(x);
            } else /* cur < x */ {// 자릿수 하나를 내려버린 뒤 y로 도배할 것

                str = new StringBuilder();
                str.append(fill(y, n.length() - 1));
                break;
            }
        }

        if (str.length() == 0 ||
                (str.length() == 1 && str.charAt(0) == '0')) {
            return "-1";
        }
        return str.toString();
    }

    public static char[] fill(char val, int count) {
        char[] ret = new char[count];
        Arrays.fill(ret, val);
        return ret;
    }

}
