#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class S21MatrixTest : public testing::Test {
 protected:
  S21Matrix *matrix_3x3;
  S21Matrix *matrix_4x3;
  S21Matrix *matrix_temp;

  void SetUp() {
    matrix_3x3 = new S21Matrix();
    matrix_3x3->operator()(0, 0) = 0;
    matrix_3x3->operator()(0, 1) = 1;
    matrix_3x3->operator()(0, 2) = 2;
    matrix_3x3->operator()(1, 0) = 3;
    matrix_3x3->operator()(1, 1) = 4;
    matrix_3x3->operator()(1, 2) = 5;
    matrix_3x3->operator()(2, 0) = 6;
    matrix_3x3->operator()(2, 1) = 7;
    matrix_3x3->operator()(2, 2) = 8;

    matrix_4x3 = new S21Matrix(4, 3);
    matrix_4x3->operator()(0, 0) = 0;
    matrix_4x3->operator()(0, 1) = 1;
    matrix_4x3->operator()(0, 2) = 2;
    matrix_4x3->operator()(1, 0) = 3;
    matrix_4x3->operator()(1, 1) = 4;
    matrix_4x3->operator()(1, 2) = 5;
    matrix_4x3->operator()(2, 0) = 6;
    matrix_4x3->operator()(2, 1) = 7;
    matrix_4x3->operator()(2, 2) = 8;
    matrix_4x3->operator()(3, 0) = 9;
    matrix_4x3->operator()(3, 1) = 10;
    matrix_4x3->operator()(3, 2) = 11;
  }

  void TearDown() {
    delete matrix_3x3;
    delete matrix_4x3;
  }
};

TEST_F(S21MatrixTest, constructor) {
  S21Matrix matrix;
  EXPECT_EQ(3, matrix.GetRows());
  EXPECT_EQ(3, matrix.GetCols());
}

TEST_F(S21MatrixTest, constructorWithParameters) {
  S21Matrix matrix(5, 6);
  EXPECT_EQ(5, matrix.GetRows());
  EXPECT_EQ(6, matrix.GetCols());
}

TEST_F(S21MatrixTest, constructorCopy) {
  S21Matrix matrix(*matrix_4x3);
  EXPECT_EQ(4, matrix.GetRows());
  EXPECT_EQ(3, matrix.GetCols());
  EXPECT_EQ(4, matrix_4x3->GetRows());
  EXPECT_EQ(3, matrix_4x3->GetCols());
  EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, constructorMove) {
  S21Matrix matrix_copy(*matrix_4x3);
  S21Matrix matrix(std::move(*matrix_4x3));
  EXPECT_EQ(4, matrix.GetRows());
  EXPECT_EQ(3, matrix.GetCols());
  EXPECT_EQ(1, matrix_copy == matrix);
  EXPECT_EQ(0, matrix_4x3->GetRows());
  EXPECT_EQ(0, matrix_4x3->GetCols());
}

TEST_F(S21MatrixTest, GetColsAndRows) {
  EXPECT_EQ(3, matrix_3x3->GetRows());
  EXPECT_EQ(3, matrix_3x3->GetCols());
  EXPECT_EQ(4, matrix_4x3->GetRows());
  EXPECT_EQ(3, matrix_4x3->GetCols());
}

TEST_F(S21MatrixTest, qualityOperator) {
  S21Matrix matrix, empty_matrix;
  EXPECT_EQ(0, *matrix_3x3 == *matrix_4x3);
  EXPECT_EQ(0, *matrix_3x3 == matrix);
  EXPECT_EQ(1, matrix == empty_matrix);
}

TEST_F(S21MatrixTest, equalsOperator) {
  S21Matrix matrix;
  matrix = *matrix_3x3;
  EXPECT_EQ(1, *matrix_3x3 == matrix);
  matrix = *matrix_4x3;
  EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, plusAndEqualsOperator) {
  S21Matrix result;
  result(0, 0) = 0;
  result(0, 1) = 2;
  result(0, 2) = 4;
  result(1, 0) = 6;
  result(1, 1) = 8;
  result(1, 2) = 10;
  result(2, 0) = 12;
  result(2, 1) = 14;
  result(2, 2) = 16;
  S21Matrix test_result;
  test_result = *matrix_3x3 + *matrix_3x3;
  *matrix_3x3 += *matrix_3x3;
  EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST(Method, Sub) {
  S21Matrix m1(4, 5), m2(4, 5), m3(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      m2(i, j) = i * j + 1;
      m3(i, j) = i * j + 2;
    }
  }
  m1.SubMatrix(m2);
  EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, Sum) {
  S21Matrix m1(4, 5), m2(4, 5), m3(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      m1(i, j) = i * j;
      m2(i, j) = i * j + 1;
      m3(i, j) = i * j + 2;
    }
  }
  m1.SumMatrix(m2);
  EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, MulMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      m1(i, j) = 2;
      m2(i, j) = 3;
      m3(i, j) = 12;
    }
  }
  m1.MulMatrix(m2);

  S21Matrix m2_2(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      m2_2(i, j) = i * j;
    }
  }
}

