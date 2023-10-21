import java.util.Arrays;
import java.util.Scanner;
import java.io.File;
import java.time.Duration;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;

public class Project1 {
    private static Scanner scanner = new Scanner(System.in);

    private static float[][] getMatrixFromUserInput() {
        System.out.print("Enter file name: ");
        String fileName = scanner.next();
        Scanner file = null;
        try {
            file = new Scanner(new File(fileName));
        } catch (java.io.FileNotFoundException e) {
            System.out.println("File not found.");
            System.exit(1);
        }

        String[] dimensions = file.nextLine().split(",");
        int rows = Integer.parseInt(dimensions[0]);
        int columns = Integer.parseInt(dimensions[1]);

        float[][] matrix = new float[rows][columns];

        for (int i = 0; i < rows; i++) {
            String[] row = file.nextLine().split(",");
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = Float.parseFloat(row[j]);
            }
        }
        return matrix;
    }

    public static void main(String[] args) {
        float[][] matrix1 = getMatrixFromUserInput();
        float[][] matrix2 = getMatrixFromUserInput();

        Matrix m1 = new Matrix(matrix1);
        Matrix m2 = new Matrix(matrix2);

        boolean exit = false;
        while (!exit) {
            System.out.println("\nSelect an operation:");
            System.out.println("1. Addition");
            System.out.println("2. Subtraction");
            System.out.println("3. Multiplication");
            System.out.println("4. Select new matrices");
            System.out.println("5. Exit");

            int choice = scanner.nextInt();
            Matrix result;
            LocalTime start = LocalTime.now();
            switch (choice) {
                case 1:
                    result = m1.add(m2);
                    if (result == null) {
                        break;
                    }
                    System.out.println("Result:");
                    System.out.println(result);
                    break;
                case 2:
                    result = m1.subtract(m2);
                    if (result == null) {
                        break;
                    }
                    System.out.println("Result:");
                    System.out.println(result);
                    break;
                case 3:
                    result = m1.multiply(m2);
                    if (result == null) {
                        break;
                    }
                    System.out.println("Result:");
                    System.out.println(result);
                    break;
                case 4:
                    matrix1 = getMatrixFromUserInput();
                    matrix2 = getMatrixFromUserInput();

                    m1 = new Matrix(matrix1);
                    m2 = new Matrix(matrix2);
                    break;
                case 5:
                    exit = true;
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
            LocalTime end = LocalTime.now();
            System.out.println("Duration: "+Duration.between(start, end).getNano()+"ns");
        }
    }

    private static class Matrix {
        private float[][] matrix;

        public Matrix(float[][] matrix) {
            this.matrix = matrix;
        }

        public Matrix add(Matrix matrix2) {
            if (matrix.length != matrix2.matrix.length || matrix[0].length != matrix2.matrix[0].length) {
                System.out.println("Matrices are not compatible.");
                return null;
            }

            float[][] result = new float[matrix.length][matrix[0].length];
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    result[i][j] = matrix[i][j] + matrix2.matrix[i][j];
                }
            }
            return new Matrix(result);
        }

        public Matrix subtract(Matrix matrix2) {
            if (matrix.length != matrix2.matrix.length || matrix[0].length != matrix2.matrix[0].length) {
                System.out.println("Matrices are not compatible.");
            }

            float[][] result = new float[matrix.length][matrix[0].length];
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    result[i][j] = matrix[i][j] - matrix2.matrix[i][j];
                }
            }
            return new Matrix(result);
        }

        public Matrix multiply(Matrix matrix2) {
            if (matrix[0].length != matrix2.matrix.length) {
                System.out.println("Matrices are not compatible.");
                return null;
            }

            float[][] result = new float[matrix.length][matrix2.matrix[0].length];
            // iterate through the rows of the first matrix
            for (int i = 0; i < matrix.length; i++) {
                // iterate through the columns of the second matrix
                for (int j = 0; j < matrix2.matrix[0].length; j++) {
                    // iterate through the columns of the first matrix
                    for (int k = 0; k < matrix[0].length; k++) {
                        result[i][j] += matrix[i][k] * matrix2.matrix[k][j];
                    }
                }
            }
            return new Matrix(result);
        }

        public String toString() {
            String result = "";
            for (int i = 0; i < matrix.length; i++) {
                result += Arrays.toString(matrix[i]) + "\n";
            }
            return result;
        }
    }
}