#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class S21Matrix {
 public:
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  //    --- getter & setter ---
  int GetRows();
  void SetRows(int row);
  int GetCols();
  void SetCols(int col);
  //      void printMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double x);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(double x);
  double &operator()(int row, int column);
  double operator()(int row, int column) const;

  double *operator[](int row) const;

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

 private:
  int rows_ = 3, cols_ = 3;
  double **matrix_ = nullptr;
  //    --- additional functions ---
  void Minor(int i, int j, S21Matrix &res);
  void MemoryAllocation();
  void DeleteMatrix();
  void CopyMatrix(const S21Matrix &other);
  //    void fillWithRand();
};

#endif  // S21_MATRIX_OOP_H_
