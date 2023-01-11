package pre_lecture.ex2;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Random;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import org.junit.Test;
import org.junit.jupiter.api.RepeatedTest;

public class Tests {
    @Test
    public void intstream1() {
        int size = 10;
        int[] answer = new int[size];
        int[] submit = IntStream.iterate(0, i -> i).limit(size).toArray();
        assertArrayEquals(answer, submit);
    }

    @Test
    public void intstream2() {
        int size = 10;
        char value = '8';
        int[] answer = new int[size];
        Arrays.fill(answer, value);
        int[] submit = IntStream.iterate(value, i -> i).limit(size).toArray();
        assertArrayEquals(answer, submit);
    }

    @Test
    public void intstream3() {
        int size = 10;
        char value = '8';
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < size; ++i) {
            str.append(value);
        }
        String submit = IntStream.iterate(value, i -> i).limit(size)
                .collect(StringBuilder::new,
                        StringBuilder::appendCodePoint,
                        StringBuilder::append)
                .toString();
        assertEquals(str.toString(), submit);
    }

    @Test
    public void sol1() {
        String n = "422223324";
        char x = '2';
        char y = '4';
        String answer = "422222444";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol1$1() {
        String n = "422223324";
        char x = '3';
        char y = '4';
        String answer = "44444444";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol1$2() {
        String n = "422223324";
        char x = '1';
        char y = '9';
        String answer = "199999999";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol2() {
        String n = "322223324";
        char x = '2';
        char y = '4';
        String answer = "244444444";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol3() {
        String n = "16";
        char x = '1';
        char y = '3';
        String answer = "13";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol4() {
        String n = "2";
        char x = '6';
        char y = '9';
        String answer = "-1";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol5() {
        String n = "5";
        char x = '0';
        char y = '8';
        String answer = "-1"; // N은 0으로 시작하지 않는다.
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol6() {
        String n = "80001";
        char x = '0';
        char y = '8';
        String answer = "80000";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol7() {
        String n = "9876543210";
        char x = '0';
        char y = '9';
        String answer = "9099999999";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);

        BigInteger bigOriginal = new BigInteger(n);
        BigInteger bigSubmig = new BigInteger(submit);
        assertTrue(bigOriginal.compareTo(bigSubmig) > 0);
    }

    @Test
    public void sol8() {
        String n = "222111";
        char x = '0';
        char y = '2';
        String answer = "222022";
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit);
    }

    @Test
    @RepeatedTest(100)
    public void timeout() {
        int size = 100_000;
        String n = (new Random()).ints(1, 10).limit(size)
                .collect(StringBuilder::new,
                        StringBuilder::append,
                        StringBuilder::append)
                .toString();
        assertEquals(size, n.length());
        char x = '0';
        char y = '1';
        String answer = Stream.iterate(y, i -> i).limit(size)
                .collect(StringBuilder::new,
                        StringBuilder::append,
                        StringBuilder::append)
                .toString();
        String submit = Solution.solution(n, x, y);
        assertEquals(answer, submit, String.format(
                "%n%norigin = %s%n%nanswer.length = %d,%nsubmit.length = %d%n",
                n, answer.length(), submit.length()));
    }
}
