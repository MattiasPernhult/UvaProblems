import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        new Main().start();
    }

    public void start() {
        Scanner scanner = new Scanner(System.in);
        int numberOfCoords = scanner.nextInt();
        while (numberOfCoords != 0) {
            Point[] points = new Point[100];
            for (int i = 0; i < numberOfCoords; i++) {
                Point p = new Point();
                p.x = scanner.nextInt();
                p.y = scanner.nextInt();
                points[i] = p;
            }

            points[numberOfCoords] = points[0];
            points[numberOfCoords + 1] = points[1];

            int i;

            if (turn(points[0], points[1], points[2]) >= 0) {
                for (i = 0; i < numberOfCoords; i++) {
                    if (turn(points[i], points[i + 1], points[i + 2]) < 0) {
                        break;
                    }
                }
            } else {
                for (i = 0; i < numberOfCoords; i++) {
                    if (turn(points[i], points[i + 1], points[i + 2]) > 0) {
                        break;
                    }
                }
            }

            if (i != numberOfCoords) {
                System.out.println("Yes");
            } else {
                System.out.println("No");
            }
            numberOfCoords = scanner.nextInt();
        }
    }

    private int turn(Point p, Point q, Point r) {
        int result = (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x);
        if (result < 0) return -1; // höger turn
        if (result > 0) return 1; // vänster turn
        return 0; // ingen turn
    }

    private class Point {
        int x, y;
    }
}
