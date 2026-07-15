#include <cstring>
#include "example.h"

S21Matrix::S21Matrix() {
    _rows = 3;
    _cols = 3;
    // that is how memory allocation works in C++
    _p = new double*[_rows]();
    for (int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols]();
    }
}

/* : <attribute_name>(value) syntax helps to automatically fill attributes with 
values */
S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    _p = new double*[_rows]();
    for (int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols]();
    }
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
    _p = new double*[_rows]();
    for (int i = 0; i < _rows; i++) {
        _p[i] = new double[_cols]();
        /* standard cpp function: copies memory of o._cols * sizeof(double)
           from o.p[i] pointer to _p[i] pointer */
        std::memcpy(_p[i], o._p[i], _cols * sizeof(double));
    }
}

S21Matrix::S21Matrix(S21Matrix&& o) {
    if (this != &o) {
        _p = o._p;
        _rows = o._rows;
        _cols = o._cols;
        o._p = nullptr;
        o._rows = 0;
        o._cols = 0;
    }
}

S21Matrix::~S21Matrix() {
    if (_p) {
        // free
        for (int i = 0; i < _rows; i++) {
            delete[] _p[i];
        }
        delete[] _p;
    }
}

void S21Matrix::sum_matrix(const S21Matrix& o) {
    // exception throwing example
    if (_rows != o._rows || _cols != o._cols) {
        throw std::out_of_range(
            "Incorrect input, matrices should have the same size");
    }
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            _p[i][j] += o._p[i][j];
        }
    }
}

// operator overload example
S21Matrix S21Matrix::operator+(const S21Matrix& o) {
    // exception throwing example
    if (_rows != o._rows || _cols != o._cols) {
        throw std::out_of_range(
            "Incorrect input, matrices should have the same size");
    }
    // creating result matrix
    S21Matrix res(_rows, _cols);
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            res._p[i][j] = _p[i][j] + o._p[i][j];
        }
    }
    return res;
}

// index operator overload
double& S21Matrix::operator()(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return _p[row][col];
}
