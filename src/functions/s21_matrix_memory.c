#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return INCORRECT_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;

  result->matrix = (double **)malloc(rows * sizeof(*(result->matrix)));

  for (int i = 0; i < rows; ++i) {
    result->matrix[i] = calloc(columns, sizeof(**result->matrix));

    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; ++j) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return ERROR_CALC;
    }
  }

  return SUCCESS;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    free(A->matrix[i]);
  }

  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_copy_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
    return INCORRECT_MATRIX;
  if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1)
    return INCORRECT_MATRIX;
  if (B->rows != A->rows || B->columns != A->columns) return ERROR_CALC;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
  return SUCCESS;
}