TEST_F(S21MatrixTest, Set) {
  matrix_4x3->SetRows(3);
  matrix_4x3->SetCols(3);
  EXPECT_EQ(true, matrix_3x3->EqMatrix(*matrix_4x3));
}

TEST_F(S21MatrixTest, mulNumberAndEqualsOperator) {
  S21Matrix result;
  result(0, 0) = 0;
  result(0, 1) = 5;
  result(0, 2) = 10;
  result(1, 0) = 15;
  result(1, 1) = 20;
  result(1, 2) = 25;
  result(2, 0) = 30;
  result(2, 1) = 35;
  result(2, 2) = 40;
  S21Matrix test_result;
  test_result = *matrix_3x3 * 5;
  *matrix_3x3 *= 5;
  EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, bracketsOperator) {
  EXPECT_EQ(0, matrix_3x3->operator()(0, 0));
  EXPECT_EQ(1, matrix_3x3->operator()(0, 1));
  EXPECT_EQ(2, matrix_3x3->operator()(0, 2));
  EXPECT_EQ(3, matrix_3x3->operator()(1, 0));
  EXPECT_EQ(4, matrix_3x3->operator()(1, 1));
  EXPECT_EQ(5, matrix_3x3->operator()(1, 2));
  EXPECT_EQ(6, matrix_3x3->operator()(2, 0));
  EXPECT_EQ(7, matrix_3x3->operator()(2, 1));
  EXPECT_EQ(8, matrix_3x3->operator()(2, 2));
}

TEST_F(S21MatrixTest, transpose) {
  S21Matrix result(3, 4);
  result(0, 0) = 0;
  result(0, 1) = 3;
  result(0, 2) = 6;
  result(0, 3) = 9;
  result(1, 0) = 1;
  result(1, 1) = 4;
  result(1, 2) = 7;
  result(1, 3) = 10;
  result(2, 0) = 2;
  result(2, 1) = 5;
  result(2, 2) = 8;
  result(2, 3) = 11;
  S21Matrix test_result;
  test_result = matrix_4x3->Transpose();
  EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, complements) {
  matrix_3x3->operator()(0, 0) = -5;
  S21Matrix result;
  result(0, 0) = -3;
  result(0, 1) = 6;
  result(0, 2) = -3;
  result(1, 0) = 6;
  result(1, 1) = -52;
  result(1, 2) = 41;
  result(2, 0) = -3;
  result(2, 1) = 31;
  result(2, 2) = -23;
  S21Matrix test_result;
  test_result = matrix_3x3->CalcComplements();
  EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, determinant) {
  EXPECT_EQ(0, matrix_3x3->Determinant());
  matrix_3x3->operator()(0, 0) = -5;
  EXPECT_EQ(15, matrix_3x3->Determinant());
  S21Matrix matrix_1x1(1, 1);
  matrix_1x1(0, 0) = 5;
  EXPECT_EQ(5, matrix_1x1.Determinant());
}

TEST_F(S21MatrixTest, eqmul) {
  S21Matrix result(3, 3);
  S21Matrix tmp(3, 3);
  result = *matrix_3x3;
  tmp = result * *matrix_3x3;
  *matrix_3x3 *= *matrix_3x3;
  EXPECT_EQ(0, result == *matrix_3x3);
}

TEST_F(S21MatrixTest, inverse) {
  matrix_3x3->operator()(0, 0) = 2;
  matrix_3x3->operator()(0, 1) = 5;
  matrix_3x3->operator()(0, 2) = 7;
  matrix_3x3->operator()(1, 0) = 6;
  matrix_3x3->operator()(1, 1) = 3;
  matrix_3x3->operator()(1, 2) = 4;
  matrix_3x3->operator()(2, 0) = 5;
  matrix_3x3->operator()(2, 1) = -2;
  matrix_3x3->operator()(2, 2) = -3;
  S21Matrix result;
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  S21Matrix test_result;
  test_result = matrix_3x3->InverseMatrix();
  EXPECT_EQ(1, result == test_result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
