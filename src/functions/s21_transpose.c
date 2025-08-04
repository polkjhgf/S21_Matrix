#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows < 1 ||
      A->columns < 1) {
    return INCORRECT_MATRIX;
  }

  if (s21_create_matrix(A->columns, A->rows, result) != SUCCESS) {
    return ERROR_CALC;
  }

  for (int i = 0; i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return SUCCESS;
}