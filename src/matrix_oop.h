#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>
#include <iostream>

class _Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated
  void move_matrix(_Matrix&& o);        // move matrix to other
  bool is_same_size(const _Matrix& o);  // checking matrices for same size
  void aloc();    // aloc memory for matrix using current row and col
  void dealoc();  // delete matrx
  _Matrix get_rs_matrix(int row, int col);  // return minor matrix

 public:
  _Matrix();                    // default constructor
  _Matrix(int rows, int cols);  // parameterized constructor
  _Matrix(const _Matrix& o);  // copy cnstructor
  _Matrix(_Matrix&& o);       // move cnstructor
  ~_Matrix();                   // destructor

  void set(double value, int row_id,
           int col_id);       // set value to cell by row and col
  void set_col(int new_col);  // set number of cols in matrix
  void set_row(int new_row);  // set number of rows in matrix

  double get(int row_id, int col_id);  // get value of cell by row and col
  int get_col();                       // get number of cols in matrix
  int get_row();                       // get number of cols in matrix

  // some operators overloads
  _Matrix& operator=(const _Matrix& o);   // assignment operator overload
  bool operator==(const _Matrix& o);        // equality operator overload
  double& operator()(int row, int col);       // index operator overload
  double operator()(int row, int col) const;  // index operator overload
  _Matrix& operator+=(const _Matrix& o);  // adding operator overload
  _Matrix operator+(const _Matrix& o);    // sum operator overload
  _Matrix operator*(const double num);      // mult number operator overload
  _Matrix operator*(const _Matrix& o);    // mult matrix operator overload
  _Matrix& operator*=(const double num);    // mult number operator overload
  _Matrix& operator*=(const _Matrix& o);  // mult matrix operator overload
  _Matrix& operator-=(const _Matrix& o);  // subtraction operator overload
  _Matrix operator-(const _Matrix& o);    // sub operator overload

  // some public methods
  bool eq_matrix(const _Matrix& o);   // equality method
  void sum_matrix(const _Matrix& o);  // sum method
  void sub_matrix(const _Matrix& o);  // sub method
  void mul_number(const double num);    // mult number method
  void mul_matrix(const _Matrix& o);  // mult matrix method
  _Matrix transpose();                // transpose method
  _Matrix calc_complements();         // return complements matrix
  double determinant();                 // return determinant
  _Matrix inverse_matrix();           // return inverse matrix
};

#endif
