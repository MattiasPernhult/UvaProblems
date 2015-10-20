import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Main main = new Main();
        main.start();
    }

    int solutionNumber;
    String a;
    String b;
    String c;

    public int decodeSingle(char letter) {
        switch (letter) {
            case 'M':
                return 1000;
            case 'D':
                return 500;
            case 'C':
                return 100;
            case 'L':
                return 50;
            case 'X':
                return 10;
            case 'V':
                return 5;
            case 'I':
                return 1;
            default:
                return 0;
        }
    }

    public int decode(String roman) {
        int result = 0;
        String uRoman = roman.toUpperCase();
        for (int i = 0; i < uRoman.length() - 1; i++) {
            if (decodeSingle(uRoman.charAt(i)) < decodeSingle(uRoman.charAt(i + 1))) {
                result -= decodeSingle(uRoman.charAt(i));
            } else {
                result += decodeSingle(uRoman.charAt(i));
            }
        }
        result += decodeSingle(uRoman.charAt(uRoman.length() - 1));
        return result;
    }

    public void start() {
        Scanner scanner = new Scanner(System.in);

        String line = scanner.nextLine();
        while (!line.contains("#")) {
            line = line.replaceAll("\\s+", "");
            line = line.toUpperCase();
            StringBuilder builder = new StringBuilder();
            builder.append(line);
            boolean[] ch = new boolean[26];
            for (int i = 0; i < builder.length(); i++) {
                if (line.charAt(i) == '+' || line.charAt(i) == '=') {
                    builder.replace(i, i + 1, " ");
                } else {
                    ch[builder.charAt(i) - 'A'] = true;
                }
            }

            String line2 = builder.toString();
            String[] words = line2.split(" ");
            a = words[0];
            b = words[1];
            c = words[2];
            boolean[] head = new boolean[128];
            head[a.charAt(0)] = true;
            head[b.charAt(0)] = true;
            head[c.charAt(0)] = true;

            List<Character> all = new ArrayList<>();

            for (int i = 0; i < 26; i++) {
                if (ch[i]) {
                    all.add(Character.toChars(65 + i)[0]);
                }
            }

            int[] value = new int[128];
            boolean[] used = new boolean[10];
            solutionNumber = 0;
            solve(0, all, value, used, head);

            if (decode(a) + decode(b) == decode(c)) {
                System.out.print("Correct ");
            } else {
                System.out.print("Incorrect ");
            }
            switch (solutionNumber) {
                case 0:
                    System.out.println("impossible");
                    break;
                case 1:
                    System.out.println("valid");
                    break;
                default:
                    System.out.println("ambiguous");
                    break;
            }
            if (scanner.hasNext()) {
                line = scanner.nextLine();
            } else {
                line = "#";
            }
        }
    }

    public void solve(int now, List<Character> all, int[] value, boolean[] used, boolean[] head) {
        if (solutionNumber > 1) {
            return;
        }
        if (now == all.size()) {
            int n1 = 0, n2 = 0, n3 = 0;

            for (int i = 0; i < a.length(); i++) {
                n1 = n1 * 10 + value[a.charAt(i)];
            }
            for (int i = 0; i < b.length(); i++) {
                n2 = n2 * 10 + value[b.charAt(i)];
            }
            for (int i = 0; i < c.length(); i++) {
                n3 = n3 * 10 + value[c.charAt(i)];
            }
            if (n1 + n2 == n3) {
                solutionNumber++;
            }
            return;
        }
        boolean var = head[all.get(now)];
        int lklk;
        if (!var) {
            lklk = 0;
        } else {
            lklk = 1;
        }
        for (int d = lklk; d < 10 && solutionNumber <= 1; d++) {
            if (!used[d]) {
                value[all.get(now)] = d;
                used[d] = true;
                solve(now + 1, all, value, used, head);
                used[d] = false;
            }
        }
    }

}
