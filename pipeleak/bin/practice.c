#include <stdio.h>
#include <stdlib.h>

void print_matrix(const size_t rows, const size_t cols, const double matrix[rows][cols]);
double** create_matrix(const size_t rows, const size_t cols);
void destroy_matrix(double** matrix, const size_t rows);
void test_static_matrix();

int main(void) {
    const size_t rows = 3;
    const size_t cols = 4;
    double** matrix = create_matrix(rows, cols);

    if (matrix == NULL) {
        fprintf(stderr, "Failed to create matrix\n");
        return 1;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = (double)i * cols + j + 0.1;
        }
    }


    for (size_t i = 0; i < rows; ++i) {
        print_matrix(1, cols, (double(*)[cols])matrix[i]);
    }
    printf("\n");

    destroy_matrix(matrix, rows);
    test_static_matrix(); 
    return 0;
}

double** create_matrix(const size_t rows, const size_t cols) {
    double** matrix = calloc(rows, sizeof(double*));
    if (matrix) {
        for (size_t row = 0; row < rows; ++row) {
            if ((matrix[row] = calloc(cols, sizeof(double))) == NULL) {
                destroy_matrix(matrix, rows);
                return NULL;
            }
        }
    }
    return matrix;
}

void destroy_matrix(double** matrix, const size_t rows) {
    if (matrix) {
        for (size_t i = 0; i < rows; ++i) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void print_matrix(const size_t rows, const size_t cols, const double matrix[rows][cols]) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void test_static_matrix() {
    const double matrix[3][4] = {
        {1.1, 1.2, 1.3, 1.4,},
        {2.1, 2.2, 2.3, 2.4,},
        {3.1, 3.2, 3.3, 3.4,},
    };

    print_matrix(3, 4, matrix);
}