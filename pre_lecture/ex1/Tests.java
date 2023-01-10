package pre_lecture.ex1;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.Test;

public class Tests {
    @Test
    public void sol1() {
        char[][] testcase = toCharArray("""
                CAAB
                ADCB""");
        int answer = 3;
        int submit = Solution.solution(testcase);
        assertEquals(answer, submit);
    }

    @Test
    public void sol2() {
        char[][] testcase = toCharArray("""
                HFDFFB
                AJHGDH
                DGAGEH""");
        int answer = 6;
        int submit = Solution.solution(testcase);
        assertEquals(answer, submit);
    }

    @Test
    public void sol3() {
        char[][] testcase = toCharArray("""
                IEFCJ
                FHFKC
                FFALF
                HFGCF
                HMCHH""");
        int answer = 10;
        int submit = Solution.solution(testcase);
        assertEquals(answer, submit);
    }

    @Test
    public void sol4() {
        char[][] testcase = toCharArray("""
                ABCDEFGHIJKLMNOPQRSTUVWXYZ""");
        int answer = 26;
        int submit = Solution.solution(testcase);
        assertEquals(answer, submit);
    }

    public char[][] toCharArray(String str) {
        String[] lines = str.split("\n");
        char[][] ret = new char[lines.length][];
        for (int r = 0; r < lines.length; ++r) {
            ret[r] = lines[r].toCharArray();
        }
        return ret;
    }
}
