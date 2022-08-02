#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(create, wrong_size) {
  EXPECT_THROW(_Matrix a = _Matrix(-5, 5), std::out_of_range);
}

TEST(sum, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a.sum_matrix(b), std::out_of_range);
}

TEST(sum_op, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a + b, std::out_of_range);
}

TEST(sum_op_pe, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a += b, std::out_of_range);
}

TEST(sub_op, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a - b, std::out_of_range);
}

TEST(sub_op_pe, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a -= b, std::out_of_range);
}

TEST(sum, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  a.sum_matrix(b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), i + j + i * j, 0.000000001);
    }
  }
}

TEST(sum_op, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  _Matrix sum(a + b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(sum.get(i, j), i + j + i * j, 0.000000001);
    }
  }
}

TEST(sum_op_pe, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  a += b;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), i + j + i * j, 0.000000001);
    }
  }
}

TEST(sub, wrong_size) {
  _Matrix a = _Matrix(5, 5);
  _Matrix b = _Matrix(7, 7);
  EXPECT_THROW(a.sub_matrix(b), std::out_of_range);
}

TEST(sub, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + 0.1 * j, i, j);
      b.set(10 + i + 0.1 * j, i, j);
    }
  }
  a.sub_matrix(b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), ((i + 0.1 * j) - (10 + i + 0.1 * j)),
                  0.000000001);
    }
  }
}

TEST(sub_op, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  _Matrix sub(a - b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(sub.get(i, j), (i + j) - (i * j), 0.000000001);
    }
  }
}

TEST(sub_op_pe, correct) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  a -= b;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), (i + j) - (i * j), 0.000000001);
    }
  }
}

TEST(op_id, ok) {
  _Matrix a = _Matrix(10, 15);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
    }
  }
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a(i, j), i + j, 0.000000001);
    }
  }
}

TEST(op_eq_eq, t_true) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i + j, i, j);
    }
  }
  bool res = (a == b);
  EXPECT_TRUE(res);
}

TEST(op_eq_eq, t_false) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i - j, i, j);
    }
  }
  bool res = (a == b);
  EXPECT_FALSE(res);
}

TEST(op_eq_eq, dif_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 4);

  bool res = (a == b);
  EXPECT_FALSE(res);
}

TEST(assign, ok) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i * j, i, j);
    }
  }
  a = b;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(b.get(i, j), a.get(i, j), 0.000000001);
    }
  }
}

TEST(assign, same) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
    }
  }
  a = a;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), i + j, 0.000000001);
    }
  }
}

TEST(op_index, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
    }
  }
  a(0, 0) = 22;
  EXPECT_NEAR(a(0, 0), 22, 0.000000001);
}

TEST(op_index_const, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
    }
  }
  const _Matrix b = a;
  double num = b(1, 1);
  EXPECT_NEAR(num, 2, 0.000000001);
}

TEST(op_index_const, wrong_size) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
    }
  }
  const _Matrix b = a;
  EXPECT_THROW(double num = b(10, 15), std::out_of_range);
}

TEST(eq, correct_eq) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i + j, i, j);
    }
  }
  EXPECT_TRUE(a.eq_matrix(b));
}

TEST(eq, correct_not_eq) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + j, i, j);
      b.set(i - j, i, j);
    }
  }
  EXPECT_FALSE(a.eq_matrix(b));
}

TEST(eq, wrong_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(4, 4);
  EXPECT_FALSE(a.eq_matrix(b));
}

TEST(mul_matrix, correct_sq_same_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
      b.set(5, i, j);
    }
  }
  a.mul_matrix(b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), 30, 0.000000001);
    }
  }
}

TEST(op_eq_mul_matrix, correct_sq_same_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
      b.set(5, i, j);
    }
  }
  a *= b;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), 30, 0.000000001);
    }
  }
}

TEST(mul_matrix, correct_same_size) {
  _Matrix a = _Matrix(3, 5);
  _Matrix b = _Matrix(5, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(5, i, j);
    }
  }
  for (int i = 0; i < b.get_row(); i++) {
    for (int j = 0; j < b.get_col(); j++) {
      b.set(2, i, j);
    }
  }
  a.mul_matrix(b);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), 50, 0.000000001);
    }
  }
}

TEST(op_mul_matrix, correct_same_size) {
  _Matrix a = _Matrix(3, 5);
  _Matrix b = _Matrix(5, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(5, i, j);
    }
  }
  for (int i = 0; i < b.get_row(); i++) {
    for (int j = 0; j < b.get_col(); j++) {
      b.set(2, i, j);
    }
  }
  _Matrix c = a * b;
  for (int i = 0; i < c.get_row(); i++) {
    for (int j = 0; j < c.get_col(); j++) {
      EXPECT_NEAR(c.get(i, j), 50, 0.000000001);
    }
  }
}

TEST(op_mul_matrix, diff_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 5);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
      b.set(5, i, j);
    }
  }
  _Matrix c;
  EXPECT_THROW(c = a * b, std::invalid_argument);
}

TEST(mul_matrix, diff_size) {
  _Matrix a = _Matrix(3, 3);
  _Matrix b = _Matrix(3, 5);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
      b.set(5, i, j);
    }
  }
  EXPECT_THROW(a.mul_matrix(b), std::invalid_argument);
}

TEST(mul_number, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
    }
  }
  a.mul_number(5);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), 10, 0.000000001);
    }
  }
}

TEST(op_mul_number, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
    }
  }
  _Matrix b = a * 5;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(b.get(i, j), 10, 0.000000001);
      EXPECT_NEAR(a.get(i, j), 2, 0.000000001);
    }
  }
}

