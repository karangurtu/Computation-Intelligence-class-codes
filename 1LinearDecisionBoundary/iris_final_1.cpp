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
		cout<<"IRIS data file is successfully opened...\n";
	}
	else
    {
		cout << "Unable to open file";
        return -1;
    }

	cout<<"Extracting data from file into feature array f...\n";
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
     //Extracting data from  file into feature array f complete
     return 0; //return successful
}


int random_no_gen(int random_arr[],int number=35,int max=50)
{
     //Selecting random data set for training

     cout<<"\n\nSelecting 70% random data set for training.... ";
     int count =0;
     int flag=0,i,j,k;
     float no,p;
     unsigned int randNumber;
     int manish=0;


     while(1)
     {
		 flag=0;
         if((manish++)%10==0)
         srand(time(0));
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
					//cout<<count<<"....";
					if(count==number)
					{
								 break;
					}
		 }
     }
     /*
     cout<<"\n\nPrinting random numbers .... \n\n";
     for(i=0;i<35;i++)
     {
                      cout<<random_arr[i]<<"\t";
     }
     */
     return 0;
}
int test_sample_gen(int random_arr[],int test_sample[])
{
    int i,j,k,num,extra,min;
    //for(i=0;i<35;i++) cout<<"\t"<<random_arr[i];
    //Sorting of random variables
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
    //cout<<"\nSorted\n\n";
    //for(i=0;i<35;i++) cout<<"\t"<<random_arr[i];

    for(i=0,j=0,k=0;i<35 || k<15 ;i++,j++)
    {
               if(random_arr[i] != j)
               {
                                test_sample[k]=j;
                                i=i-1;
                                k=k+1;
               }
    }
    //if(random_arr[34] !=49)
    //test_sample[14]=49;
    //cout<<"\nTest Sample \n\n";
    //for(i=0;i<15;i++) cout<<"\t"<<test_sample[i];
    //cout<<"\n";
    //system("PAUSE");
    return 0;
}

int freq_distribution(float f[][4],int random_arr[],float f_count[][2][3],int num[],int feature,int number=35)
{
     //finding the frequency distribution of data p(fi|Cj)
     int i,j,k;
     int flag,count;
     float no;
     for(i=0;i<number;i++)
                      for(j=0;j<2;j++)
                                      for(k=0;k<3;k++)
                                                      f_count[i][j][k]=0.0;

     flag=0;count=0;
     for(k=0;k<3;k++)
     {
                     count=0;
                     for(j=0;j<number;j++)//number is 35 by default
                     {
                                      flag=0;
                                      no=f[random_arr[j]+(50*(k))][feature]; //fetching random element from feature array
                                      //cout<<"no="<<no<<"..\t";
                                      for(i=0;i<count;i++)
                                      {
                                                          if(no==f_count[i][0][k])
                                                          {
                                                                                      flag=1;
                                                                                      break;
                                                          }
                                      }
                                      if(flag==1)
                                      {
                                                 f_count[i][0][k]=no;
                                                 f_count[i][1][k]+=1;
                                      }
                                      else
                                      {
                                                 f_count[count][0][k]=no;
                                                 f_count[count][1][k]+=1;
                                                 count++;
                                      }
                     }
                     num[k]=count;
     }

     //cout<<"\n\nfrequency plot.... \n";
     /*
     for(i=0;i<3;i++)
     {
                     cout<<"\nCLASS "<<i<<"....\n\n";
                     for(j=0;j<num[i];j++)
                     {
                                          for(k=0;k<2;k++)
                                          {
                                                          cout<<f_count[j][k][i]<<"\t";
                                          }
                                          cout<<"\n";
                     }
     }
     */
     return 0;
}

int freq_sort(float freq_count[][2][3],int num[3],int count=3)
{
    unsigned int i,j,k,l;
    float min=0;
    float third[2];
    for(i=0;i<3;i++)
    {
                   for(j=0;j<num[i]-1;j++)
                   {
                                        min=freq_count[j][0][i];
                                        l=j;//very important i forgot to do this initially
                                        for(k=j+1;k<num[i];k++)
                                        {
                                                               if(min>freq_count[k][0][i])
                                                               {
                                                                                          min=freq_count[k][0][i];
                                                                                          l=k;
                                                               }


                                        }
                                        //swapping
                                        third[0]=freq_count[j][0][i];
                                        freq_count[j][0][i]=freq_count[l][0][i];
                                        freq_count[l][0][i]=third[0];
                                        third[1]=freq_count[j][1][i];
                                        freq_count[j][1][i]=freq_count[l][1][i];
                                        freq_count[l][1][i]=third[1];
                   }
    }
    return 0;
}

