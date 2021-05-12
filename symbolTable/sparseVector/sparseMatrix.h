#ifndef SPARSEMATRIX_H_INCLUDED
#define SPARSEMATRIX_H_INCLUDED

#include "sparseVector.h"
#include <iostream>
#include <stdexcept>

class sparseMatrix
{
public:
    sparseMatrix(int r, int c):
        rowSize(r), rows(new sparseVector[rowSize]), columnSize(c),columns(new sparseVector[columnSize])
    {
        for (int i = 0; i < rowSize;  ++i)
            rows[i].setDimension(columnSize);
        for (int i = 0; i < columnSize; ++i)
            columns[i].setDimension(rowSize);
    }
    ~sparseMatrix()
    {
        delete[] rows;
        delete[] columns;
    }

    double &get(int row, int column)
    {
        if (row < 0 || row >= rowSize || column < 0 || column >= columnSize)
            throw std::invalid_argument("invalid row or column index.\n");
        return rows[row].get(column);
    }
    void insert(int row, int column, double value)
    {
        if (row < 0 || row >= rowSize || column < 0 || column >= columnSize)
            throw std::invalid_argument("invalid row or column index.\n");
        rows[row].insert(column, value);
        columns[column].insert(row, value);
    }
    void remove(int row, int column)
    {
        if (row < 0 || row >= rowSize || column < 0 || column >= columnSize)
            throw std::invalid_argument("invalid row or column index.\n");
        rows[row].remove(column);
        columns[column].remove(row);
    }

    // sum
    sparseMatrix operator+(sparseMatrix &rhs)
    {
        sparseMatrix ret(rowSize, columnSize);
        for (int i = 0; i < rowSize; ++i)
            ret.rows[i] = rows[i] +  rhs.rows[i];
        for (int i = 0; i < columnSize; ++i)
            ret.columns[i] = columns[i] + rhs.columns[i];
        return ret;
    }

    // matrix- matrix multiplication
    sparseMatrix operator*(sparseMatrix &rhs)
    {
        if (columnSize != rhs.rowSize)
            throw std::invalid_argument("first matrix column number must match second matrix row number.\n");
        sparseMatrix ret(rowSize, columnSize);
        for (int i = 0; i < rowSize; ++i)
        {
            for (int j = 0; j < columnSize; ++j)
            {
                double sum = 0.0;
                sum  = rows[i] * columns[j];
                if (sum != 0.0)
                    ret.insert(i, j, sum);
            }
        }
        return ret;
    }
    // matrix-vector multiplication
    sparseVector operator*(sparseVector &rhs)
    {
        if (columnSize != rhs.getDimension())
            throw std::invalid_argument("the matrix column must match the vector dimension.\n");
        sparseVector ret(rowSize);
        for (int i = 0; i < rowSize; ++i)
        {
            double sum = 0.0;
            sum = rows[i] * rhs;
            if (sum != 0)
                ret.insert(i, sum);
        }
        return ret;
    }
    void print()
    {
        for (int i = 0; i < rowSize; ++i)
        {
            rows[i].print();
            std::cout << std::endl;
        }
    }
private:
    int rowSize;
    sparseVector *rows;
    int columnSize;
    sparseVector *columns;
};


#endif // SPARSEMATRIX_H_INCLUDED
