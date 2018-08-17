#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#define pi 3.14159265
#include <iomanip>
#include <math.h>

using namespace std;
float pointsABC[10][3] = { 0.0 };
float pointsABCTransMatrix[3][10] = { 0.0 };
float product[3] = { 0.0 };

float pointsY[10] = { 0.0 };

int main()
{

    ifstream infile("dataRC.txt");
    string line;
    int i = 0;

    string timeDataStr = "";
    string velocityData = "";
    string accData = "";
    string rotaData = "";
    string delimiter = ";";
    int posDeli = 0;
    double timeData = 0.0;
    double timeDataPrev = 0.0;
    double deltadistanceTemp = 0.0;
    double angleRadTemp = 0.0;
    double angleDegTemp = 0.0;
    double distance = 0;
    double xCoord = 0;
    double yCoord = 0;
    double xCoordTemp = 0;
    double yCoordTemp = 0;
    ofstream myfile;
    myfile.open("output_coord.txt");

    int index = 0;

    while (getline(infile, line)) {

        string s = line;

        timeDataStr = s.substr(0, s.find(delimiter));
        posDeli = s.find(delimiter);
        s = s.substr(posDeli + 1, s.length() - 1);

        velocityData = s.substr(0, s.find(delimiter));
        posDeli = s.find(delimiter);
        s = s.substr(posDeli + 1, s.length() - 1);

        accData = s.substr(0, s.find(delimiter));
        posDeli = s.find(delimiter);
        s = s.substr(posDeli + 1, s.length() - 1);

        rotaData = s.substr(0, s.find(delimiter));

        timeData = stod(timeDataStr) - timeDataPrev;
        angleRadTemp = stod(rotaData) * timeData;
        angleDegTemp = angleRadTemp * 180 / pi;
        distance = stod(velocityData) * timeData;

        xCoord = distance * cos(angleDegTemp);

        yCoord = distance * sin(angleDegTemp);

        cout << "#" << i << " Time Diff(sec):" << timeData << " Velocity(m/s):" << velocityData << " Acceleration (m/s^2):"
             << accData << " Omega(rad/s):" << rotaData
             << " Degree: " << scientific << setprecision(20) << angleDegTemp
             << " Distance: " << scientific << setprecision(20) << distance
             << " X: " << scientific << setprecision(20) << xCoord
             << " Y: " << scientific << setprecision(20) << yCoord << endl;

        xCoordTemp = xCoordTemp + xCoord;

        yCoordTemp = yCoordTemp + yCoord;

        myfile << xCoordTemp << ";" << yCoordTemp << ";" << endl;

        i++;

        timeDataPrev = timeData;
    }

    myfile.close();

    return 0;
}
