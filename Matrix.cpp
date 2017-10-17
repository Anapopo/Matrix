#include "Matrix.h"

void Matrix::init(int rows, int columns)
{
    if (rows > 0 && columns > 0)
    {
        this->rows = rows;
        this->columns = columns;
        this->element = new int*[rows];
        for (int i = 0; i < rows; i++)
            this->element[i] = new int[columns];
    }
    else throw invalid_argument("rows or columns must be larger than 0!");
}

void Matrix::init(int rows, int columns, int x)
{
    this->init(rows, columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->element[i][j] = x;
}
//构造函数
Matrix::Matrix(int rows) { this->init(rows, rows); }

Matrix::Matrix(int rows, int columns) { this->init(rows, columns); }

Matrix::Matrix(int rows, int columns, int x) { this->init(rows, columns, x); }

Matrix::Matrix(int rows, int columns, int values[])
{
    this->init(rows, columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->element[i][j] = values[i * columns + j];
}
//析构函数
Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
        delete(this->element[i]);
    delete(this->element);
}
//重载<<符号
ostream& operator<<(ostream& out, Matrix &mat)
{
    out << "Matrix (" << mat.rows << "X" << mat.columns << ")" << endl;
    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.columns; j++)
            out << setw(4) << mat.element[i][j];
        out << endl;
    }
    return out;
}
//设置元素
void Matrix::set(int i, int j, int x)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        this->element[i][j] = x;
    else throw out_of_range("i and j must be range from 0 to rows/columns");
}
//获取元素
int Matrix::get(int i, int j)
{   
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        return this->element[i][j];
    throw out_of_range("can not find the specify i and j!");
}
//指定矩阵行数和列数
void Matrix::setRowsColumns(int rows, int columns)
{
    if (rows > this->rows || columns > this->columns)
    {
        int rows_old = this->rows;
        int columns_old = this->columns;
        int **temp = this->element;
        this->init(rows, columns);
        for (int i = 0; i < rows_old; i++)
            for (int j = 0; j < columns_old; j++)
                this->element[i][j] = temp[i][j];

        for (int i = 0; i < rows_old; i++)
            delete(temp[i]);
        delete(temp);
        
    }
}
//返回矩阵行数
int Matrix::getRows() { return this->rows; }
//返回矩阵列数
int Matrix::getColumns() { return this->columns; }
//复制构造函数
Matrix::Matrix(Matrix &mat)
{
    this->init(mat.getRows(), mat.getColumns());
    for (int i = 0; i < mat.getRows(); i++)
        for (int j = 0; j < mat.getColumns(); j++)
            this->element[i][j] = mat.get(i, j);
}
//赋值操作符号
Matrix& Matrix::operator=(Matrix &mat)
{
    if (this != &mat)
    {
        this->~Matrix();
        this->init(mat.getRows(), mat.getColumns());
        for (int i = 0; i < mat.getRows(); i++)
            for (int j = 0; j < mat.getColumns(); j++)
                this->element[i][j] = mat.get(i, j);
	}
    return (*this);
}

