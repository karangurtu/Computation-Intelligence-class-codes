//Programmer : Manish Sharma
//msivent@gmail.com

#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

int file_fetch(float f[150][4])
{
	ifstream iris;//creating file handle
	char data[20];
	//float f[150][4];

	iris.open("iris_data.txt");//attaching file handle to IRIS data file
	if (iris.is_open())
	{
		cout<<"IRIS data file is successfully opened.\n";
	}
	else
    {
		cout << "Unable to open file";
        return -1;
    }

	cout<<"Extracting data from file into feature array f.\n";
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
     cout<<"Data Extraction Complete.\n";
     //Extracting data from  file into feature array f complete
     return 0; //return successful
}

int random_no_gen(int random_arr[],int number=35,int max=50)
{
     //cout<<"\n\nSelecting 70% random data set for training.... ";

     //number is saving total number of random numbers to be generated
     //max is saving value for (maximum-1) value of random number
     //random_arr[] is saving random variables generated in an ascending order

     int count =0; //keeping count of how many numbers are generated till now
     int flag=0; //keeping track if the number generated is generated previously also
     int i,j,k; //general variables used for looping
     unsigned int randNumber;
     int manish=0; //counter for refeeding my rng
     srand(time(0)); //Seeding my random number generator with my system time

     while(1)
     {
		 flag=0;
         //if((manish++)%10==0)
         //srand(time(0)); //Seeding my random number generator with my system time
		 randNumber = (rand()%max); // This gets a random number as an integer

		 for(i=0;i<count;i++)
		 {
						  if(randNumber==random_arr[i])
						  {
													   flag = 1;
													   break;
						  }
		 }
		 if(flag==0)
		 {
					random_arr[i]=randNumber;
					count++;
					if(count==number)
					{
								 break;
					}
		 }
     }
     //Sorting of random variables
     int min,extra;
     for(i=0;i<34;i++)
     {
          min=random_arr[i];
          k=i;
          for(j=i+1;j<35;j++)
          {
               if(min>random_arr[j])
               {
                    k=j;
                    min=random_arr[k];
               }
          }
          extra=random_arr[i];
          random_arr[i]=min;
          random_arr[k]=extra;
     }
     return 0;
}
int test_sample_gen(int random_arr[],int test_sample[])
{
    int i,j,k,num,extra,min;

    for(i=0,j=0,k=0;i<35 || k<15 ;i++,j++)
    {
               if(random_arr[i] != j)
               {
                                test_sample[k]=j;
                                i=i-1;
                                k=k+1;
               }
    }
    return 0;
}

int DF_initial_prediction(float DF[][5])
{
    srand(time(0)); //Seeding my random number generator with my system time
    for(int i=0;i<3;i++)
    {
         for(int j=0;j<5;j++)
              //DF[i][j]=i+j*2; //doing just a random thing... :( don't know why
        	  DF[i][j]=(float((rand()%10))/40); // feeding DF with random variables of the order of 1/num(class) in this case .33
        	  //DF[i][j]=i*1000;
    }
    return 0;
}

int max(float var[3])
{
    if((var[0]>var[1]) && (var[0]>var[2]))
    return 0;
    else if((var[1]>var[0]) && (var[1]>var[2]))
    return 1;
    else if((var[2]>var[0]) && (var[2]>var[1]))
    return 2;
    else return -1;
}
