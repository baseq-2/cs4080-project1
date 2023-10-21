#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// create matrix from file
void getMatrixFromUserInput(float matrix[100][100])
{
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // read matrix dimensions
    int rows, cols;
    char line[1000];
    fgets(line, 1000, file);

    // split line into tokens
    char *token = strtok(line, ",");
    rows = atoi(token);
    token = strtok(NULL, ",");
    cols = atoi(token);

    for (int i = 0; i < 100; i++)
    {
        char line[1000];
        fgets(line, 1000, file);

        // split line into tokens
        char *token = strtok(line, ",");
        int j = 0;
        while (token != NULL)
        {
            matrix[i][j] = atof(token);
            token = strtok(NULL, ",");
            j++;
        }
    }

    fclose(file);
}

// add two matrices using pointer arithmetic
void addMatrices(float matrix1[100][100], float matrix2[100][100], float result[100][100], int rows, int cols)
{
    // check if dimensions are valid
    if (rows != cols)
    {
        printf("Invalid matrix dimensions\n");
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        float *row1 = (float *)matrix1 + i * rows;
        float *row2 = (float *)matrix2 + i * rows;
        float *rowResult = (float *)result + i * rows;

        for (int j = 0; j < cols; j++)
        {
            *(rowResult + j) = *(row1 + j) + *(row2 + j);
        }
    }
}

// subtract two matrices using pointer arithmetic
void subtractMatrices(float matrix1[100][100], float matrix2[100][100], float result[100][100], int rows, int cols)
{
    // check if dimensions are valid
    if (rows != cols)
    {
        printf("Invalid matrix dimensions\n");
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        float *row1 = (float *)matrix1 + i * rows;
        float *row2 = (float *)matrix2 + i * rows;
        float *rowResult = (float *)result + i * rows;

        for (int j = 0; j < cols; j++)
        {
            *(rowResult + j) = *(row1 + j) - *(row2 + j);
        }
    }
}

// multiply two matrices using pointer arithmetic
void multiplyMatrices(float matrix1[100][100], float matrix2[100][100], float result[100][100], int rows1, int cols1, int rows2, int cols2)
{
    if (cols1 != rows2)
    {
        printf("Invalid matrix dimensions\n");
        return;
    }

    for (int i = 0; i < rows1; i++)
    {
        float *row1 = (float *)matrix1 + i * rows1;
        float *rowResult = (float *)result + i * rows1;

        for (int j = 0; j < cols2; j++)
        {
            float sum = 0;
            for (int k = 0; k < cols1; k++)
            {
                sum += *(row1 + k) * *((float *)matrix2 + k * rows2 + j);
            }
            *(rowResult + j) = sum;
        }
    }
}

void printMatrix(float matrix[100][100], int rows, int cols)
{
    printf("Result:\n");
    for (int i = 0; i < rows; i++)
    {
        printf("[");
        for (int j = 0; j < cols; j++)
        {
            printf("%.2f", *((float *)matrix + i * rows + j));

            if (j != 99)
            {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main()
{
    float matrix1[100][100];
    float matrix2[100][100];

    getMatrixFromUserInput(matrix1);
    getMatrixFromUserInput(matrix2);

    float result[100][100];
    int exit = 0;
    struct timespec start, end;
    long long duration;
    while (exit == 0)
    {
        printf("\nSelect an operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Select new matrices\n");
        printf("5. Exit\n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // calculate time to complete
            clock_gettime(CLOCK_REALTIME, &start);
            addMatrices(matrix1, matrix2, result, 100, 100);
            clock_gettime(CLOCK_REALTIME, &end);
            printMatrix(result, 100, 100);
            duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
            printf("Duration: %lldns\n", duration);
            break;
        case 2:
            clock_gettime(CLOCK_REALTIME, &start);
            subtractMatrices(matrix1, matrix2, result, 100, 100);
            clock_gettime(CLOCK_REALTIME, &end);
            printMatrix(result, 100, 100);
            break;
        case 3:
            clock_gettime(CLOCK_REALTIME, &start);
            multiplyMatrices(matrix1, matrix2, result, 100, 100, 100, 100);
            clock_gettime(CLOCK_REALTIME, &end);
            printMatrix(result, 100, 100);
            duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
            printf("Duration: %lldns\n", duration);
            break;
        case 4:
            getMatrixFromUserInput(matrix1);
            getMatrixFromUserInput(matrix2);
            break;
        case 5:
            exit = 1;
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}