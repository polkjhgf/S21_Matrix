#include "s21_matrix_test.h"

START_TEST(test_copy_null_a) {
  matrix_t B;
  ck_assert_int_eq(s21_copy_matrix(NULL, &B), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_copy_null_b) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_copy_matrix(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_copy_null_matrix_a) {
  matrix_t A = {0};
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_copy_null_matrix_b) {
  matrix_t A;
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_copy_invalid_rows_a) {
  matrix_t A;
  matrix_t B;
  A.rows = 0;
  A.columns = 2;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_copy_invalid_columns_a) {
  matrix_t A;
  matrix_t B;
  A.rows = 2;
  A.columns = -1;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_copy_invalid_rows_b) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 2, &A);
  B.rows = 0;
  B.columns = 2;
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_copy_invalid_columns_b) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 2, &A);
  B.rows = 2;
  B.columns = 0;
  ck_assert_int_eq(s21_copy_matrix(&A, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_copy_different_dimensions) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_copy_matrix(&A, &B), ERROR_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_copy_success) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Fill matrix A with some values
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
    }
  }

  ck_assert_int_eq(s21_copy_matrix(&A, &B), SUCCESS);

  // Verify the copy
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(A.matrix[i][j], B.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_copy_matrix() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_copy_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_copy_null_a);
  tcase_add_test(tc_core, test_copy_null_b);
  tcase_add_test(tc_core, test_copy_null_matrix_a);
  tcase_add_test(tc_core, test_copy_null_matrix_b);
  tcase_add_test(tc_core, test_copy_invalid_rows_a);
  tcase_add_test(tc_core, test_copy_invalid_columns_a);
  tcase_add_test(tc_core, test_copy_invalid_rows_b);
  tcase_add_test(tc_core, test_copy_invalid_columns_b);
  tcase_add_test(tc_core, test_copy_different_dimensions);
  tcase_add_test(tc_core, test_copy_success);

  suite_add_tcase(s, tc_core);
  return s;
}