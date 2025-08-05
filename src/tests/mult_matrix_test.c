#include "s21_matrix_test.h"

START_TEST(test_random_multiplication) {
  int a_rows = rand() % 50 + 1;
  int a_cols = rand() % 50 + 1;
  int b_rows = a_cols;
  int b_cols = rand() % 50 + 1;

  matrix_t A = {0}, B = {0}, expected = {0}, result = {0};
  s21_create_matrix(a_rows, a_cols, &A);
  s21_create_matrix(b_rows, b_cols, &B);
  s21_create_matrix(a_rows, b_cols, &expected);

  for (int i = 0; i < a_rows; i++)
    for (int j = 0; j < a_cols; j++) A.matrix[i][j] = get_rand(-1e9, 1e9);

  for (int i = 0; i < b_rows; i++)
    for (int j = 0; j < b_cols; j++) B.matrix[i][j] = get_rand(-1e9, 1e9);

  for (int i = 0; i < a_rows; i++)
    for (int j = 0; j < b_cols; j++)
      for (int k = 0; k < a_cols; k++)
        expected.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_predefined_multiplication) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  double valsA[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double valsB[3][2] = {{7, 8}, {9, 10}, {11, 12}};
  double valsR[2][2] = {{58, 64}, {139, 154}};

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = valsA[i][j];

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) B.matrix[i][j] = valsB[i][j];

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) expected.matrix[i][j] = valsR[i][j];

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_invalid_size_multiplication) {
  int m = -(rand() % 10 + 1), n = -(rand() % 10 + 1);
  matrix_t A = {0}, B = {0}, result = {0};

  s21_create_matrix(m, n, &A);
  s21_create_matrix(n, m, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_incompatible_matrices) {
  matrix_t A = {0}, B = {0}, result = {0};

  s21_create_matrix(2, 4, &A);
  s21_create_matrix(3, 5, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_mult_matrix() {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc = tcase_create("matrix_mult_tests");

  tcase_add_loop_test(tc, test_random_multiplication, 0, 100);
  tcase_add_loop_test(tc, test_invalid_size_multiplication, 0, 100);
  tcase_add_test(tc, test_incompatible_matrices);
  tcase_add_test(tc, test_predefined_multiplication);

  suite_add_tcase(s, tc);
  return s;
}
