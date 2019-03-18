///Author: Jake Young
///Date: 2-29-2019
///PRE: None
/// POST: This main function will declare a MyVector class object and
/// Matrix object that we weill use to run calculations with Ax =b and other
/// matrix computations.

#include <iostream>
#include <fstream>
#include "MyVector.h"
#include <vector>
#include <sstream>
#include "Matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
    string line = "";

    int lines = 0;
    ifstream file;

    try
    {
        if (argc > 2 || argc < 2)
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
        Matrix<double> matrix1(lines, lines);
        Matrix<double> matrix2(lines, 1);
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
                ss >> myVector;
                matrix1.PushBack(myVector);
            }
            else
            {
                i--;
            }
        }
        //Copy a blank line for file format
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
        cout << "A * A^T:" << endl;
        cout << matrix1 * matrix1.Transpose() << endl;
        cout << endl;
        cout << "x:" << endl;
        MyVector<double> x = matrix1.Eliminate(myVector);
        for (int i = 0; i < lines; i++)
        {
            cout << x[i] << endl;
        }
        cout << endl;
        matrix2.PushBack(x);
        cout << "A * x:" << endl;
        cout << matrix1 * matrix2 << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}