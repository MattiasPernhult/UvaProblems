import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        try {
            new Main().start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void start() throws IOException {

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            int numberOfPoints = Integer.parseInt(reader.readLine().trim());
            if (numberOfPoints == 0) {
                break;
            }

            List<Point> points = new ArrayList<>();
            for (int i = 0; i < numberOfPoints; i++) {
                Point point = new Point();

                StringTokenizer str = new StringTokenizer(reader.readLine());

                point.x = Double.parseDouble(str.nextToken());
                point.y = Double.parseDouble(str.nextToken());

                points.add(point);
            }

            Pair pair = bruteForce(points);
            double distance;

            if (pair != null) {
                distance = pair.distance;
            } else {
                System.out.println("INFINITY");
                continue;
            }

            if (distance > 10000) {
                System.out.println("INFINITY");
            } else {
                String answer = String.format("%.4f", distance);
                String newAnswer = answer.replace(',', '.');
                System.out.println(newAnswer);
            }
        }
    }

    public Pair bruteForce(List<Point> points) {
        int numberOfPoints = points.size();
        if (numberOfPoints < 2) {
            return null;
        }
        Pair pair = new Pair(points.get(0), points.get(1));
        if (numberOfPoints > 2) {
            for (int i = 0; i < numberOfPoints - 1; i++) {
                Point point1 = points.get(i);
                for (int j = i + 1; j < numberOfPoints; j++) {
                    Point point2 = points.get(j);
                    double distance = distance(point1, point2);
                    if (distance < pair.distance) {
                        pair.update(point1, point2, distance);
                    }
                }
            }
        }
        return pair;
    }

    public Pair divideAndConquer(List<Point> points) {
        List<Point> pointsSortedByX = new ArrayList<>(points);
        sortByX(pointsSortedByX);
        List<Point> pointsSortedByY = new ArrayList<>(points);
        sortByY(pointsSortedByY);
        return divideAndConquer(pointsSortedByX, pointsSortedByY);
    }

    private Pair divideAndConquer(List<Point> pointsSortedByX, List<Point> pointsSortedByY) {
        int numberOfPoints = pointsSortedByX.size();
        if (numberOfPoints <= 3) {
            return bruteForce(pointsSortedByX);
        }

        int dividingIndex = numberOfPoints >>> 1;

        List<Point> leftOfCenter = pointsSortedByX.subList(0, dividingIndex);
        List<Point> rightOfCenter = pointsSortedByX.subList(dividingIndex, numberOfPoints);

        List<Point> tempList = new ArrayList<>(leftOfCenter);
        sortByY(tempList);

        Pair closestPair = divideAndConquer(leftOfCenter, tempList);

        tempList.clear();
        tempList.addAll(rightOfCenter);
        sortByY(tempList);
        Pair closestPairRight = divideAndConquer(rightOfCenter, tempList);

        if (closestPairRight.distance < closestPair.distance) {
            closestPair = closestPairRight;
        }

        tempList.clear();

        double shortestDistance = closestPair.distance;
        double centerX = rightOfCenter.get(0).x;

        for (Point point : pointsSortedByY) {
            if (Math.abs(centerX - point.x) < shortestDistance) {
                tempList.add(point);
            }
        }

        for (int i = 0; i < tempList.size() - 1; i++) {
            Point point1 = tempList.get(i);
            for (int j = i + 1; j < tempList.size(); j++) {
                Point point2 = tempList.get(j);
                if ((point2.y - point1.y) >= shortestDistance) {
                    break;
                }
                double distance = distance(point1, point2);
                if (distance < closestPair.distance) {
                    closestPair.update(point1, point2, distance);
                    shortestDistance = distance;
                }
            }
        }

        return closestPair;
    }

    public void sortByX(List<Point> points) {
        Collections.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point point1, Point point2) {
                if (point1.x < point2.x) {
                    return -1;
                }
                if (point1.x > point2.x) {
                    return 1;
                }
                return 0;
            }
        });
    }

    public void sortByY(List<Point> points) {
        Collections.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point point1, Point point2) {
                if (point1.y < point2.y) {
                    return -1;
                }
                if (point1.y > point2.y) {
                    return 1;
                }
                return 0;
            }
        });
    }

    public double distance(Point p1, Point p2) {
        double xDist = Math.abs(p2.x - p1.x);
        double yDist = Math.abs(p2.y - p1.y);
        return Math.sqrt(xDist * xDist + yDist * yDist);
    }

    private class Point {
        double x, y;
    }

    private class Pair {
        Point point1 = null, point2 = null;
        double distance = 0.0;

        public Pair(Point p1, Point p2) {
            this.point1 = p1;
            this.point2 = p2;
            calculateDistance();
        }

        public void update(Point p1, Point p2, double dist) {
            this.point1 = p1;
            this.point2 = p2;
            this.distance = dist;
        }

        public void calculateDistance() {
            this.distance = distance(point1, point2);
        }
    }
}
