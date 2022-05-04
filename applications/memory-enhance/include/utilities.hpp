/***************************
 * utilities.hpp
 * 
 * Created on: Jan-23-2017
 * Author: Jake Sacks
 ***************************/

#include "datatypes.hpp"

using namespace std;

#ifndef UTILITIES_H_
#define UTILITIES_H_

void printVector(vector<M_DOUBLE> v);
void printMatrix(vector<vector<M_DOUBLE>> m);

void mmMul(bool mat1_transpose,
           bool mat2_transpose,
           M_DOUBLE val,
           vector<vector<M_DOUBLE>> &mat1, 
           vector<vector<M_DOUBLE>> &mat2, 
           vector<vector<M_DOUBLE>> &res);
void mvMul(bool mat_transpose,
           M_DOUBLE val,
           vector<vector<M_DOUBLE>> &mat, 
           vector<M_DOUBLE> &vect, 
           vector<M_DOUBLE> &res);
M_DOUBLE dotProd(vector<M_DOUBLE> vect1, vector<M_DOUBLE> vect2);
void horConcat(vector<vector<M_DOUBLE>> &mat1, 
               vector<vector<M_DOUBLE>> &mat2);
void vertConcat(vector<vector<M_DOUBLE>> &mat1, 
                vector<vector<M_DOUBLE>> &mat2);
vector<vector<M_DOUBLE>> zeroMatrix(M_INT dim1, M_INT dim2);
#endif // UTILITIES_H_