#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct Dimension
{
    int rows;
    int cols;
};

// create matrix from file
float **getMatrixFromUserInput(struct Dimension *dim)
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

    dim->rows = rows;
    dim->cols = cols;

    // create matrix from dimensions
    float **matrix;
    matrix = (float **)malloc(dim->rows * sizeof(float *));
    for (int i = 0; i < dim->rows; i++)
    {
        *(matrix + i) = (float *)malloc(dim->cols * sizeof(float));
    }

    // read matrix values using pointer arithmetic
    for (int i = 0; i < rows; i++)
    {
        char line[1000];
        fgets(line, 1000, file);

        // split line into tokens
        char *token = strtok(line, ",");
        int j = 0;
        while (token != NULL)
        {
            *(*(matrix + i) + j) = atof(token);
            token = strtok(NULL, ",");
            j++;
        }
    }

    fclose(file);
    return matrix;
}

// add two matrices using pointer arithmetic
float** addMatrices(float **matrix1, float **matrix2, struct Dimension *dim, int rows1, int cols1, int rows2, int cols2)
{
    // check if dimensions are valid
    if (rows1 != rows2 || cols1 != cols2)
    {
        printf("Invalid matrix dimensions\n");
        return NULL;
    }

    dim->rows = rows1;
    dim->cols = cols1;
    float **result;
    result = (float **)malloc(dim->rows * sizeof(float *));
    for (int i = 0; i < dim->rows; i++)
    {
        *(result + i) = (float *)malloc(dim->cols * sizeof(float));
    }

    for (int i = 0; i < dim->rows; i++) {
        float *row1 = *(matrix1+i);
        float *row2 = *(matrix2+i);
        float *rowResult = *(result+i);
        for (int j = 0; j < dim->cols; j++) {
            *(rowResult+j) = *(row1+j) + *(row2+j);
        }
    }
    return result;
}

// subtract two matrices using pointer arithmetic
float** subtractMatrices(float **matrix1, float **matrix2, struct Dimension *dim, int rows1, int cols1, int rows2, int cols2)
{
    // check if dimensions are valid
    if (rows1 != rows2 || cols1 != cols2)
    {
        printf("Invalid matrix dimensions\n");
        return NULL;
    }

    dim->rows = rows1;
    dim->cols = cols1;
    float **result;
    result = (float **)malloc(dim->rows * sizeof(float *));
    for (int i = 0; i < dim->rows; i++)
    {
        *(result + i) = (float *)malloc(dim->cols * sizeof(float));
    }

    for (int i = 0; i < dim->rows; i++) {
        float *row1 = *(matrix1+i);
        float *row2 = *(matrix2+i);
        float *rowResult = *(result+i);
        for (int j = 0; j < dim->cols; j++) {
            *(rowResult+j) = *(row1+j) - *(row2+j);
        }
    }
    return result;
}

// multiply two matrices using pointer arithmetic
float** multiplyMatrices(float **matrix1, float **matrix2, struct Dimension *dim, int rows1, int cols1, int rows2, int cols2)
{
    if (cols1 != rows2)
    {
        printf("Invalid matrix dimensions\n");
        return NULL;
    }

    dim->rows = rows1;
    dim->cols = cols2;
    float **result;
    result = (float **)malloc(dim->rows * sizeof(float *));
    for (int i = 0; i < dim->rows; i++)
    {
        *(result + i) = (float *)malloc(dim->cols * sizeof(float));
    }

    for (int i = 0; i < dim->rows; i++) {
        float *row1 = *(matrix1+i);
        float *rowResult = *(result+i);
        for (int j = 0; j < dim->cols; j++) {
            float sum = 0;
            for (int k = 0; k < cols1; k++) {
                sum += *(row1+k) * *(*(matrix2+k)+j);
            }
            *(rowResult+j) = sum;
        }
    }
    return result;
}

void printMatrix(float **matrix, int rows, int cols)
{
    printf("Result:\n");
    for (int i = 0; i < rows; i++)
    {
        printf("[");
        for (int j = 0; j < cols; j++)
        {
            printf("%.2f", *(*(matrix + i) + j));
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
    struct Dimension dim1;
    float **matrix1;
    matrix1 = getMatrixFromUserInput(&dim1);

    struct Dimension dim2;
    float **matrix2;
    matrix2 = getMatrixFromUserInput(&dim2);

    float **result;
    struct Dimension dim3;
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
            result = addMatrices(matrix1, matrix2, &dim3, dim1.rows, dim1.cols, dim2.rows, dim2.cols);
            clock_gettime(CLOCK_REALTIME, &end);
            if (result == NULL)
            {
                break;
            }
            printMatrix(result, dim3.rows, dim3.cols);
            free(result);
            duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
            printf("Duration: %lldns\n", duration);
            break;
        case 2:
            clock_gettime(CLOCK_REALTIME, &start);
            result = subtractMatrices(matrix1, matrix2, &dim3, dim1.rows, dim1.cols, dim2.rows, dim2.cols);
            clock_gettime(CLOCK_REALTIME, &end);
            if (dim3.rows == 0 && dim3.cols == 0)
            {
                break;
            }
            printMatrix(result, dim3.rows, dim3.cols);
            free(result);
            break;
        case 3:
            clock_gettime(CLOCK_REALTIME, &start);
            result = multiplyMatrices(matrix1, matrix2, &dim3, dim1.rows, dim1.cols, dim2.rows, dim2.cols);
            clock_gettime(CLOCK_REALTIME, &end);
            if (dim3.rows == 0 && dim3.cols == 0)
            {
                break;
            }
            printMatrix(result, dim3.rows, dim3.cols);
            free(result);
            duration = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
            printf("Duration: %lldns\n", duration);
            break;
        case 4:
            free(matrix1);
            free(matrix2);
            matrix1 = getMatrixFromUserInput(&dim1);
            matrix2 = getMatrixFromUserInput(&dim2);
            break;
        case 5:
            exit = 1;
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    free(matrix1);
    free(matrix2);
    return 0;
}