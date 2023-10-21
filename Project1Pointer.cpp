#include <string>
#include <iostream>
#include <chrono>
using namespace std;
class Matrix {       
  public:             
    int rows;
    int cols;        
    float **matrix;
    Matrix operator+(Matrix const& obj) 
    { 
        Matrix res; 
        res = obj;
        return res; 
    } 
};

// create matrix from file
Matrix getMatrixFromUserInput()
{
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

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

    Matrix m;
    m.rows = rows;
    m.cols = cols;

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
    m.matrix = matrix;
    return m;
}

void printMatrix(Matrix m)
{
    printf("Result:\n");
    for (int i = 0; i < m.rows; i++)
    {
        printf("[");
        for (int j = 0; j < m.cols; j++)
        {
            printf("%.2f", *(*(m.matrix + i) + j));
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
    Matrix matrix1;
    matrix1 = getMatrixFromUserInput();

    Matrix matrix2;
    matrix2 = getMatrixFromUserInput();

    Matrix result;
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
            auto start = high_resolution_clock::now();
            result = matrix1 + matrix2;
            auto stop = high_resolution_clock::now();
            if (result == NULL)
            {
                break;
            }
            printMatrix(result);
            duration = duration_cast<nanoseconds>(stop - start);
            printf("Duration: %lldns\n", duration.count());
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            matrix1 = getMatrixFromUserInput();
            matrix2 = getMatrixFromUserInput();
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