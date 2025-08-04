#include "s21_matrix_test.h"

START_TEST(calc_complements_single_element) {
  matrix_t m = {0}, res = {0};
  s21_create_matrix(1, 1, &m);
  m.matrix[0][0] = 5;

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(res.matrix[0][0], 1);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_null_input) {
  matrix_t m = {0}, res = {0};
  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_non_square) {
  matrix_t m = {0}, res = {0};
  s21_create_matrix(2, 3, &m);

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_standard_3x3) {
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &expected);

  double input[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};

  double answer[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) {
      m.matrix[i][j] = input[i][j];
      expected.matrix[i][j] = answer[i][j];
    }

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_2x2) {
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(2, 2, &m);
  s21_create_matrix(2, 2, &expected);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[1][0] = 3;
  m.matrix[1][1] = 4;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = -3;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = 1;

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_negative_elements) {
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &expected);

  double input[3][3] = {{1, -2, 3}, {0, 4, 2}, {-5, 2, 1}};

  double answer[3][3] = {{0, -10, 20}, {8, 16, -8}, {-16, -2, 4}};

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) {
      m.matrix[i][j] = input[i][j];
      expected.matrix[i][j] = answer[i][j];
    }

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), 0);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_single_zero) {
  matrix_t m = {0}, res = {0};
  s21_create_matrix(1, 1, &m);
  m.matrix[0][0] = 0;

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(res.matrix[0][0], 1);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_zero_determinant) {
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &expected);

  double input[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  double answer[3][3] = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) {
      m.matrix[i][j] = input[i][j];
      expected.matrix[i][j] = answer[i][j];
    }

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_2x2_negative) {
  matrix_t m = {0}, res = {0}, expected = {0};
  s21_create_matrix(2, 2, &m);
  s21_create_matrix(2, 2, &expected);

  m.matrix[0][0] = -1;
  m.matrix[0][1] = -2;
  m.matrix[1][0] = -3;
  m.matrix[1][1] = -4;

  expected.matrix[0][0] = -4;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = -1;

  int status = s21_calc_complements(&m, &res);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc = tcase_create("complements_tests");

  tcase_add_test(tc, calc_complements_standard_3x3);
  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_2x2_negative);
  tcase_add_test(tc, calc_complements_negative_elements);
  tcase_add_test(tc, calc_complements_zero_determinant);
  tcase_add_test(tc, calc_complements_non_square);
  tcase_add_test(tc, calc_complements_null_input);
  tcase_add_test(tc, calc_complements_single_element);
  tcase_add_test(tc, calc_complements_single_zero);

  suite_add_tcase(s, tc);
  return s;
}
