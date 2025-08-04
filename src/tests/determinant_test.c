#include "s21_matrix_test.h"

START_TEST(test_det_all_same_columns) {
  int n = 5;
  matrix_t mat = {0};
  s21_create_matrix(n, n, &mat);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat.matrix[i][j] = j;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_linearly_dependent) {
  int n = 4;
  matrix_t mat = {0};
  s21_create_matrix(n, n, &mat);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat.matrix[i][j] = i + j;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_known_large_result) {
  int n = 5;
  matrix_t mat = {0};
  s21_create_matrix(n, n, &mat);

  mat.matrix[0][1] = 6;
  mat.matrix[0][2] = -2;
  mat.matrix[0][3] = -1;
  mat.matrix[0][4] = 5;
  mat.matrix[1][3] = -9;
  mat.matrix[1][4] = -7;
  mat.matrix[2][1] = 15;
  mat.matrix[2][2] = 35;
  mat.matrix[3][1] = -1;
  mat.matrix[3][2] = -11;
  mat.matrix[3][3] = -2;
  mat.matrix[3][4] = 1;
  mat.matrix[4][0] = -2;
  mat.matrix[4][1] = -2;
  mat.matrix[4][2] = 3;
  mat.matrix[4][4] = -2;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, 2480.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_standard_case_3x3) {
  matrix_t mat = {0};
  s21_create_matrix(3, 3, &mat);

  mat.matrix[0][0] = 2;
  mat.matrix[0][1] = 3;
  mat.matrix[0][2] = 1;
  mat.matrix[1][0] = 7;
  mat.matrix[1][1] = 4;
  mat.matrix[1][2] = 1;
  mat.matrix[2][0] = 9;
  mat.matrix[2][1] = -2;
  mat.matrix[2][2] = 1;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, -32.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_2x2_negative_values) {
  matrix_t mat = {0};
  s21_create_matrix(2, 2, &mat);

  mat.matrix[0][0] = -5;
  mat.matrix[0][1] = -4;
  mat.matrix[1][0] = -2;
  mat.matrix[1][1] = -3;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, 7.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_single_element) {
  matrix_t mat = {0};
  s21_create_matrix(1, 1, &mat);
  mat.matrix[0][0] = -5;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_double_eq_tol(result, -5.0, 1e-6);
  ck_assert_int_eq(status, OK);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_invalid_size_negative) {
  matrix_t mat = {0};
  int n = -(rand() % 100 + 1);
  s21_create_matrix(n, n, &mat);

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_det_non_square_matrix) {
  matrix_t mat = {0};
  int r = 4, c = 5;
  s21_create_matrix(r, c, &mat);

  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      mat.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;

  double result = 0;
  int status = s21_determinant(&mat, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&mat);
}
END_TEST

Suite *suite_determinant() {
  Suite *s = suite_create("determinant_tests");
  TCase *tc = tcase_create("determinant_case");

  tcase_add_test(tc, test_det_all_same_columns);
  tcase_add_test(tc, test_det_linearly_dependent);
  tcase_add_test(tc, test_det_known_large_result);
  tcase_add_test(tc, test_det_standard_case_3x3);
  tcase_add_test(tc, test_det_2x2_negative_values);
  tcase_add_test(tc, test_det_single_element);
  tcase_add_loop_test(tc, test_det_invalid_size_negative, 0, 100);
  tcase_add_test(tc, test_det_non_square_matrix);

  suite_add_tcase(s, tc);
  return s;
}
