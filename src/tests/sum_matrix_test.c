#include "s21_matrix_test.h"

START_TEST(sum_basic_constant_values) {
  matrix_t a = {0}, b = {0}, expected = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);

  a.matrix[0][0] = 2.0;
  b.matrix[0][0] = 3.0;
  expected.matrix[0][0] = 5.0;
  a.matrix[0][1] = 1.5;
  b.matrix[0][1] = 0.5;
  expected.matrix[0][1] = 2.0;
  a.matrix[1][0] = -1.0;
  b.matrix[1][0] = 1.0;
  expected.matrix[1][0] = 0.0;
  a.matrix[1][1] = 4.2;
  b.matrix[1][1] = -2.2;
  expected.matrix[1][1] = 2.0;

  matrix_t res = {0};
  s21_sum_matrix(&a, &b, &res);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_index_based_fill) {
  matrix_t x = {0}, y = {0}, expect = {0};
  s21_create_matrix(4, 4, &x);
  s21_create_matrix(4, 4, &y);
  s21_create_matrix(4, 4, &expect);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) {
      x.matrix[i][j] = i + 1;
      y.matrix[i][j] = j + 1;
      expect.matrix[i][j] = i + j + 2;
    }

  matrix_t out = {0};
  s21_sum_matrix(&x, &y, &out);
  ck_assert_int_eq(s21_eq_matrix(&out, &expect), 1);

  s21_remove_matrix(&x);
  s21_remove_matrix(&y);
  s21_remove_matrix(&expect);
  s21_remove_matrix(&out);
}
END_TEST

START_TEST(sum_invalid_sizes) {
  matrix_t x = {0}, y = {0}, z = {0};
  s21_create_matrix(3, 3, &x);
  s21_create_matrix(1, 5, &y);
  int code = s21_sum_matrix(&x, &y, &z);
  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&x);
  s21_remove_matrix(&y);
}
END_TEST

START_TEST(sum_null_args) {
  matrix_t a = {0}, b = {0}, c = {0};
  int r1 = s21_sum_matrix(NULL, &b, &c);
  int r2 = s21_sum_matrix(&a, NULL, &c);
  int r3 = s21_sum_matrix(&a, &b, NULL);
  ck_assert_int_eq(r1, INCORRECT_MATRIX);
  ck_assert_int_eq(r2, INCORRECT_MATRIX);
  ck_assert_int_eq(r3, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sum_zero_filled) {
  matrix_t x = {0}, y = {0}, z = {0};
  s21_create_matrix(2, 3, &x);
  s21_create_matrix(2, 3, &y);
  s21_create_matrix(2, 3, &z);
  matrix_t out = {0};
  s21_sum_matrix(&x, &y, &out);
  ck_assert_int_eq(s21_eq_matrix(&out, &z), 1);
  s21_remove_matrix(&x);
  s21_remove_matrix(&y);
  s21_remove_matrix(&z);
  s21_remove_matrix(&out);
}
END_TEST

START_TEST(sum_with_negatives) {
  matrix_t a = {0}, b = {0}, expect = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expect);

  a.matrix[0][0] = -1.5;
  b.matrix[0][0] = -0.5;
  expect.matrix[0][0] = -2.0;
  a.matrix[0][1] = 0.0;
  b.matrix[0][1] = -2.0;
  expect.matrix[0][1] = -2.0;
  a.matrix[1][0] = 3.0;
  b.matrix[1][0] = -3.0;
  expect.matrix[1][0] = 0.0;
  a.matrix[1][1] = 5.5;
  b.matrix[1][1] = 1.5;
  expect.matrix[1][1] = 7.0;

  matrix_t sum = {0};
  s21_sum_matrix(&a, &b, &sum);
  ck_assert_int_eq(s21_eq_matrix(&sum, &expect), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expect);
  s21_remove_matrix(&sum);
}
END_TEST

Suite *suite_sum_matrix() {
  Suite *s = suite_create("suite_sum_matrix");
  TCase *tc = tcase_create("case_sum_matrix");

  tcase_add_test(tc, sum_basic_constant_values);
  tcase_add_test(tc, sum_index_based_fill);
  tcase_add_test(tc, sum_invalid_sizes);
  tcase_add_test(tc, sum_null_args);
  tcase_add_test(tc, sum_zero_filled);
  tcase_add_test(tc, sum_with_negatives);

  suite_add_tcase(s, tc);
  return s;
}
