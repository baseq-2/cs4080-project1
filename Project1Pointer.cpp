#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
class Matrix
{
public:
    int rows;
    int cols;
    float **matrix;

    Matrix() : rows(0), cols(0), matrix(nullptr) {}

    Matrix operator+(Matrix const &obj)
    {
        Matrix *res = new Matrix();
        if (rows != obj.rows || cols != obj.cols)
        {
            return *res;
        }
        res->rows = rows;
        res->cols = cols;
        float **result;
        result = (float **)malloc(res->rows * sizeof(float *));
        for (int i = 0; i < res->rows; i++)
        {
            *(result + i) = (float *)malloc(res->cols * sizeof(float));
        }
        for (int i = 0; i < res->rows; i++)
        {
            float *row1 = *(matrix + i);
            float *row2 = *(obj.matrix + i);
            float *rowResult = *(result + i);
            for (int j = 0; j < res->cols; j++)
            {
                *(rowResult + j) = *(row1 + j) + *(row2 + j);
            }
        }
        res->matrix = result;
        return *res;
    }
    Matrix operator-(Matrix const &obj)
    {
        Matrix *res = new Matrix();
        if (rows != obj.rows || cols != obj.cols)
        {
            return *res;
        }
        res->rows = rows;
        res->cols = cols;
        float **result;
        result = (float **)malloc(res->rows * sizeof(float *));
        for (int i = 0; i < res->rows; i++)
        {
            *(result + i) = (float *)malloc(res->cols * sizeof(float));
        }
        for (int i = 0; i < res->rows; i++)
        {
            float *row1 = *(matrix + i);
            float *row2 = *(obj.matrix + i);
            float *rowResult = *(result + i);
            for (int j = 0; j < res->cols; j++)
            {
                *(rowResult + j) = *(row1 + j) - *(row2 + j);
            }
        }
        res->matrix = result;
        return *res;
    }
    Matrix operator*(Matrix const &obj)
    {
        Matrix *res = new Matrix();
        if (rows != obj.cols || cols != obj.rows)
        {
            return *res;
        }
        res->rows = rows;
        res->cols = cols;
        float **result;
        result = (float **)malloc(res->rows * sizeof(float *));
        for (int i = 0; i < res->rows; i++)
        {
            *(result + i) = (float *)malloc(res->cols * sizeof(float));
        }
        for (int i = 0; i < res->rows; i++)
        {
            float *row1 = *(matrix + i);
            float *row2 = *(obj.matrix + i);
            float *rowResult = *(result + i);
            for (int j = 0; j < res->cols; j++)
            {
                *(rowResult + j) = *(row1 + j) * *(row2 + j);
            }
        }
        res->matrix = result;
        return *res;
    }
};

// create matrix from file
Matrix getMatrixFromUserInput()
{
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    ifstream f;
    f.open(filename);
    if (!f.is_open())
    {
        std::cerr << "Error: file open failed '" << filename << "'.\n";
        exit(1);
    }

    // read matrix dimensions
    int rows, cols;

    // split line into tokens
    string line, val;
    getline(f, line);
    stringstream s(line);
    getline(s, val, ',');
    rows = stoi(val);
    getline(s, val, ',');
    cols = stoi(val);

    Matrix m;
    m.rows = rows;
    m.cols = cols;

    // create matrix from dimensions
    float **matrix;
    matrix = (float **)malloc(m.rows * sizeof(float *));
    for (int i = 0; i < m.rows; i++)
    {
        *(matrix + i) = (float *)malloc(m.cols * sizeof(float));
    }

    // read matrix values using pointer arithmetic
    for (int i = 0; i < rows; i++)
    {
        getline(f, line);

        // split line into tokens
        stringstream s(line);
        int j = 0;
        while (getline(s, val, ','))
        {
            *(*(matrix + i) + j) = stof(val);
            j++;
        }
    }

    f.close();
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
            if (j < m.cols-1)
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
        {
            // calculate time to complete
            auto start = chrono::high_resolution_clock::now();
            result = matrix1 + matrix2;
            auto stop = chrono::high_resolution_clock::now();
            if (result.matrix == NULL)
            {
                break;
            }
            printMatrix(result);
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            cout << "Duration: " << duration.count() << "ns" << endl;
            break;
        }
        case 2:
        {
            auto start = chrono::high_resolution_clock::now();
            result = matrix1 - matrix2;
            auto stop = chrono::high_resolution_clock::now();
            if (result.matrix == NULL)
            {
                break;
            }
            printMatrix(result);
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            cout << "Duration: " << duration.count() << "ns" << endl;
            break;
        }
        case 3:
        {
            auto start = chrono::high_resolution_clock::now();
            result = matrix1 * matrix2;
            auto stop = chrono::high_resolution_clock::now();
            if (result.matrix == NULL)
            {
                break;
            }
            printMatrix(result);
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            cout << "Duration: " << duration.count() << "ns" << endl;
            break;
        }
        case 4:
        {
            matrix1 = getMatrixFromUserInput();
            matrix2 = getMatrixFromUserInput();
            break;
        }
        case 5:
        {
            exit = 1;
            break;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
    return 0;
}