///Author: Jake Young
///Date: 2-15-2019
///PRE: None
///POST: This is the main function that will call all code and will be used to define any other class

#include <iostream>
#include "Cylindrical.h"
#include "Norm.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    Cylindrical<double> cylindrical;
    vector<Cylindrical<double>> vect;
    Norm<double, Cylindrical<double>> norm;
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
            throw std::runtime_error("Not accurate amount of cylindrical objects");
        }

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
            ss >> cylindrical;
            vect.push_back(cylindrical);
        }
        file.close();

        cout << std::fixed;
        cout << std::setprecision(7) << -vect[0];
        cout << !vect[1];
        cout << (vect[2] == vect[3]) << endl;
        cout << vect[4].PrintPoints() << endl;
        cout << norm(vect) << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}