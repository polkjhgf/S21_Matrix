#include "../s21_matrix.h"

double recurcive_determinant(matrix_t *A, int n) {
  if (n == 1) {
    return A->matrix[0][0];
  } else if (n == 2) {
    return A->matrix[0][0] * A->matrix[1][1] -
           A->matrix[1][0] * A->matrix[0][1];
  } else {
    double det = 0;
    for (int k = 0; k < n; ++k) {
      matrix_t submatrix;

      // Где 0 - это строка, а k - это столбец, то есть первая строка, Нулевая
      // строка и катый элемент
      double letter = A->matrix[0][k];

      if (s21_create_matrix(n - 1, n - 1, &submatrix) != SUCCESS) {
        return 0.0;
      }

      int A_row = 0;

      for (int i = 0; i < n; ++i) {
        if (i == 0)
          continue;
        int A_col = 0;

        for (int j = 0; j < n; ++j) {
          if (j == k)
            continue;

          submatrix.matrix[A_row][A_col] = A->matrix[i][j];
          A_col++;
        }

        A_row++;
      }

      int sign = 1;
      if (k % 2 != 0) {
        sign = -1;
      }

      det += sign * letter * recurcive_determinant(&submatrix, n - 1);

      s21_remove_matrix(&submatrix);
    }

    return det;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }
  if (A->rows != A->columns) {
    return ERROR_CALC;
  }
  *result = recurcive_determinant(A, A->rows);
  return SUCCESS;
}