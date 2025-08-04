#include "../s21_matrix.h"
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return INCORRECT_MATRIX;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return SUCCESS;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      double det = 0;

      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != SUCCESS) {
        s21_remove_matrix(result);
        return ERROR_CALC;
      }

      for (int k = 0, mi = 0; k < A->rows; k++) {
        if (k == i)
          continue;
        for (int l = 0, mj = 0; l < A->columns; l++) {
          if (l == j)
            continue;
          minor.matrix[mi][mj] = A->matrix[k][l];
          mj++;
        }
        mi++;
      }

      if (s21_determinant(&minor, &det) != SUCCESS) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return ERROR_CALC;
      }

      result->matrix[i][j] = det * ((i + j) % 2 ? -1 : 1);
      s21_remove_matrix(&minor);
    }
  }
  return SUCCESS;
}