TEST(op_mul_eq_number, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(2, i, j);
    }
  }
  a *= 5;
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), 10, 0.000000001);
    }
  }
}

TEST(set, incorrect_range) {
  _Matrix a = _Matrix(2, 2);
  EXPECT_THROW(a.set(10, 10, 10), std::out_of_range);
}

TEST(get, incorrect_range) {
  _Matrix a = _Matrix(2, 2);
  EXPECT_THROW(a.get(10, 10), std::out_of_range);
}

TEST(op_brace, incorrect_range) {
  _Matrix a = _Matrix(2, 2);
  EXPECT_THROW(a(10, 10), std::out_of_range);
}

TEST(set_col, new_col_greater) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  int old_col = a.get_col();
  a.set_col(4);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      if (j < old_col) {
        EXPECT_NEAR(a.get(i, j), i + 0.1 * j, 0.000000001);
      } else {
        EXPECT_NEAR(a.get(i, j), 0, 0.000000001);
      }
    }
  }
}

TEST(set_col, new_col_less) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  a.set_col(2);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), i + 0.1 * j, 0.000000001);
    }
  }
}

TEST(set_col, bad_size) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + j, i, j);
    }
  }
  EXPECT_THROW(a.set_col(0), std::out_of_range);
}

TEST(set_row, new_row_greater) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  int old_row = a.get_row();
  a.set_row(4);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      if (i < old_row) {
        EXPECT_NEAR(a.get(i, j), i + 0.1 * j, 0.000000001);
      } else {
        EXPECT_NEAR(a.get(i, j), 0, 0.000000001);
      }
    }
  }
}

TEST(set_row, new_row_less) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  a.set_row(2);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      EXPECT_NEAR(a.get(i, j), i + 0.1 * j, 0.000000001);
    }
  }
}

TEST(set_row, bad_size) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  EXPECT_THROW(a.set_row(0), std::out_of_range);
}

TEST(copy, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  _Matrix b = _Matrix(a);
  for (int i = 0; i < b.get_col(); i++) {
    for (int j = 0; j < b.get_row(); j++) {
      EXPECT_TRUE(a.get(i, j) == b.get(i, j));
    }
  }
}

TEST(move, ok) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  _Matrix b(std::move(a));
  for (int i = 0; i < b.get_col(); i++) {
    for (int j = 0; j < b.get_row(); j++) {
      EXPECT_NEAR(b.get(i, j), i + 0.1 * j, 0.0000001);
    }
  }
}

TEST(transpose, t3x3) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_col(); i++) {
    for (int j = 0; j < a.get_row(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  _Matrix b = _Matrix(a.transpose());
  for (int i = 0; i < b.get_col(); i++) {
    for (int j = 0; j < b.get_row(); j++) {
      EXPECT_NEAR(b.get(j, i), i + 0.1 * j, 0.0000001);
    }
  }
}

TEST(transpose, t2x5) {
  _Matrix a = _Matrix(2, 5);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  _Matrix b(a.transpose());
  for (int i = 0; i < b.get_row(); i++) {
    for (int j = 0; j < b.get_col(); j++) {
      EXPECT_NEAR(b.get(i, j), j + 0.1 * i, 0.0000001);
    }
  }
}

TEST(determinant, t2x2) {
  _Matrix a = _Matrix(2, 2);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  EXPECT_NEAR(a.determinant(), -0.1, 0.0000001);
}

TEST(determinant, t1x1) {
  _Matrix a = _Matrix(1, 1);
  a.set(5, 0, 0);
  EXPECT_NEAR(a.determinant(), 5, 0.0000001);
}

TEST(determinant, t3x3) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      a.set(i + 0.1 * j, i, j);
    }
  }
  EXPECT_NEAR(a.determinant(), 0, 0.0000001);
}

TEST(determinant, t4x4) {
  _Matrix a = _Matrix(4, 4);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      if (i != j) {
        a.set(i + 10 * j, i, j);
      } else {
        a.set(10, i, j);
      }
    }
  }
  EXPECT_NEAR(a.determinant(), 39060, 0.0000001);
}

TEST(determinant, bad_size) {
  _Matrix a = _Matrix(4, 3);
  EXPECT_THROW(a.determinant(), std::out_of_range);
}

TEST(comlements, bad_size) {
  _Matrix a = _Matrix(4, 3);
  EXPECT_THROW(a.calc_complements(), std::out_of_range);
}

TEST(inverse, bad_size) {
  _Matrix a = _Matrix(4, 3);
  EXPECT_THROW(a.inverse_matrix(), std::out_of_range);
}

TEST(inverse, t3x3) {
  _Matrix a = _Matrix(3, 3);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      if (i != j) {
        a.set(i + 10 * j, i, j);
      } else {
        a.set(10, i, j);
      }
    }
  }
  _Matrix res(a.inverse_matrix());
  EXPECT_NEAR(res.get(0, 0), 0.11176470588235293, 0.0000001);
  EXPECT_NEAR(res.get(0, 1), -0.102941176470588, 0.0000001);
}

TEST(inverse, t4x4) {
  _Matrix a = _Matrix(4, 4);
  for (int i = 0; i < a.get_row(); i++) {
    for (int j = 0; j < a.get_col(); j++) {
      if (i != j) {
        a.set(i + 10 * j, i, j);
      } else {
        a.set(10, i, j);
      }
    }
  }
  _Matrix res(a.inverse_matrix());
  EXPECT_NEAR(res.get(0, 0), 0.11218637992831541, 0.0000001);
  EXPECT_NEAR(res.get(0, 1), -0.10087045570916539, 0.0000001);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
