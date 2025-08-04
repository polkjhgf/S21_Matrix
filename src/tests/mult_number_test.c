#include "s21_matrix_test.h"

START_TEST(zero_multiplier_check) {
  matrix_t original = {0};
  matrix_t expected = {0};
  matrix_t actual = {0};
  s21_create_matrix(2, 2, &original);
  s21_create_matrix(2, 2, &expected);

  original.matrix[0][0] = 1.5;
  original.matrix[0][1] = 2.5;
  original.matrix[1][0] = 3.5;
  original.matrix[1][1] = 4.5;

  s21_mult_number(&original, 0, &actual);

  ck_assert_int_eq(s21_eq_matrix(&actual, &expected), SUCCESS);

  s21_remove_matrix(&original);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&actual);
}
END_TEST

START_TEST(negative_multiplier_check) {
  matrix_t original = {0};
  matrix_t expected = {0};
  matrix_t actual = {0};
  s21_create_matrix(2, 3, &original);
  s21_create_matrix(2, 3, &expected);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      original.matrix[i][j] = (i + 1) * (j + 1);
      expected.matrix[i][j] = -original.matrix[i][j];
    }
  }

  s21_mult_number(&original, -1, &actual);

  ck_assert_int_eq(s21_eq_matrix(&actual, &expected), SUCCESS);

  s21_remove_matrix(&original);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&actual);
}
END_TEST

START_TEST(null_matrix_handling) {
  int error_code = s21_mult_number(NULL, 10, NULL);
  ck_assert_int_eq(error_code, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_mult_number_matrix() {
  Suite *s = suite_create("Number Multiplication");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, zero_multiplier_check);
  tcase_add_test(tc, negative_multiplier_check);
  tcase_add_test(tc, null_matrix_handling);

  suite_add_tcase(s, tc);
  return s;
}