// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}
TEST(test_matrix_width) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    
    ASSERT_EQUAL(width, Matrix_width(mat));
    delete mat;
}
TEST(test_matrix_height) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    
    ASSERT_EQUAL(height, Matrix_height(mat));
    delete mat;
}
TEST(matrix_fill_border) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    const int border_value = 21;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, border_value);
    
    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
          if (r == 0 || r == height - 1 || c == 0 || c == width - 1) {
              ASSERT_EQUAL(*Matrix_at(mat, r, c), border_value);
          }
          else {
              ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
          }
      }
    }
    delete mat;
}
TEST(matrix_row) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    const int border_value = 21;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, border_value);
    
    int *ptr = Matrix_at(mat, 2, 1);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    delete mat;
}
TEST(matrix_column) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    const int border_value = 21;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, border_value);
    
    int *ptr = Matrix_at(mat, 2, 1);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 1);
    
    int *ptr2 = Matrix_at(mat, 4, 2);
    ASSERT_EQUAL(Matrix_column(mat, ptr2), 2);
    delete mat;
    
}
TEST(matrix_max) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    const int border_value = 21;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, border_value);
    
    *Matrix_at(mat, 0, 0) = 25;
    *Matrix_at(mat, 0, 1) = 33;
    *Matrix_at(mat, 2, 2) = 45;
    *Matrix_at(mat, 3, 0) = 16;
    *Matrix_at(mat, 4, 1) = 77;
    
    ASSERT_EQUAL(Matrix_max(mat), 77);
    
    delete mat;
    
}
TEST(Matrix_column_of_min_value_in_row) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 5;
    const int height = 5;
    
    Matrix_init(mat, width, height);
    
    *Matrix_at(mat, 0, 0) = 17;
    *Matrix_at(mat, 0, 1) = 14;
    *Matrix_at(mat, 0, 2) = 36;
    *Matrix_at(mat, 0, 3) = 22;
    *Matrix_at(mat, 0, 4) = 5;
    
    *Matrix_at(mat, 1, 0) = 1;
    *Matrix_at(mat, 1, 1) = 13;
    *Matrix_at(mat, 1, 2) = 12;
    *Matrix_at(mat, 1, 3) = 6;
    *Matrix_at(mat, 1, 4) = 5;
    
    *Matrix_at(mat, 2, 0) = 0;
    *Matrix_at(mat, 2, 1) = 1;
    *Matrix_at(mat, 2, 2) = 1;
    *Matrix_at(mat, 2, 3) = 3;
    *Matrix_at(mat, 2, 4) = 22;
    
    *Matrix_at(mat, 3, 0) = 7;
    *Matrix_at(mat, 3, 1) = 6;
    *Matrix_at(mat, 3, 2) = 6;
    *Matrix_at(mat, 3, 3) = 4;
    *Matrix_at(mat, 3, 4) = 19;
    
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 4), 1);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 4), 3);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 3), 1);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 0, 3), 1);
    
    delete mat;
}
TEST(Matrix_min_value_in_row) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 5;
    const int height = 4;
    
    Matrix_init(mat, width, height);
    
    *Matrix_at(mat, 0, 0) = 17;
    *Matrix_at(mat, 0, 1) = 14;
    *Matrix_at(mat, 0, 2) = 36;
    *Matrix_at(mat, 0, 3) = 22;
    *Matrix_at(mat, 0, 4) = 5;
    
    *Matrix_at(mat, 1, 0) = 1;
    *Matrix_at(mat, 1, 1) = 13;
    *Matrix_at(mat, 1, 2) = 12;
    *Matrix_at(mat, 1, 3) = 6;
    *Matrix_at(mat, 1, 4) = 5;
    
    *Matrix_at(mat, 2, 0) = 0;
    *Matrix_at(mat, 2, 1) = 1;
    *Matrix_at(mat, 2, 2) = 1;
    *Matrix_at(mat, 2, 3) = 3;
    *Matrix_at(mat, 2, 4) = 22;
    
    *Matrix_at(mat, 3, 0) = 7;
    *Matrix_at(mat, 3, 1) = 6;
    *Matrix_at(mat, 3, 2) = 6;
    *Matrix_at(mat, 3, 3) = 4;
    *Matrix_at(mat, 3, 4) = 19;
    
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 14);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 1, 4), 6);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 1, 3), 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 3), 6);
    
    delete mat;
}

TEST(test_matrix_print) {
    
    Matrix *mat = new Matrix;
    Matrix_init(mat, 1, 1);

    *Matrix_at(mat, 0, 0) = 42;
    ostringstream expected;
    expected << "1 1\n"
            << "42 \n";
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());
    delete mat;
    
    Matrix *mat2 = new Matrix; // create a Matrix in dynamic memory

    const int width = 5;
    const int height = 4;
    
    Matrix_init(mat2, width, height);
    
    *Matrix_at(mat2, 0, 0) = 17;
    *Matrix_at(mat2, 0, 1) = 14;
    *Matrix_at(mat2, 0, 2) = 36;
    *Matrix_at(mat2, 0, 3) = 22;
    *Matrix_at(mat2, 0, 4) = 5;
    
    *Matrix_at(mat2, 1, 0) = 1;
    *Matrix_at(mat2, 1, 1) = 13;
    *Matrix_at(mat2, 1, 2) = 12;
    *Matrix_at(mat2, 1, 3) = 6;
    *Matrix_at(mat2, 1, 4) = 5;
    
    *Matrix_at(mat2, 2, 0) = 0;
    *Matrix_at(mat2, 2, 1) = 1;
    *Matrix_at(mat2, 2, 2) = 1;
    *Matrix_at(mat2, 2, 3) = 3;
    *Matrix_at(mat2, 2, 4) = 22;
    
    *Matrix_at(mat2, 3, 0) = 7;
    *Matrix_at(mat2, 3, 1) = 6;
    *Matrix_at(mat2, 3, 2) = 6;
    *Matrix_at(mat2, 3, 3) = 4;
    *Matrix_at(mat2, 3, 4) = 19;
    
    ostringstream expected2;
    expected2
    << "5 4\n"
    << "17 14 36 22 5 \n"
    << "1 13 12 6 5 \n"
    << "0 1 1 3 22 \n"
    << "7 6 6 4 19 \n";
    ostringstream actual2;
    Matrix_print(mat, actual2);
    ASSERT_EQUAL(expected2.str(), actual2.str());
      
    
    
    delete mat2;
    
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
