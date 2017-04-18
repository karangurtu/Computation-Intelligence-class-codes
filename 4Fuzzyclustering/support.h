#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<ctime>

using namespace std;

int file_fetch(float f[150][4])
{
	ifstream iris;//creating file handle
	char data[20];
	//float f[150][4];

	iris.open("iris_data.txt");//attaching file handle to IRIS data file
	if (iris.is_open())
	{
		//cout<<"IRIS data file is successfully opened.\n";
	}
	else
    {
		cout << "Unable to open iris_data.txt file";
        return -1;
    }

	//cout<<"Extracting data from file into feature array f.\n";
	//Extracting data from file into feature array f
	for(int count=0;count<150;count++)
	{
		iris.get(data,5);
		//cout<<data<<"\n";
		f[count][0]=atof(data);
		iris.get(data,5);
		//cout<<data<<"\n";
		f[count][1]=atof(data);
		iris.get(data,5);
		//cout<<data<<"\n";
		f[count][2]=atof(data);
		iris.get(data,5);
		//cout<<data<<"\n";
		f[count][3]=atof(data);
		iris.getline(data,20);
		//cout<<data<<"\n";
     }
     iris.close();//closing file handle
     cout<<"\n1.    Iris Data read and put in matrix.\n";
     //Extracting data from  file into feature array f complete
     return 0; //return successful
}
