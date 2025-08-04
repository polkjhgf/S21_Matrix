#include "./s21_matrix_test.h"

START_TEST(test_equal_random_matrix) {
  int rows = rand() % 50 + 1;
  int cols = rand() % 50 + 1;
  matrix_t a = {0}, b = {0};
  s21_create_matrix(rows, cols, &a);
  s21_create_matrix(rows, cols, &b);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j) {
      double val = get_rand(-1000, 1000);
      a.matrix[i][j] = val;
      b.matrix[i][j] = val;
    }
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_diff_size_matrix) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(4, 4, &b);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_invalid_matrix_input) {
  matrix_t a = {0}, b = {0};
  int rows = -(rand() % 10 + 1);
  int cols = -(rand() % 10 + 1);
  s21_create_matrix(rows, cols, &a);
  s21_create_matrix(3, 3, &b);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_null_matrix_structs) {
  matrix_t a = {0}, b = {0};
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
}
END_TEST

START_TEST(test_zero_sized_matrix) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(0, 0, &a);
  s21_create_matrix(0, 0, &b);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_single_equal_elements) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = 3.1415;
  b.matrix[0][0] = 3.1415;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_single_diff_elements) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = 1.0;
  b.matrix[0][0] = 2.0;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_equal_2x2_matrix) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  double values[2][2] = {{1, 2}, {3, 4}};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      a.matrix[i][j] = b.matrix[i][j] = values[i][j];
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_approx_equal_values) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1.000000001;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  b.matrix[0][0] = 1.0;
  b.matrix[0][1] = 2.0;
  b.matrix[1][0] = 3.0;
  b.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(test_too_different_values) {
  matrix_t a = {0}, b = {0};
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1.01;
  a.matrix[0][1] = 2;
  a.matrix[1][0] = 3;
  a.matrix[1][1] = 4;
  b.matrix[0][0] = 1.0;
  b.matrix[0][1] = 2;
  b.matrix[1][0] = 3;
  b.matrix[1][1] = 4;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

Suite *suite_eq_matrix() {
  Suite *s = suite_create("matrix_equality_tests");
  TCase *tc = tcase_create("equality_case");

  tcase_add_loop_test(tc, test_equal_random_matrix, 0, 100);
  tcase_add_test(tc, test_diff_size_matrix);
  tcase_add_test(tc, test_invalid_matrix_input);
  tcase_add_test(tc, test_null_matrix_structs);
  tcase_add_test(tc, test_zero_sized_matrix);
  tcase_add_test(tc, test_single_equal_elements);
  tcase_add_test(tc, test_single_diff_elements);
  tcase_add_test(tc, test_equal_2x2_matrix);
  tcase_add_test(tc, test_approx_equal_values);
  tcase_add_test(tc, test_too_different_values);

  suite_add_tcase(s, tc);
  return s;
}
