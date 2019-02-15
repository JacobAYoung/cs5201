#include <iostream>
#include "Cylindrical.h"
#include "Norm.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    Cylindrical<double> cylindrical;
    vector<Cylindrical<double>> vect;
    Norm<double, Cylindrical<double>> norm;
    string line = "";
    int lines = 0;
    ifstream file;

    try
    {
        file.open("data.txt");
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