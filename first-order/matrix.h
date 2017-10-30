
#ifndef MATRIX_H
#define MATRIX_H 

#include <vector>

using namespace std;

template <typename T>
class Matrix {
public:
    Matrix (size_t columns, size_t rows, const T value);
    
    T& operator()(size_t i, size_t j);
    T operator()(size_t i, size_t j) const;
    vector<T> row(size_t i);
    vector<T> col(size_t i);

private:
    int r,c;
    std::vector<T> data;
};

#endif
