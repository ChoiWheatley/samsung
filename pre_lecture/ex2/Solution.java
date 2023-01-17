package pre_lecture.ex2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class Solution {

    public static void main(String[] args) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out))) {
            String line = br.readLine();
            int t = Integer.valueOf(line);

            for (int test_case = 1; test_case <= t; ++test_case) {

                String[] splitted = br.readLine().split(" ");
                String n = splitted[0];
                char x = splitted[1].charAt(0);
                char y = splitted[2].charAt(0);

                String submit = solution(n, x, y);
                bw.write(String.format("#%d %s\n", test_case, submit));
                bw.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
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
            } else /* cur < x */ {// 앞 자리수를 거슬러 올라간 뒤 y로 도배할 것

                int backIdx = idx - 1;
                for (; backIdx > 0 && str.charAt(backIdx) == x; --backIdx)
                    ;
                if (str.length() != 0) {
                    str.delete(backIdx, idx);
                    if (n.charAt(backIdx) > x) {
                        str.append(x);
                    }
                    str.append(fill(y, n.length() - backIdx - 1));
                } else {
                    str = new StringBuilder();
                    str.append(fill(y, n.length() - 1));
                }
                break;
            }
        }

        if (str.length() > 0 && str.charAt(0) == '0') {
            str.deleteCharAt(0);
        }
        if (str.length() == 0) {
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
