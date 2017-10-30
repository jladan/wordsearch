/* Matrix class
 */

#include "matrix.h"

template <typename T>
Matrix<T>::Matrix (size_t rows, size_t columns, const T value) {
    c = columns;
    r = rows;
    data = std::vector<T>(r*c, value);
}

template <typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
    return data[i + j*r];
}

template <typename T>
T Matrix<T>::operator()(size_t i, size_t j) const {
    return data[i + j*r];
}

template <typename T>
vector<T> Matrix<T>::row(size_t i) {
    vector<T> tmp(c);
    for (size_t k=0; k<c; k++)
        tmp[k] = data[i + k*r];

    return tmp;
}

template <typename T>
vector<T> Matrix<T>::col(size_t i) {
    vector<T> tmp(r);
    for (size_t k=0; k<r; k++)
        tmp[k] = data[k + i*r];

    return tmp;
}