int maxval(float no1,float no2,float no3)
{
    static int previous_return=0;

    if((no1 > no2) && (no1 > no3))
    {
            previous_return = 0;
            return 0;
    }
    else if((no2 > no1) && (no2 > no3))
    {
         previous_return = 1;
         return 1;
    }
    else if((no3 > no1) && (no3 > no2))
    {
         previous_return = 2;
         return 2;
    }
    //else return previous_return;
    else return -1;
}

int classification(float freq_count[][2][3],int num[],int sequence[],float decision_boundary[],float graph[100][2],float & max,float & min)
{
    int i,j,k;
    float mode[3],min_copy;
    /*int goodness=class_sequence(freq_count,num,sequence,mode);
    if(goodness==-1)
    {
                    //cout<<"\nfeature not good for classification...\n";
    }
    */
    //cout<<"Sequence= \t"<<sequence[0]<<"\t"<<sequence[1]<<"\t"<<sequence[2]<<"\n";
    //deciding on decision boundary...
    //first dicision boundary will lie between seq[0] and seq[1] 2nd b/w seq[1] and seq[2]
    //Combining 2 classes in one matrix
    //float graph[100][2];

    //min=freq_count[0][0][sequence[0]];
    //max=freq_count[num[sequence[2]]-1][0][sequence[2]];
    if(freq_count[0][0][0]<=(freq_count[0][0][1]+0.01) && freq_count[0][0][0]<=(freq_count[0][0][2]+0.01))
         min=freq_count[0][0][0];
    else if(freq_count[0][0][1]<=(freq_count[0][0][0]+0.01) && freq_count[0][0][1]<=(freq_count[0][0][2]+0.01))
         min=freq_count[0][0][1];
    else min=freq_count[0][0][2];

    min_copy=min;

    if((freq_count[num[0]-1][0][0]+0.01)>=freq_count[num[1]-1][0][1] && (freq_count[num[0]-1][0][0]+0.01)>=freq_count[num[2]-1][0][2])
         max=freq_count[num[0]-1][0][0];
    else if((freq_count[num[1]-1][0][1]+0.01)>=freq_count[num[0]-1][0][0] && (freq_count[num[1]-1][0][1]+0.01)>=freq_count[num[2]-1][0][2])
         max=freq_count[num[1]-1][0][0];
    else max=freq_count[num[2]-1][0][2];

    //cout<<"\n"<<"min= "<<min<<"\t"<<"max= "<<max<<"\n";
    i=0;
    int p,q,r;
    float pass[3];
    int count[3]={0,0,0};

    do{
                               graph[i][0]=min;
                               for(j=0;j<3;j++)
                               {
                                               pass[j]=0.0;
                                               float a=freq_count[count[j]][0][j];
                                               if(num[j]<=count[j])
                                                   continue;
                                               while(freq_count[count[j]][0][j]<=min+0.01)//to remove floating point errors
                                               {
                                                    if(((freq_count[count[j]][0][j]-min)<=0.01) ||((freq_count[count[j]][0][j]-min)<=0.01))
                                                    {
                                                         pass[j]=freq_count[count[j]][1][j];
                                                         count[j]++;
                                                         break;
                                                    }
                                                    else
                                                    {
                                                         count[j]++;
                                                    }
                                               }
                               }

                               graph[i][1]=maxval(pass[0],pass[1],pass[2]);
                               //cout<<min<<"\t"<<pass[0]<<"\t"<<pass[1]<<"\t"<<pass[2]<<"\t"<<graph[i][1]<<"\n";
                               min+=0.1;
                               i=i+1;
    }while(min<=max);

    i=0;
    cout<<"\n\n";
    min=min_copy;
    /*
    do{
                     cout<<graph[i][0]<<"\t"<<"class "<<graph[i][1]<<"\n";
                     i=i+1;
                     min_copy=min_copy+0.1;
    }while(min_copy<=max);
    */
    int flag=0;
    int states=int(((max-min)/0.1)+1);

    //smoothening of decision matrix
    while(1)
    {
            flag=0;
            for(i=1;i<states;i++)
            {
                                 if(graph[i][1]==-1 && graph[i-1][1] !=-1)
                                 {
                                                    graph[i][1]=graph[i-1][1];
                                                    i+=1;
                                                    flag=1;
                                 }
            }
            for(j=states-2;j>=0;j--)
            {
                                    if(graph[j][1]==-1 && graph[j+1][1] !=-1)
                                    {
                                                       graph[j][1]=graph[j+1][1];
                                                       j-=1;
                                                       flag=1;
                                    }
            }
            if(flag==0) break;
    }
    min_copy=min;
    i=0;
    //cout<<"\n\n";
    cout<<"Decision Matrix :\n";
    do{
                     cout<<graph[i][0]<<"\t"<<"class "<<graph[i][1]<<"\n";
                     i=i+1;
                     min_copy=min_copy+0.1;
    }while(min_copy<=max);

    return 0;
}


