#include "s21_matrix_test.h"

START_TEST(test_creation_valid_size) {
  int r = (rand() % 50) + 1;
  int c = (rand() % 50) + 1;
  matrix_t mat = {0};
  int code = s21_create_matrix(r, c, &mat);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(mat.rows, r);
  ck_assert_int_eq(mat.columns, c);
  for (int x = 0; x < r; ++x) {
    for (int y = 0; y < c; ++y) {
      ck_assert_ldouble_eq_tol(mat.matrix[x][y], 0.0, 1e-7);
    }
  }
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_creation_zero_rows) {
  int r = 0, c = 5;
  matrix_t m = {0};
  int result = s21_create_matrix(r, c, &m);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_creation_zero_columns) {
  int r = 5, c = 0;
  matrix_t m = {0};
  int result = s21_create_matrix(r, c, &m);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_create_matrix() {
  Suite *s = suite_create("create_matrix_tests");
  TCase *tc = tcase_create("matrix_creation");

  tcase_add_test(tc, test_creation_valid_size);
  tcase_add_test(tc, test_creation_zero_rows);
  tcase_add_test(tc, test_creation_zero_columns);

  suite_add_tcase(s, tc);
  return s;
}
