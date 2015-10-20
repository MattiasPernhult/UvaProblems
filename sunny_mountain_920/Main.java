import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static void main(String[] args) {
        new Main().start();
    }

    public void start() {

        Scanner scanner = new Scanner(System.in);

        int testCases = scanner.nextInt();

        while (testCases-- > 0) {
            List<Point> points = new ArrayList<>();
            int numberOfRows = scanner.nextInt();
            for (int i = 0; i < numberOfRows; i++) {
                Point point = new Point();
                point.x = scanner.nextInt();
                point.y = scanner.nextInt();
                points.add(point);
            }

            Collections.sort(points);

            double highestHill = 0, sun = 0;

            for (int i = 1; i < numberOfRows; i++) {

                if (points.get(i).y > highestHill) {

                    double x, y;
                    x = points.get(i).x - (double) (points.get(i).x - points.get(i - 1).x) * (points.get(i).y - highestHill) / (points.get(i).y - points.get(i - 1).y);
                    y = highestHill;
                    sun += Math.sqrt((x - points.get(i).x) * (x - points.get(i).x) + (y - points.get(i).y) * (y - points.get(i).y));
                    highestHill = points.get(i).y;

                    //double distanceBetweenXPoints = points.get(i).x - points.get(i - 1).x;
                    //double distanceBetweenYPoints = points.get(i).y - points.get(i - 1).y;

                    //double sunnyPart = points.get(i).y - highestHill;
                    //double sunnyPartToCount = sunnyPart / distanceBetweenYPoints;

                    //double sqrt = distanceBetweenXPoints * distanceBetweenXPoints + distanceBetweenYPoints * distanceBetweenYPoints;
                    //double hill = Math.sqrt(sqrt);

                    //double finalSunnyPart = hill * sunnyPart / distanceBetweenYPoints;
                    //sun += finalSunnyPart;
                }
                //highestHill = Math.max(highestHill, points.get(i).y);
            }
            String answer = String.format("%.2f", sun);
            String newAnswer = answer.replace(',', '.');
            System.out.println(newAnswer);
        }
    }

    private class Point implements Comparable<Point> {
        double x;
        double y;

        @Override
        public int compareTo(Point point) {
            int compareX = (int) point.x;
            return (int) (compareX - x);
        }
    }

}
