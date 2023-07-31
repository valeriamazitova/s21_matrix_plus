# s21_matrix_plus
Implementation of the s21_matrix_oop.h library.

Following functions were implemented using object-oriented approach:
`bool EqMatrix(const S21Matrix& other)` - Checks matrices for equality with each other

`void SumMatrix(const S21Matrix& other)` - Adds the second matrix to the current one

`void SubMatrix(const S21Matrix& other)` - Subtracts another matrix from the current one

`void MulNumber(const double num)` - Multiplies the current matrix by a number

`void MulMatrix(const S21Matrix& other)` - Multiplies the current matrix by the second matrix

`S21Matrix Transpose()` - Creates a new transposed matrix from the current one and returns it

`S21Matrix CalcComplements()` - Calculates the algebraic addition matrix of the current one and returns it

`double Determinant()` - Calculates and returns the determinant of the current matrix

`S21Matrix InverseMatrix()` - Calculates and returns the inverse matrix

operator overload:
- '+'
- '-'
- '*'
- == 
- =
- +=
- -=
- *=
- Indexation by matrix elements (row, column)
