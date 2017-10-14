#include "Matrix.h"
int main()
{
	/*
    int table[4*4] = {1,2,3,4,5,6,7,8,9};
    Matrix mat(4, 4, table), mat2(mat), mat3 = mat;
    
    int e[4 * 4] = { 1,2,3,4,2,5,6,7,3,6,8,9,4,7,9,10};
    Matrix ete(4, 4, e);

    cout << "Ete is " << ete;
    cout << "Ete is Symmetric ? Echo:" << ete.isSymmetric() << endl << endl;//正确

    cout << "Mat is " << mat;
    cout << "(Mat == Ete) ? Echo:" << (mat == ete) << endl << endl;//正确

    mat += mat3;
    cout << "Mat + Mat3 is " << mat << endl;

    Matrix mat4 = mat2 + mat3;
    cout << "Mat2 + Mat3 is " << mat4 << endl;

    Matrix mat5 = mat * mat4;
    cout << "Mat * Mat4 is " << mat5 << endl;

    mat *= mat4;
    cout << "Mat * Mat4 is " << mat << endl;
    

    cout << "Tansposed Matrix is " << mat.transpose() << endl;

    int z[4 * 4] = {1,2,3,4,0,5,6,7,0,0,8,9,0,0,0,10};
    Matrix mat6(4, 4, z);
    cout << "Mat6 is Triangular ? Echo:" << mat6.isTriangular(true) << endl << endl;

    mat6.saddlePoint();
	*/
	Matrix::helixPhalanx(4);
    return 0;
}

