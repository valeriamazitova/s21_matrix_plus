#include "s21_matrix_oop.h"

void S21Matrix::MemoryAllocation() {
  if (rows_ < 1 || cols_ < 1) {
    throw out_of_range(
        "number of rows or columns "
        "cannot be less than one");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
}

S21Matrix::S21Matrix() { MemoryAllocation(); }

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAllocation();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  if (matrix_ != other.matrix_) {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
    swap(matrix_, other.matrix_);
  }
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("matrices should have the same size to calculate sum");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("matrices should have the same size to subtract them");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw out_of_range("matrices are not compatible size for multiplication");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool isEqual = (rows_ == other.rows_ && cols_ == other.cols_);
  for (auto i = 0; i < rows_ && isEqual; i++) {
    for (auto j = 0; j < cols_ && isEqual; j++) {
      if (fabs(matrix_[i][j] - other(i, j)) > 1e-7) {
        isEqual = false;
      }
    }
  }
  return isEqual;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      res(i, j) = matrix_[j][i];
    }
  }
  return *this = res;
}

void S21Matrix::Minor(int i, int j, S21Matrix &res) {
  int shift_m = 0, shift_n = 0;
  for (int m = 0; m < res.rows_; m++) {
    if (m == i) shift_m = 1;
    shift_n = 0;
    for (int n = 0; n < res.cols_; n++) {
      if (n == j) shift_n = 1;
      res(m, n) = matrix_[m + shift_m][n + shift_n];
    }
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw invalid_argument(
        "unable to calculate complements: "
        "number of rows is not equal to number of columns");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ > 1) {
    double det = 0.0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix this_sup(rows_ - 1, cols_ - 1);
        Minor(i, j, this_sup);
        det = this_sup.Determinant();
        res(i, j) = pow(-1, i + 1 + j + 1) * det;
      }
    }
  } else if (rows_ == 1) {
    res(0, 0) = matrix_[0][0];
  }
  return *this = res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw invalid_argument(
        "unable to calculate determinant: "
        "number of rows is not equal to number of columns");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    int sign = pow(-1, 1 + 1);
    double det = 0.0;
    for (int i = 0; i < rows_; i++) {
      S21Matrix this_new(rows_ - 1, cols_ - 1);
      Minor(i, 0, this_new);
      det = this_new.Determinant();
      result += matrix_[i][0] * sign * det;
      sign = -sign;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw invalid_argument(
        "unable to calculate inverse matrix: "
        "number of rows is not equal to number of columns");
  }
  double det = Determinant();
  if (det == 0)
    throw invalid_argument(
        "unable to calculate inverse matrix: "
        "determinant is equal to zero");
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res(0, 0) = 1 / det;
  } else {
    CalcComplements();
    Transpose();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        res(i, j) = 1 / det * matrix_[i][j];
      }
    }
  }
  return *this = res;
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int row) {
  if (row != rows_) {
    S21Matrix this_copy(*this);
    DeleteMatrix();
    rows_ = row;
    cols_ = this_copy.cols_;
    MemoryAllocation();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i < this_copy.GetRows()) {
          matrix_[i][j] = this_copy(i, j);
        }
      }
    }
  }
}

void S21Matrix::SetCols(int col) {
  if (col != cols_) {
    S21Matrix this_copy(*this);
    DeleteMatrix();
    rows_ = this_copy.rows_;
    cols_ = col;
    MemoryAllocation();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (j < this_copy.GetCols()) {
          matrix_[i][j] = this_copy(i, j);
        }
      }
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(double x) {
  S21Matrix res(*this);
  res.MulNumber(x);
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (*this == other) return *this;
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryAllocation();
  CopyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double x) {
  this->MulNumber(x);
  return *this;
}

double &S21Matrix::operator()(int row, int column) {
  if (row < 0 || row >= rows_ || column < 0 || column >= cols_) {
    throw out_of_range("operator(): row or column number is out of range");
  }
  return matrix_[row][column];
}

double S21Matrix::operator()(int row, int column) const {
  if (row < 0 || row >= rows_ || column < 0 || column >= cols_) {
    throw out_of_range(
        "operator(): row or column number "
        "is out of range");
  }
  return matrix_[row][column];
}

double *S21Matrix::operator[](int row) const {
  if (row >= rows_ || row < 0) throw std::out_of_range("Invalid array size!");
  return matrix_[row];
}

// void S21Matrix::printMatrix() {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       cout << matrix_[i][j] << " ";
//     }
//     cout << "\n";
//   }
// }

// void S21Matrix::fillWithRand() {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       matrix_[i][j] = rand() % 10;
//     }
//   }
// }
