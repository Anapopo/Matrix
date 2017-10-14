#include <stdio.h>
#include <iostream>
using namespace std;
#include <iomanip>
class Matrix
{
private:
    int rows;
    int columns;
    int **element;

    void init(int rows, int columns);
    void init(int rows, int columns, int x);

public:
    Matrix(int rows = 0); //rows�׷���
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, int x);
    Matrix(int rows, int columns, int values[]);
    ~Matrix();

    friend ostream& operator<<(ostream& out, Matrix&);
    int get(int i, int j);
    void set(int i, int j, int x);
    int getRows();//���ؾ�������
    int getColumns();//��������
    void setRowsColumns(int rows, int columns);//���������������Զ�����
    //5-1
    Matrix(Matrix &mat);
    Matrix& operator=(Matrix &mat);
    bool operator==(Matrix &mat);
    void operator+=(Matrix &mat);//��ǰ�������һ������
    Matrix operator+(Matrix &mat);//������Ӻ�ľ��󣬱���*this
    void operator*=(Matrix &mat);//��ǰ�������һ������
    Matrix operator*(Matrix &mat);
    Matrix transpose();
    bool isTriangular(bool up);
    bool isSymmetric();//�ж��Ƿ��ǶԳƾ���
    int saddlePoint();//���ؾ���İ���ֵ
	static int** helixPhalanx(int n);
};

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
//���캯��
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
//��������
Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
        delete(this->element[i]);
    delete(this->element);
}
//����<<����
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
//����Ԫ��
void Matrix::set(int i, int j, int x)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        this->element[i][j] = x;
    else throw out_of_range("i and j must be range from 0 to rows/columns");
}
//��ȡԪ��
int Matrix::get(int i, int j)
{   
    if (i >= 0 && i < rows && j >= 0 && j < columns)
        return this->element[i][j];
    throw out_of_range("can not find the specify i and j!");
}
//ָ����������������
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
//���ؾ�������
int Matrix::getRows() { return this->rows; }
//���ؾ�������
int Matrix::getColumns() { return this->columns; }
//���ƹ��캯��
Matrix::Matrix(Matrix &mat)
{
    this->init(mat.getRows(), mat.getColumns());
    for (int i = 0; i < mat.getRows(); i++)
        for (int j = 0; j < mat.getColumns(); j++)
            this->element[i][j] = mat.get(i, j);
}
//��ֵ��������
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
    return *this;
}
//�Ƚ����������Ƿ����
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
//��ǰ�������һ������
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
//������Ӻ�ľ��󣬱���*this
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
//��ǰ�������һ������
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
//������������˺�ľ��󣬱���*this����
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
//�����ת��
Matrix Matrix::transpose()
{
    Matrix temp(this->columns, this->rows);

    for (int i = 0; i < temp.getRows(); i++)
        for (int j = 0; j < temp.getColumns(); j++)
            temp.set(i, j, this->element[j][i]);
    return temp;
}
//�ж���������
bool Matrix::isTriangular(bool up)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = (up ? i : 0); j < (up ? this->columns : i + 1); j++)
            if (!this->element[i][j])
                return false;
    return true;
}
//�ж��Ƿ��ǶԳƾ���
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
//���ؾ���İ���ֵ
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
        //��ʱrows_min�ǵ�i������С��Ԫ�أ�rows_min_j�������б�
        flag = 1;
        for (int k = 0; k < this->rows; k++)//������(rows_min_j)��
        {
            if (this->element[k][rows_min_j] > rows_min)//�ж�rows_min�ǲ��ǵ�ǰ�е����ֵ
            {
                flag = 0;
                break;
            }
        }
        if (flag)/*�������������������ɹ��ҵ�����*/
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
        out[posX][posY] = writeNumber;//���
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
        printf("Next Position is (%d:%d:%d)\n", posX, posY, direction);
    }
    
    printf("Matrix:%d*%d\n", n, n);
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            cout << setw(3) << out[i][j];
        printf("\n");
    }
    return out;
}
