package pre_lecture.ex1;

import java.util.Scanner;

class Solution {
    public static void main(String args[]) throws Exception {
        /*
         * 표준입력 System.in 으로부터 스캐너를 만들어 데이터를 읽어옵니다.
         */
        Scanner sc = new Scanner(System.in);
        int T;
        T = sc.nextInt();
        /*
         * 여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
         */

        for (int test_case = 1; test_case <= T; test_case++) {

            /////////////////////////////////////////////////////////////////////////////////////////////
            /*
             * 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
             */
            int R = sc.nextInt();
            int C = sc.nextInt();
            char[][] map = new char[R][C];
            for (int r = 0; r < R; ++r) {
                map[r] = sc.next().toCharArray();
            }
            int submit = solution(map);
            System.out.printf("#%d %d\n", test_case, submit);
            /////////////////////////////////////////////////////////////////////////////////////////////

        }
        sc.close();
    }

    public static int solution(char[][] map) {
        return dfs(map, 0, 0, new boolean[map.length][map[0].length], new boolean[(int) 'Z' + 1]);
    }

    public static int dfs(char[][] map, int r, int c, boolean[][] visited, boolean[] bought) {
        final int R = map.length;
        final int C = map[0].length;
        if (r < 0 || R <= r ||
                c < 0 || C <= c ||
                visited[r][c]) {
            return 0;
        }
        char cur = map[r][c];
        if (bought[(int) cur]) {
            return 0;
        }

        visited[r][c] = true;
        bought[(int) cur] = true;

        int best = 0;
        for (Delta delta : Delta.values()) {
            int nextR = r + delta.r;
            int nextC = c + delta.c;
            best = Integer.max(best, dfs(map, nextR, nextC, visited, bought));
        }

        visited[r][c] = false;
        bought[(int) cur] = false;

        return best + 1;
    }

    public static enum Delta {
        U(-1, 0), R(0, 1), D(1, 0), L(0, -1);

        public final int r;
        public final int c;

        Delta(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}