int loop(float f[150][4],int random_arr[35],int test_sample[15],float graph[100][2],float & max,float & min,int feature)
{
     int i,j,k;
     //float f[150][4];
     //int random_arr[35];
     //int test_sample[15];
     float freq_count[35][2][3];
     for(i=0;i<35;i++)
     for(j=0;j<2;j++)
     for(k=0;k<3;k++)
     freq_count[i][j][k] = 0.0;
     int num[3];
     int sequence[]={0,1,2};
     float decision_boundary[10];

     random_no_gen(random_arr);
     test_sample_gen(random_arr,test_sample);

     //int feature=2;
     freq_distribution(f,random_arr,freq_count,num,feature);
     //cout<<num[0]<<"\t"<<num[1]<<"\t"<<num[2];
     freq_sort(freq_count,num);

     /*cout<<"\n\nClass 0\t\tClass 1\t\tClass 2\n";
     int flag;

     for(i=0;i<35;i++)
     {
                      flag=0;
                      for(j=0;j<3;j++)
                      {
                                      if(num[j]>i)
                                      {
                                                  cout<<freq_count[i][0][j]<<"\t"<<freq_count[i][1][j]<<"\t";
                                                  flag=1;
                                      }
                                      else
                                      {
                                      cout<<"\t\t";
                                      }

                      }
                      cout<<"\n";
                      if(flag==0) break;
     }
     */
     //float graph[100][2];
     //float max,min;
     classification(freq_count,num,sequence,decision_boundary,graph,max,min);
     //cout<<"\nmin="<<min<<"\tmax="<<max<<"\n\n";
     return 0;
}

float error(float f[150][4],int test_sample[15],float graph[100][2],float max,float min,int feature)
{
      float error=0;
      int i,j,k;
      int ip_class,pr_class;    //ip = input , pr = predicted
      float ip_feature,diff;
      int states=int(((max-min)/0.1)+1+0.01);
      for(i=0;i<3;i++)
      {

                      ip_class=i;
                      for(j=0;j<15;j++)
                      {
                                       ip_feature=f[(i*50)+ test_sample[j]][feature];
                                       if(ip_feature <min+0.001)
                                            pr_class = int(graph[0][1]+0.01);
                                       else if(ip_feature >max-0.001)
                                            pr_class = int(graph[states-1][1]+0.01);
                                       else
                                       {
                                           diff=ip_feature-min;
                                           k=int((diff/0.1)+.01);
                                           pr_class=int(graph[k-1][1] +0.01); //find the position
                                       }

                                       if(ip_class!=pr_class)
                                       {
                                                       error+=1;
                                       }
                                       //find corrosponding classification
                                       //add error if not same..... hurrah u r done.... :)
                      }
      }
      error=(error/45)*100; //calculating error percentage
      return error;
}

int main()
{
    float f[150][4],graph[100][2],max,min;
    int random_arr[35],test_sample[15],feature=0,i,j,k;
    float err_per;
    char feature_names[4][30]={"sepal length in cm","sepal width in cm","petal length in cm","petal width in cm"};
    int N=4;//for n fold cross validation
    //Fetching data from file
    file_fetch(f);
    cout<<"\nClass 0 : Iris-setosa\n";
    cout<<"Class 1 : Iris-versicolor\n";
    cout<<"Class 2 : Iris-virginica\n";

    for(i=0;i<=3;i++)
    {
                     cout<<"\nTESTING FEATURE :"<<feature_names[i]<<"\n";
                    feature = i;
                    for(j=0;j<N;j++) // N fold cross validation
                    {
                                     cout<<"\n------------------------------------------------------------------------\n";
                                      cout<<"\n[ Feature :: "<<feature_names[i]<<" , Iteration :: "<<j+1<<" ]";
                                      loop(f,random_arr,test_sample,graph,max,min,feature);
                                      err_per=error(f,test_sample,graph,max,min,feature);
                                      cout<<"Percentage Error:"<<err_per;
                    }

                    cout<<"\n......"<<i<<" feature set test complete..\n";
                    system("PAUSE");
    }
    system("PAUSE");
    return 0;
}
