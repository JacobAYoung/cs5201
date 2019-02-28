#include <iostream>
#include <fstream>
#include "MyVector.h"
#include "LinearIndependent.h"
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    vector<MyVector<double>> vect;

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

        if (lines <= 0)
        {
            throw std::runtime_error("Check how many objects you would like to create at the top of your file.");
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

            istringstream ss(line);
            ss >> myVector;
            vect.push_back(myVector);
        }
        file.close();

        cout << vect[0] + vect[1] << endl;
        cout << vect[0] - vect[1] << endl;
        cout << vect[0] * vect[1] << endl;
        cout << vect[1][0] << endl;

        vector<vector<double>> matrix;
        for (int i = 0; i < lines; i++)
        {
            vector<double> subVector;
            matrix.push_back(subVector);
            for (int j = 0; j < lines; j++)
            {
                matrix[i].push_back(vect[j][i]);
            }
        }
        cout.precision(4);
        cout.setf(ios::fixed);
        LinearIndependent<double> linear(lines - 1);
        bool test = linear.CheckLinearIndependent(matrix, lines - 1);
        cout << test << endl;
        if (test)
        {
            vector<double> data = linear.GetData();
            for (unsigned int i = 0; i < data.size(); i++)
            {
                cout << data[i] << endl;
            }
        }
        cout << linear.GetEpsilon() << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}