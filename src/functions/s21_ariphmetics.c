#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return FAILURE;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
        return FAILURE;
      }
    }
  }

  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return ERROR_CALC;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  for (int i = 0; i < result->rows; ++i) {
    for (int j = 0; j < result->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return SUCCESS;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return ERROR_CALC;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  for (int i = 0; i < result->rows; ++i) {
    for (int j = 0; j < result->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return SUCCESS;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  for (int i = 0; i < result->rows; ++i) {
    for (int j = 0; j < result->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return SUCCESS;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
      B->columns <= 0) {
    return INCORRECT_MATRIX; // 1 или 2 в зависимости от проекта
  }

  if (A->columns != B->rows) {
    return ERROR_CALC;
  }

  if (result->matrix != NULL) {
    s21_remove_matrix(result);
  }
  if (s21_create_matrix(A->rows, B->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < B->columns; ++j) {
      result->matrix[i][j] = 0.0;
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return SUCCESS;
}