//比较两个矩阵是否相等
bool Matrix::operator==(Matrix &mat)
{   
    if (this->rows != mat.getRows() || this->columns != mat.getColumns())
        return false;
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            if (this->element[i][j] != mat.get(i, j))
                return false;
    return true;
}
//当前矩阵加上一个矩阵
void Matrix::operator+=(Matrix &mat)
{
    if (this->rows == mat.getRows() && this->columns == mat.getColumns())
    {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->columns; j++)
                this->element[i][j] += mat.get(i,j);
    }
    else throw invalid_argument("The specify matrix's rows/columns must be the same as this");
}
//返回相加后的矩阵，保留*this
Matrix Matrix::operator+(Matrix &mat)
{
    if (this->rows == mat.getRows() && this->columns == mat.getColumns())
    {
        Matrix temp(*this);
        temp += mat;
        return temp;
    }
    else throw invalid_argument("The specify matrix's rows/columns must be the same as this");
}
//当前矩阵乘上一个矩阵
void Matrix::operator*=(Matrix &mat)
{
    if (this->columns == mat.getRows())
    {   
        Matrix temp(this->rows, mat.getColumns());
        
        for (int i = 0; i < this->rows; i++)
        {
            for (int k = 0; k < mat.getColumns(); k++)
            {
                int sum = 0;
                for (int j = 0; j < mat.getRows(); j++)
                    sum += this->element[i][j] * mat.get(j, k);
                //cout << sum << endl;
                temp.set(i, k, sum);
            }
        }

        this->setRowsColumns(temp.getRows(), temp.getColumns());
        for (int x = 0; x < this->rows; x++)
            for (int y = 0; y < this->columns; y++)
                this->element[x][y] = temp.get(x, y);
        //cout << temp;

    }
    else throw invalid_argument("The specify matrix error");
}
//返回两矩阵相乘后的矩阵，保持*this不变
Matrix Matrix::operator*(Matrix &mat)
{
    if (this->columns == mat.getRows())
    {
        Matrix temp(this->rows, mat.getColumns());

        for (int i = 0; i < this->rows; i++)
        {
            for (int k = 0; k < mat.getColumns(); k++)
            {
                int sum = 0;
                for (int j = 0; j < mat.getRows(); j++)
                    sum += this->element[i][j] * mat.get(j, k);
                temp.set(i, k, sum);
            }
        }
        return temp;
    }
    else throw invalid_argument("The specify matrix error");
}
//矩阵的转置
Matrix Matrix::transpose()
{
    Matrix temp(this->columns, this->rows);

    for (int i = 0; i < temp.getRows(); i++)
        for (int j = 0; j < temp.getColumns(); j++)
            temp.set(i, j, this->element[j][i]);
    return temp;
}
//判断上下三角
bool Matrix::isTriangular(bool up)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = (up ? i : 0); j < (up ? this->columns : i + 1); j++)
            if (!this->element[i][j])
                return false;
    return true;
}
//判断是否是对称矩阵
bool Matrix::isSymmetric()
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
        {
            if (i == j) continue;
            if (this->element[i][j] != this->element[j][i])
                return false;
        }
    return true;
}
//返回矩阵的鞍点值
int Matrix::saddlePoint()
{   
    int flag;
    for (int i = 0; i < this->rows; i++)
    {   
        int rows_min = this->element[i][0];
        int rows_min_j = 0;
        for (int j = 1; j < this->columns; j++)
        {
            if (this->element[i][j] < this->element[i][rows_min_j])
            {
                rows_min_j = j;
                rows_min = this->element[i][j];
            }    
        }
        //此时rows_min是第i行中最小的元素，rows_min_j是它的列标
        flag = 1;
        for (int k = 0; k < this->rows; k++)//遍历第(rows_min_j)列
        {
            if (this->element[k][rows_min_j] > rows_min)//判断rows_min是不是当前列的最大值
            {
                flag = 0;
                break;
            }
        }
        if (flag)/*如果条件成立，则表明成功找到鞍点*/
        {   
            cout << "saddlePoint(i,j)=" << rows_min << ",i=" << i << ",j=" << rows_min_j << "." << endl;
            return rows_min;
        }
    }
    return -1;    
}

int** Matrix::helixPhalanx(int n)
{
    int ** out = new int*[n];
    for (int i = 0; i < n; i++) out[i] = new int[n];
    int posX=0,posY=0,direction=0,writeNumber=1;

    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            out[i][j]=0;
    
    while(true) {
        out[posX][posY] = writeNumber;//写数据
        writeNumber++;
        if (writeNumber == n*n+1) break;
        
        switch(direction) {
            case 0://right
                if (posY<=n-2 && out[posX][posY+1] == 0) posY++;
                else {
                    posX++;
                    direction = 1;
                }
                break;
            case 1://Down
                if (posX<=n-2 && out[posX+1][posY] == 0) posX++;
                else {
                    posY--;
                    direction = 2;
                }
                break;
            case 2://Left
                if (posY>=1 && out[posX][posY-1] == 0) posY--;
                else {
                    posX--;
                    direction = 3;
                }
                break;
            case 3://Up
                if (posX>=1 && out[posX-1][posY] == 0) posX--;
                else {
                    posY++;
                    direction = 0;
                }
                break;
        }
        //printf("Next Position is (%d:%d:%d)\n", posX, posY, direction);
    }
    
    printf("Helix Matrix:%d*%d\n", n, n);
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            cout << setw(3) << out[i][j];
        printf("\n");
    }
    return out;
}
