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
        if (Matrix1.isLowerTriangularMatrix())
        {
            LMatrix<double> lM(Matrix1.GetRows(), Matrix1.GetColumns());
            lM = Matrix1;

            cout << "A * A^T:" << endl;
            Matrix1 = lM * lM.Transpose();
            cout << Matrix1 * Matrix1.Transpose() << endl;
            cout << endl;

            cout << "x:" << endl;
            GaussElimination<double> gauss;
            MyVector<double> x = gauss.ForwardSub(lM, myVector);
            for (int i = 0; i < lines; i++)
            {
                cout << x[i] << endl;
            }
            cout << endl;

            cout << "A * x:" << endl;
            Matrix<double> Matrix2(lines, 1);
            Matrix2.PushBack(x);
            cout << Matrix1 * Matrix2 << endl;
        }
        else if (Matrix1.isUpperTriangularMatrix())
        {
            UMatrix<double> uM(Matrix1.GetRows(), Matrix1.GetColumns());
            uM = Matrix1;
            cout << "A * A^T:" << endl;
            Matrix1 = uM * uM.Transpose();
            cout << Matrix1 * Matrix1.Transpose() << endl;
            cout << endl;

            cout << "x:" << endl;
            GaussElimination<double> gauss;
            MyVector<double> x = gauss.BackSub(uM, myVector);
            for (int i = 0; i < lines; i++)
            {
                cout << x[i] << endl;
            }
            cout << endl;

            cout << "A * x:" << endl;
            Matrix<double> Matrix2(lines, 1);
            Matrix2.PushBack(x);
            cout << Matrix1 * Matrix2 << endl;
        }
        else
        {
            cout << "A * A^T:" << endl;
            cout << Matrix1 * Matrix1.Transpose() << endl;
            cout << endl;

            cout << "x:" << endl;
            GaussElimination<double> gauss;
            MyVector<double> x = gauss.GaussEliminate(Matrix1, myVector);
            for (int i = 0; i < lines; i++)
            {
                cout << x[i] << endl;
            }
            cout << endl;

            cout << "A * x:" << endl;
            Matrix<double> Matrix2(lines, 1);
            Matrix2.PushBack(x);
            cout << Matrix1 * Matrix2 << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}