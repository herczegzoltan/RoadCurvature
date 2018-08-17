#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#define pi 3.14159265
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

ifstream infile("output_coord.txt");
string line = "";
string delimiter = ";";
string x_read = "";
string y_read = "";
int posDeli = 0;


double x_val = 0.0;
double y_val = 0.0;

long double TempX[10]={0.0};
long double TempY[10]={0.0};

long double dataPointXY[10][3] = {0.0};
long double dataPointXYtrans[3][10] = {0.0};
long double dataPointXYtransXdataPointXY[3][3] = {0.0};
long double dataPointXYtransXdataPointXY_inverse[3][3] = {0.0};


vector<double> dataX;
vector<double> dataY;

int main()
{
    int index = 0;
    ofstream myfile;
    myfile.open ("results.txt");

    while (getline(infile, line)) {

        string s = line;
        x_read = s.substr(0, s.find(delimiter));
        posDeli = s.find(delimiter);
        s = s.substr(posDeli+1, s.length()-1);
        y_read = s.substr(0, s.find(delimiter));

        x_val = stod(x_read);
        y_val = stod(y_read);

        cout<< x_val  <<" "<<y_val <<endl;
        dataX.push_back(x_val);
        dataY.push_back(y_val);


        index++;
    }

  for (unsigned i=0; i<dataX.size(); i++)
    cout << ' ' << dataX.at(i);


  for (unsigned i = 0; i<dataY.size(); i++)
    cout << ' ' << dataY.at(i);

    int index_data = 0;
    for(int i = 0; i < dataX.size();i++){
            index_data++;

        for(int j = 0; j < 10 ;j++){
            TempX[j] = dataX.at(i+j);
        }

        for(int j = 0; j < 10 ;j++){
            TempY[j] = dataY.at(i+j);
        }

        cout <<"\n"<<endl;
        for(int k = 0; k < 10;k++){
            cout <<TempX[k]<<" " << TempY[k]<<endl;

            dataPointXY[k][0] = TempX[k] * TempX[k];
            dataPointXY[k][1] = TempX[k];
            dataPointXY[k][2] = 1;
        }

        cout <<"\nMatrix reading...[10][3]"<<endl;
        for(int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if(j == 2){
                    cout<< "[" << i << "][" << j << "] = " << dataPointXY[i][j]<<"\n";
                }
                else{
                    cout<< "[" << i << "][" << j << "] = " << dataPointXY[i][j]<<" ";
                }
            }
        }

        cout <<"\nMatrix transpose...[3][10]"<<endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 10; j++){
                dataPointXYtrans[i][j] = dataPointXY[j][i];
                cout << dataPointXYtrans[i][j] << " ";
            }
            cout << "\n ";
        }

        cout <<"\nMatrix transpose * original Matrix..."<<endl;
        double product[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

        for (int row = 0; row < 3; row++) {
           for (int col = 0; col < 3; col++) {
               for (int inner = 0; inner < 10; inner++) {
                   product[row][col] += dataPointXYtrans[row][inner] * dataPointXY[inner][col];
               }
               std::cout << product[row][col] << "  ";
           }
           cout << "\n";
       }

        cout <<"\nMatrix inverse(transpose * original)..."<<endl;
        float determinant = 0;
        for(int i = 0; i < 3; i++)
        determinant = determinant + (product[0][i] * (product[1][(i+1)%3] * product[2][(i+2)%3] - product[1][(i+2)%3] * product[2][(i+1)%3]));

        cout<<"\n\nInverse of matrix is: \n";
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                dataPointXYtransXdataPointXY_inverse[i][j] = ((product[(j+1)%3][(i+1)%3] * product[(j+2)%3][(i+2)%3]) - (product[(j+1)%3][(i+2)%3] * product[(j+2)%3][(i+1)%3]))/ determinant;
                cout <<dataPointXYtransXdataPointXY_inverse[i][j]<<"\t"<<endl;
            }

            cout<<"\n";
        }



        cout<<"\nInverse matrix * transponalt matrix...: \n";
        long double productinverse_trans[3][10] = {0.0};

        for (int row = 0; row < 3; row++) {
           for (int col = 0; col < 10; col++) {
               for (int inner = 0; inner < 3; inner++) {
                   productinverse_trans[row][col] += dataPointXYtransXdataPointXY_inverse[row][inner] * dataPointXYtrans[inner][col];
               }
               std::cout << productinverse_trans[row][col] << "  ";
           }
           cout << "\n";
       }




        cout<<"\nResult...: \n";
        long double parabolaResult[3] = {0.0};

        for (int row = 0; row < 3; row++) {
               for (int inner = 0; inner < 10; inner++) {
                   parabolaResult[row] += productinverse_trans[row][inner] * TempY[inner];
               }
               std::cout << parabolaResult[row] << "  ";

           cout << "\n";
       }

        myfile << parabolaResult[0] << ";" <<parabolaResult[1]<<";"<<parabolaResult[2]<<";"<<endl;

        cout<<"--------------------------------------------"<<endl;

    }
    return 0;

}
