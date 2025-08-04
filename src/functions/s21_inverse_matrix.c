#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return INCORRECT_MATRIX;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != SUCCESS) {
    return ERROR_CALC;
  }

  if (A->rows == 1) {
    if (A->matrix[0][0] == 0.0) {
      return ERROR_CALC;
    }
    result->matrix[0][0] = 1 / A->matrix[0][0];
    return SUCCESS;
  }

  matrix_t complements;
  if (s21_calc_complements(A, &complements) != SUCCESS) {
    return ERROR_CALC;
  }

  double determinant = 0.0;

  if (s21_determinant(A, &determinant) != SUCCESS || determinant == 0.0) {
    s21_remove_matrix(&complements);
    return ERROR_CALC;
  }

  if (s21_transpose(&complements, result) != SUCCESS) {
    s21_remove_matrix(&complements);
    return ERROR_CALC;
  }

  s21_remove_matrix(&complements);

  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = result->matrix[i][j] / determinant;
    }
  }

  return SUCCESS;
}