///Author: Jake Young
///Date: 2-29-2019
///PRE: None
/// POST: This main function will declare a MyVector class object and
/// LMatrix object that we weill use to run calculations with Ax =b and other
/// LMatrix computations.

#include <iostream>
#include <fstream>
#include "MyVector.h"
#include <vector>
#include <sstream>
#include "Matrix.h"
#include "LMatrix.h"
#include "UMatrix.h"
#include "DMatrix.h"
#include "TMatrix.h"
#include "SMatrix.h"
#include "GaussElimination.h"

using namespace std;

int main(int argc, char *argv[])
{
    string line = "";

    int lines = 0;
    ifstream file;

    try
    {
        if (argc != 2)
        {
            throw std::runtime_error("Parameter error");
        }

        file.open(argv[1]);

        if (!file.good())
        {
            throw std::runtime_error("Error opening file!");
        }

        getline(file, line);
        istringstream inputStream(line);
        inputStream >> lines;
        //Define matricies
        Matrix<double> Matrix1(lines, lines);
        if (lines <= 0)
        {
            throw std::runtime_error("Check how many objects you would like "
                                     "to create at the top of your file.");
        }
        MyVector<double> myVector(lines);
        for (int i = 0; i < lines; i++)
        {
            if (file.eof())
            {
                throw std::runtime_error("Too many objects trying to be declared from file");
            }
            getline(file, line);

            for (unsigned int i = 0; i < line.size(); i++)
            {
                if (isalpha(line[i]))
                {
                    throw std::runtime_error("Contains a character");
                }
            }

            if (line != "")
            {
                istringstream ss(line);
                ss >> Matrix1;
            }
            else
            {
                i--;
            }
        }
        //Get blank line
        getline(file, line);
        //Copy the vector
        getline(file, line);
        istringstream ss(line);
        ss >> myVector;
        //Close the file
        file.close();

        //Output
        cout.precision(8);
        cout.setf(ios::fixed);
        if (Matrix1.isDiagonalMatrix())
        {
            DMatrix<double> dM(Matrix1.GetRows(), Matrix1.GetColumns());
            dM = Matrix1;
            LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            LMatrix<double> lM2(Matrix1.GetRows(), Matrix1.GetColumns());
            // lM(1, 0) = 2;
            // lM(2, 0) = 2;
            //lM(2, 1) = 2;
            lM(0, 0) = 1;
            lM(1, 1) = 1;
            lM(2, 2) = 1;
            lM2(0, 0) = 1;
            lM2(1, 1) = 1;
            lM2(2, 2) = 1;

            UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            UMatrix<double> uM2(Matrix1.GetRows(), Matrix1.GetColumns());
            // uM(0, 1) = 2;
            // uM(0, 2) = 2;
            uM(1, 2) = 2;
            uM(0, 0) = 1;
            uM(1, 1) = 1;
            uM(2, 2) = 1;
            uM2(0, 0) = 1;
            uM2(1, 1) = 1;
            uM2(2, 2) = 1;
            // for (int i = 0; i < Matrix1.GetRows(); i++)
            // {
            //     for (int j = 0; j < Matrix1.GetColumns(); j++)
            //     {
            //         Matrix1[i][j] = 2;
            //     }
            // }
            Matrix1[0][0] = 1;
            Matrix1[1][1] = 1;
            Matrix1[2][2] = 1;
            //Matrix1[0][1] = 1;
            //Matrix1[1][2] = 1;
            SMatrix<double> sM(Matrix1.GetRows(), Matrix1.GetColumns());
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    sM[i][j] = 2;
                }
            }
            cout << "-------------Diagonal Matrix-------------" << endl;
            cout << dM << endl;

            cout << "-------------Lower Matrix-------------" << endl;
            cout << lM << endl;

            if (uM == Matrix1)
            {
                cout << "Equal" << endl;
            }
            if (Matrix1 == uM)
            {
                cout << "Equal" << endl;
            }

            // cout << "-------------Diagonal Matrix-------------" << endl;
            // cout << dM << endl;

            // cout << "-------------Symmetric Matrix-------------" << endl;
            // cout << sM << endl;
            // cout << endl;
            // cout << "-------------Diagonal/Symmetric-------------" << endl;
            // cout << dM - sM << endl;
            // cout << endl;
            // cout << "-------------Symmetric/Diagonal-------------" << endl;
            // cout << sM - dM << endl;
            // cout << endl;

            // cout << "-------------Dense Matrix-------------" << endl;
            // cout << Matrix1 << endl;
            // cout << endl;
            // cout << "-------------Diagonal/Dense-------------" << endl;
            // cout << dM - Matrix1 << endl;
            // cout << endl;
            // cout << "-------------Dense/Diagonal-------------" << endl;
            // cout << Matrix1 - dM << endl;
            // cout << endl;

            // cout << "-------------Lower Matrix-------------" << endl;
            // cout << lM << endl;
            // cout << "-------------diagonal/lower-------------" << endl;
            // cout << dM - lM << endl;
            // cout << "-------------Lower/diagonal-------------" << endl;
            // cout << lM - dM << endl;

            // cout << "-------------Upper Matrix-------------" << endl;
            // cout << uM << endl;
            // cout << "-------------Diagonal/Upper-------------" << endl;
            // cout << dM - uM << endl;
            // cout << "-------------Upper/Diagonal-------------" << endl;
            // cout << uM - dM << endl;
        }
        else if (Matrix1.isSymmetricMatrix())
        {
            SMatrix<double> sM(Matrix1.GetRows(), Matrix1.GetColumns());
            sM = Matrix1;
            DMatrix<double> dM(Matrix1.GetRows(), Matrix1.GetColumns());
            dM(0, 0) = 1;
            dM(1, 1) = 2;
            dM(2, 2) = 3;
            LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            lM(1, 0) = 2;
            lM(2, 0) = 2;
            lM(2, 1) = 2;
            lM(0, 0) = 2;
            lM(1, 1) = 2;
            lM(2, 2) = 2;
            UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            uM(0, 1) = 2;
            uM(0, 2) = 2;
            uM(1, 2) = 2;
            uM(0, 0) = 2;
            uM(1, 1) = 2;
            uM(2, 2) = 2;
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    Matrix1[i][j] = 2;
                }
            }

            cout << "-------------Symmetric Matrix-------------" << endl;
            cout << sM << endl;

            cout << "-------------Symmetric/Symmetric-------------" << endl;
            cout << sM * sM << endl;

            cout << "-------------Diagonal Matrix-------------" << endl;
            cout << dM << endl;
            cout << endl;
            cout << "-------------Symmetric/Diagonal-------------" << endl;
            cout << sM * dM << endl;
            cout << endl;
            cout << "-------------Diagonal/Symmetric-------------" << endl;
            cout << dM * sM << endl;
            cout << endl;

            cout << "-------------Dense Matrix-------------" << endl;
            cout << Matrix1 << endl;
            cout << endl;
            cout << "-------------Symmetric/Dense-------------" << endl;
            cout << sM * Matrix1 << endl;
            cout << endl;
            cout << "-------------Dense/Symmetric-------------" << endl;
            cout << Matrix1 * sM << endl;
            cout << endl;

            cout << "-------------Lower Matrix-------------" << endl;
            cout << lM << endl;
            cout << "-------------Symmetric/lower-------------" << endl;
            cout << sM * lM << endl;
            cout << "-------------Lower/Symmetric-------------" << endl;
            cout << lM * sM << endl;

            cout << "-------------Upper Matrix-------------" << endl;
            cout << uM << endl;
            cout << "-------------Symmetric/Upper-------------" << endl;
            cout << sM * uM << endl;
            cout << "-------------Upper/Symmetric-------------" << endl;
            cout << uM * sM << endl;
        }
        else if (Matrix1.isLowerTriangularMatrix())
        {
            SMatrix<double> sM(Matrix1.GetRows(), Matrix1.GetColumns());
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    sM[i][j] = 2;
                }
            }
            DMatrix<double> dM(Matrix1.GetRows(), Matrix1.GetColumns());
            dM(0, 0) = 1;
            dM(1, 1) = 2;
            dM(2, 2) = 3;
            LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            lM = Matrix1;
            UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            uM(0, 1) = 2;
            uM(0, 2) = 2;
            uM(1, 2) = 2;
            uM(0, 0) = 2;
            uM(1, 1) = 2;
            uM(2, 2) = 2;
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    Matrix1[i][j] = 2;
                }
            }

            cout << "-------------Lower Matrix-------------" << endl;
            cout << -lM << endl;
            cout << "-------------Lower/Lower-------------" << endl;
            cout << lM - lM << endl;

            cout << "-------------Diagonal Matrix-------------" << endl;
            cout << dM << endl;
            cout << "-------------Lower/Diagonal-------------" << endl;
            cout << lM - dM << endl;
            cout << "-------------Diagonal/Lower-------------" << endl;
            cout << dM - lM << endl;

            cout << "-------------Dense Matrix-------------" << endl;
            cout << Matrix1 << endl;
            cout << endl;
            cout << "-------------Lower/Dense-------------" << endl;
            cout << lM - Matrix1 << endl;
            cout << endl;
            cout << "-------------Dense/Lower-------------" << endl;
            cout << Matrix1 - lM << endl;
            cout << endl;

            cout << "-------------Symmetric Matrix-------------" << endl;
            cout << sM << endl;
            cout << endl;
            cout << "-------------Symmetric/lower-------------" << endl;
            cout << sM - lM << endl;
            cout << endl;
            cout << "-------------Lower/Symmetric-------------" << endl;
            cout << lM - sM << endl;
            cout << endl;

            cout << "-------------Upper Matrix-------------" << endl;
            cout << uM << endl;
            cout << "-------------Lower/Upper-------------" << endl;
            cout << lM - uM << endl;
            cout << endl;
            cout << "-------------Upper/Lower-------------" << endl;
            cout << uM - lM << endl;

            // LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            // lM = Matrix1;

            // cout << "A * A^T:" << endl;
            // Matrix1 = lM * lM.Transpose();
            // cout << Matrix1 * Matrix1.Transpose() << endl;
            // cout << endl;

            // cout << "x:" << endl;
            // GaussElimination<double> gauss;
            // MyVector<double> x = gauss.ForwardSub(lM, myVector);
            // for (int i = 0; i < lines; i++)
            // {
            //     cout << x[i] << endl;
            // }
            // cout << endl;

            // cout << "A * x:" << endl;
            // Matrix<double> Matrix2(lines, 1);
            // Matrix2.PushBack(x);
            // cout << Matrix1 * Matrix2 << endl;
        }
        else if (Matrix1.isUpperTriangularMatrix())
        {
            SMatrix<double> sM(Matrix1.GetRows(), Matrix1.GetColumns());
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    sM[i][j] = 2;
                }
            }
            DMatrix<double> dM(Matrix1.GetRows(), Matrix1.GetColumns());
            dM(0, 0) = 1;
            dM(1, 1) = 2;
            dM(2, 2) = 3;
            LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            lM(1, 0) = 2;
            lM(2, 0) = 2;
            lM(2, 1) = 2;
            lM(0, 0) = 2;
            lM(1, 1) = 2;
            lM(2, 2) = 2;
            UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            uM = Matrix1;
            for (int i = 0; i < Matrix1.GetRows(); i++)
            {
                for (int j = 0; j < Matrix1.GetColumns(); j++)
                {
                    Matrix1[i][j] = 2;
                }
            }

            cout << "-------------upper Matrix-------------" << endl;
            cout << uM << endl;
            cout << "-------------upper/upper-------------" << endl;
            cout << uM - uM << endl;

            cout << "-------------Diagonal Matrix-------------" << endl;
            cout << dM << endl;
            cout << "-------------upper/Diagonal-------------" << endl;
            cout << uM - dM << endl;
            cout << "-------------Diagonal/upper-------------" << endl;
            cout << dM - uM << endl;

            cout << "-------------Dense Matrix-------------" << endl;
            cout << Matrix1 << endl;
            cout << endl;
            cout << "-------------upper/Dense-------------" << endl;
            cout << uM - Matrix1 << endl;
            cout << endl;
            cout << "-------------Dense/upper-------------" << endl;
            cout << Matrix1 - uM << endl;
            cout << endl;

            cout << "-------------Symmetric Matrix-------------" << endl;
            cout << sM << endl;
            cout << endl;
            cout << "-------------Symmetric/upper-------------" << endl;
            cout << sM - uM << endl;
            cout << endl;
            cout << "-------------upper/Symmetric-------------" << endl;
            cout << uM - sM << endl;
            cout << endl;

            cout << "-------------Lower Matrix-------------" << endl;
            cout << lM << endl;
            cout << "-------------lower/Upper-------------" << endl;
            cout << lM - uM << endl;
            cout << endl;
            cout << "-------------Upper/lower-------------" << endl;
            cout << uM - lM << endl;
            // UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            // uM = Matrix1;
            // cout << "A * A^T:" << endl;
            // Matrix1 = uM * uM.Transpose();
            // cout << Matrix1 * Matrix1.Transpose() << endl;
            // cout << endl;

            // cout << "x:" << endl;
            // GaussElimination<double> gauss;
            // MyVector<double> x = gauss.BackSub(uM, myVector);
            // for (int i = 0; i < lines; i++)
            // {
            //     cout << x[i] << endl;
            // }
            // cout << endl;

            // cout << "A * x:" << endl;
            // Matrix<double> Matrix2(lines, 1);
            // Matrix2.PushBack(x);
            // cout << Matrix1 * Matrix2 << endl;
        }
        else
        {
            TMatrix<double> tM(Matrix1.GetRows(), Matrix1.GetColumns());
            tM = Matrix1;
            cout << tM << endl;
            //cout << "A * A^T:" << endl;
            // cout << Matrix1 * Matrix1.Transpose() << endl;
            // cout << endl;

            // cout << "x:" << endl;
            // GaussElimination<double> gauss;
            // MyVector<double> x = gauss.GaussEliminate(Matrix1, myVector);
            // for (int i = 0; i < lines; i++)
            // {
            //     cout << x[i] << endl;
            // }
            // cout << endl;

            // cout << "A * x:" << endl;
            // Matrix<double> Matrix2(lines, 1);
            // Matrix2.PushBack(x);
            // cout << Matrix1 * Matrix2 << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}