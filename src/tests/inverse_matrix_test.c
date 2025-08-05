#include "s21_matrix_test.h"

START_TEST(inverse_matrix_valid) {
  matrix_t mat, expected, result;
  s21_create_matrix(3, 3, &mat);
  s21_create_matrix(3, 3, &expected);

  double data[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double inv_data[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      mat.matrix[i][j] = data[i][j];
      expected.matrix[i][j] = inv_data[i][j];
    }

  ck_assert_int_eq(s21_inverse_matrix(&mat, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_unit_matrix) {
  matrix_t unit, result;
  s21_create_matrix(3, 3, &unit);

  for (int i = 0; i < 3; i++) unit.matrix[i][i] = 1.0;

  ck_assert_int_eq(s21_inverse_matrix(&unit, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&unit, &result), SUCCESS);

  s21_remove_matrix(&unit);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_singular_matrix) {
  matrix_t singular, result;
  s21_create_matrix(2, 2, &singular);
  singular.matrix[0][0] = 1;
  singular.matrix[0][1] = 2;
  singular.matrix[1][0] = 2;
  singular.matrix[1][1] = 4;

  ck_assert_int_eq(s21_inverse_matrix(&singular, &result), CALCULATION_ERROR);
  s21_remove_matrix(&singular);
}
END_TEST

START_TEST(inverse_non_square_matrix) {
  matrix_t m, result;
  s21_create_matrix(2, 3, &m);
  ck_assert_int_eq(s21_inverse_matrix(&m, &result), CALCULATION_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_null_input) {
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_zero_size_matrix) {
  matrix_t m = {0}, result = {0};
  m.rows = 0;
  m.columns = 0;
  ck_assert_int_eq(s21_inverse_matrix(&m, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_single_element_valid) {
  matrix_t m, result, expected;
  s21_create_matrix(1, 1, &m);
  s21_create_matrix(1, 1, &expected);

  m.matrix[0][0] = 2.0;
  expected.matrix[0][0] = 0.5;

  ck_assert_int_eq(s21_inverse_matrix(&m, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_single_element_zero) {
  matrix_t m, result;
  s21_create_matrix(1, 1, &m);

  m.matrix[0][0] = 0.0;

  ck_assert_int_eq(s21_inverse_matrix(&m, &result), CALCULATION_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, inverse_matrix_valid);
  tcase_add_test(tc, inverse_unit_matrix);
  tcase_add_test(tc, inverse_singular_matrix);
  tcase_add_test(tc, inverse_non_square_matrix);
  tcase_add_test(tc, inverse_null_input);
  tcase_add_test(tc, inverse_zero_size_matrix);
  tcase_add_test(tc, inverse_single_element_valid);
  tcase_add_test(tc, inverse_single_element_zero);
  suite_add_tcase(s, tc);
  return s;
}
