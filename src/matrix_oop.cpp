#include "matrix_oop.h"

void _Matrix::aloc() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

_Matrix::_Matrix() : rows_(3), cols_(3) {  //
  aloc();
}

_Matrix::_Matrix(int _rows, int _cols) : rows_(_rows), cols_(_cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range(
        "Incorrect input, rows and cols must be greater than 0");
  }
  aloc();
}

_Matrix::_Matrix(const _Matrix& o) : rows_(o.rows_), cols_(o.cols_) {
  aloc();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

_Matrix& _Matrix::operator=(const _Matrix& o) {
  if (matrix_ != o.matrix_) {
    dealoc();
    rows_ = o.rows_;
    cols_ = o.cols_;
    aloc();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  }
  return *this;
}

void _Matrix::set_col(int new_col) {
  if (new_col < 1) {
    throw std::out_of_range("Incorrect input, cols must be greater than 0");
  }
  if (new_col != cols_) {
    _Matrix tmp_(std::move(*this));
    cols_ = new_col;
    aloc();
    for (int i = 0; i < tmp_.rows_ && i < rows_; i++) {
      for (int j = 0; j < tmp_.cols_ && j < cols_; j++) {
        matrix_[i][j] = tmp_.matrix_[i][j];
      }
    }
  }
}

void _Matrix::set_row(int new_row) {
  if (new_row < 1) {
    throw std::out_of_range("Incorrect input, rows must be greater than 0");
  }
  if (new_row != rows_) {
    _Matrix tmp_(std::move(*this));
    rows_ = new_row;
    aloc();
    for (int i = 0; i < tmp_.rows_ && i < rows_; i++) {
      for (int j = 0; j < tmp_.cols_ && j < cols_; j++) {
        matrix_[i][j] = tmp_.matrix_[i][j];
      }
    }
  }
}

void _Matrix::move_matrix(_Matrix&& o) {
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
  std::swap(cols_, o.cols_);
  std::swap(rows_, o.rows_);
  std::swap(matrix_, o.matrix_);
}

_Matrix::_Matrix(_Matrix&& o) {  //
  move_matrix(std::move(o));
}

void _Matrix::dealoc() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

_Matrix::~_Matrix() {  //
  dealoc();
}

double& _Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, id is out of range");
  return matrix_[row][col];
}

double _Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, id is out of range");
  return matrix_[row][col];
}

void _Matrix::sum_matrix(const _Matrix& o) {
  if (!is_same_size(o))
    throw std::out_of_range("Incorrect input, matrices have different sizes");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += o.matrix_[i][j];
    }
  }
}

_Matrix _Matrix::operator+(const _Matrix& o) {
  _Matrix sum(o);
  sum.sum_matrix(*this);
  return sum;
}

_Matrix& _Matrix::operator+=(const _Matrix& o) {
  this->sum_matrix(o);
  return *this;
}

void _Matrix::sub_matrix(const _Matrix& o) {
  if (!is_same_size(o)) {
    throw std::out_of_range("Incorrect input, matrices have different sizes");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= o.matrix_[i][j];
    }
  }
}

_Matrix _Matrix::operator-(const _Matrix& o) {
  _Matrix sub_(*this);
  sub_.sub_matrix(o);
  return sub_;
}

_Matrix& _Matrix::operator-=(const _Matrix& o) {
  sub_matrix(o);
  return *this;
}

bool _Matrix::eq_matrix(const _Matrix& o) {
  bool result_ = is_same_size(o);
  if (result_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result_ &= (fabs(matrix_[i][j] - o.matrix_[i][j]) < 1e-8);
      }
    }
  }
  return result_;
}

void _Matrix::mul_number(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

_Matrix _Matrix::operator*(const double num) {
  _Matrix mul_n_(*this);
  mul_n_.mul_number(num);
  return mul_n_;
}

_Matrix& _Matrix::operator*=(const double num) {
  this->mul_number(num);
  return *this;
}

bool _Matrix::is_same_size(const _Matrix& o) {
  return (cols_ == o.cols_ && rows_ == o.rows_);
}

void _Matrix::mul_matrix(const _Matrix& o) {
  if (rows_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices have different sizes");
  }
  _Matrix mul_ = _Matrix(rows_, o.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < o.cols_; j++) {
      for (int k = 0; k < o.rows_; k++) {
        mul_.matrix_[i][j] += matrix_[i][k] * o.matrix_[k][j];
      }
    }
  }
  *this = mul_;
}

_Matrix _Matrix::operator*(const _Matrix& o) {
  _Matrix mul_m_(*this);
  mul_m_.mul_matrix(o);
  return mul_m_;
}

_Matrix& _Matrix::operator*=(const _Matrix& o) {
  this->mul_matrix(o);
  return *this;
}

bool _Matrix::operator==(const _Matrix& o) {  //
  return eq_matrix(o);
}

_Matrix _Matrix::transpose() {
  _Matrix transp_ = _Matrix(cols_, rows_);
  for (int i = 0; i < transp_.get_row(); i++) {
    for (int j = 0; j < transp_.get_col(); j++) {
      transp_.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transp_;
}

_Matrix _Matrix::calc_complements() {
  if (rows_ != cols_)
    throw std::out_of_range("Incorrect input, matrix must be square");
  _Matrix comp_ = _Matrix(rows_, cols_);
  int size_ = rows_;
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      int degree_ = ((i + j) % 2 == 0) ? 1 : -1;
      _Matrix tmp_(get_rs_matrix(i, j));
      comp_.matrix_[i][j] = tmp_.determinant() * degree_;
    }
  }

  return comp_;
}

double _Matrix::determinant() {
  if (rows_ != cols_)
    throw std::out_of_range("Incorrect input, matrix must be square");
  double det_ = 0;
  int degree_ = 1;
  if (rows_ == 1) {
    det_ = matrix_[0][0];
  } else if (rows_ == 2) {
    det_ = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < rows_; j++) {
      _Matrix RS_(this->get_rs_matrix(0, j));
      det_ += (degree_ * matrix_[0][j] * RS_.determinant());
      degree_ *= -1;
    }
  }
  return det_;
}

_Matrix _Matrix::inverse_matrix() {
  double det_ = determinant();
  if (!det_) throw std::invalid_argument("Determinant must be not 0");
  _Matrix comp_(this->calc_complements());
  _Matrix trans_comp_(comp_.transpose());
  trans_comp_.mul_number(1 / det_);
  return trans_comp_;
}

_Matrix _Matrix::get_rs_matrix(int row, int col) {
  int size_ = rows_ - 1;
  _Matrix RS_(size_, size_);
  int offsetRow_ = 0;
  for (int i = 0; i < size_; i++) {
    int offsetCol = 0;
    if (i == row) offsetRow_ = 1;
    for (int j = 0; j < size_; j++) {
      if (j == col) offsetCol = 1;
      RS_.matrix_[i][j] = matrix_[i + offsetRow_][j + offsetCol];
    }
  }
  return RS_;
}

void _Matrix::set(double value, int row_id, int col_id) {
  if (!matrix_ || row_id > rows_ || col_id > cols_) {
    throw std::out_of_range("Incorrect input, id is out of range");
  }
  matrix_[row_id][col_id] = value;
}

double _Matrix::get(int row_id, int col_id) {
  if (row_id > rows_ || col_id > cols_ || row_id < 0 || col_id < 0)
    throw std::out_of_range("Incorrect input, id is out of range");
  return matrix_[row_id][col_id];
}

int _Matrix::get_col() {  //
  return cols_;
}

int _Matrix::get_row() {  //
  return rows_;
}
