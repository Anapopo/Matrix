#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
private:
    int rows;
    int columns;
    int **element;

    void init(int rows, int columns);
    void init(int rows, int columns, int x);

public:
    Matrix(int rows = 0); //rows阶方阵
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, int x);
    Matrix(int rows, int columns, int values[]);
    ~Matrix();

    friend ostream& operator<<(ostream& out, Matrix&);
    int get(int i, int j);
    void set(int i, int j, int x);
    int getRows();//返回矩阵行数
    int getColumns();//返回列数
    void setRowsColumns(int rows, int columns);//设置行数列数，自动扩容
    //5-1
    Matrix(Matrix &mat);
    Matrix& operator=(Matrix &mat);
    bool operator==(Matrix &mat);
    void operator+=(Matrix &mat);//当前矩阵加上一个矩阵
    Matrix operator+(Matrix &mat);//返回相加后的矩阵，保留*this
    void operator*=(Matrix &mat);//当前矩阵乘上一个矩阵
    Matrix operator*(Matrix &mat);
    Matrix transpose();
    bool isTriangular(bool up);
    bool isSymmetric();//判断是否是对称矩阵
    int saddlePoint();//返回矩阵的鞍点值
    static int** helixPhalanx(int n);
};

