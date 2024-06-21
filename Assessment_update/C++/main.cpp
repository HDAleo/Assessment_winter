class Matrix {  
public:  
    Matrix(int r, int c) : rows(r), cols(c) {  
        matrix = new int*[rows];  
        for (int i = 0; i < rows; ++i) {  
            matrix[i] = new int[cols];  
            for (int j = 0; j < cols; ++j) {  
                matrix[i][j] = 0;  
            }  
        }  
    }  
  
    ~Matrix() {  
        for (int i = 0; i < rows; ++i) {  
            delete[] matrix[i];  
        }  
        delete[] matrix;  
    }  
  
    Matrix operator*(const Matrix& other) const {  
        if (cols != other.rows) {  
            throw std::invalid_argument("Matrix dimensions must match for multiplication.");  
        }  
  
        Matrix result(rows, other.cols);  
        for (int i = 0; i < rows; ++i) {  
            for (int j = 0; j < other.cols; ++j) {  
                for (int k = 0; k < cols; ++k) {  
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];  
                }  
            }  
        }  
        return result;  
    }  
   
    friend std::istream& operator>>(std::istream& in, Matrix& mat) {  
        for (int i = 0; i < mat.rows; ++i) {  
            for (int j = 0; j < mat.cols; ++j) {  
                in >> mat.matrix[i][j];  
            }  
        }  
        return in;  
    }  
  
    friend std::ostream& operator<<(std::ostream& out, const Matrix& mat) {  
        for (int i = 0; i < mat.rows; ++i) {  
            for (int j = 0; j < mat.cols; ++j) {  
                out << mat.matrix[i][j] << " ";  
            }  
            out << std::endl;  
        }  
        return out;  
    }  
  
private:  
    int rows;  
    int cols;  
    int** matrix;  
};  

#include <iostream>  
#include "matrix.h"

int main() {
    int rows, cols;

    std::cin >> rows >> cols;
    Matrix A(rows, cols);
    std::cin >> A;

    std::cin >> rows >> cols;
    Matrix B(rows, cols);
    std::cin >> B;

    std::cout << A * B;

    return 0;
}