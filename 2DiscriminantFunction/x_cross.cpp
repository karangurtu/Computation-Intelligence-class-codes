#include<iostream>
#include<math.h>

using namespace std;

#include "iris_header.h"

#define MAX_EPOCH 2000

int file_fetch(float f[150][4]);
int random_no_gen(int random_arr[],int number,int max);
int test_sample_gen(int random_arr[],int test_sample[]);
int DF_initial_prediction(float DF[][5]);
int max(float var[3]);


int x_cross()
{
    //general variable declarations
    float f[150][4]; //used for saving extracted data from file in array
    int training_sample[35],test_sample[15]; //used for saving test samples and training samples
    int i,j,k; //used for looping
    char feature_names[4][30]={"sepal length in cm","sepal width in cm","petal length in cm","petal width in cm"};
    char class_names[3][20]={"Iris-setosa","Iris-versicolor","Iris-virginica"};
    
    //fetching data from iris_data.txt to floating type matrix f
    file_fetch(f);
    
    //training sample and testing sample generation
    random_no_gen(training_sample,35,50);
    test_sample_gen(training_sample,test_sample);
    
    //Discriminant function generation
    float DF[3][5]; // for 3 classes and 4 features
    float DF_copy[3][5];
    float DF_value[3];
    float gamma;// = 0.001;//.001;// gamma = learning rate
    //.02 is giving 94% error in first iteration
    //not converging for above .015, tested on .016
    float LR=0.015;
    int pr_error=0,error=0,p;
    int pr_class,actual_class;
    int a1,a2;//used for copy of DF to DF_copy
    int continuity=0;//will keep track of number of same errors in previous countings
    
    //doing initial prediction of Discriminant function.. binomial or any other trick
    
    DF_initial_prediction(DF);
    
//    cout<<"\n\nProgrammer : Manish sharma\n\n";
    
    cout<<"Discriminant function before training :\n\n";
    for(i=0;i<3;i++)
    {
         cout<<"DF "<<i+1<<" : ";
         for(j=0;j<5;j++)
         {
              cout<<DF[i][j];
              if(j==0)
                   cout<<" + ";
              else if(j!=4)
                   cout<<" f"<<j<<" + ";
              else cout<<" f"<<j;
         }          
         cout<<"\n";
    }
    
    cout<<"\nTraining...... ";
    for(int epoch=0;epoch<MAX_EPOCH;epoch++)//training loop should stop automatically after the loop saturates
    {
            // creating copy of Discriminant function            
            error=0;
            for(a1=0;a1<3;a1++)
                 for(a2=0;a2<5;a2++) DF_copy[a1][a2] = DF[a1][a2];
            for(j=0;j<35;j++)
            {
                 for(actual_class=0,i=0;actual_class<3;actual_class++,i++)//this loop is taking care that sample from each class is fed one by one
                      {
                      //sample j of class i has been selected
                      p=training_sample[j];
                      //Calculating DF_values for above sample
                      for(k=0;k<3;k++)
                      {
                           DF_value[k]=DF_copy[k][0] + DF_copy[k][1]*f[(i*50)+p][0] + DF_copy[k][2]*f[(i*50)+p][1] + DF_copy[k][3]*f[(i*50)+p][2] + DF_copy[k][4]*f[(i*50)+p][3];
                      }
                      pr_class = max(DF_value);//Predict class on the basis of DF//  <-------------- Decision making
                      
                      if(pr_class != actual_class ) 
                      {    
                           error+=1;
                      //correct coefficients of actual_class and pr_class   // <--------------- Correction
                           if(pr_class == -1)
                           {    
                                //correct acutal class with epsilon error to remove deadlock
                                DF_copy[actual_class][0] = DF_copy[actual_class][0] + .01;
                           }
                           else
                           {
                                gamma = LR/(1+epoch); // formulae for adaptive learning rate
                                //correct actual class and pr_class both
                                DF_copy[actual_class][0]   =  DF_copy[actual_class][0] + gamma*fabs(DF_value[actual_class]-DF_value[pr_class]);
                                DF_copy[actual_class][1]   =  DF_copy[actual_class][1] + gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][0];
                                DF_copy[actual_class][2]   =  DF_copy[actual_class][2] + gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][1];
                                DF_copy[actual_class][3]   =  DF_copy[actual_class][3] + gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][2];
                                DF_copy[actual_class][4]   =  DF_copy[actual_class][4] + gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][3];
                                
                                DF_copy[pr_class][0]   =  DF_copy[pr_class][0] - gamma*fabs(DF_value[actual_class]-DF_value[pr_class]);
                                DF_copy[pr_class][1]   =  DF_copy[pr_class][1] - gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][0];
                                DF_copy[pr_class][2]   =  DF_copy[pr_class][2] - gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][1];
                                DF_copy[pr_class][3]   =  DF_copy[pr_class][3] - gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][2];
                                DF_copy[pr_class][4]   =  DF_copy[pr_class][4] - gamma*fabs(DF_value[actual_class]-DF_value[pr_class])*f[(i*50)+p][3];
                           }
                           
                      }
                 }
            }
            if(error==pr_error) continuity++;
            else continuity = 0;
            
            pr_error=error;
            cout<<"\nErrors = "<<(float(error)*100)/105<<" % ,in epoch "<<epoch+1<<" ,Learning rate :"<<gamma;
            //condition for breaking the loop
            if(continuity ==20)           
            {
                 cout<<"\n\nLast 20 epochs have shown no visible improvement ,";
                 cout<<"so ending further iterations :)";
            break;
            }
            // creating copy of Discriminant function            
            for(a1=0;a1<3;a1++)
                 for(a2=0;a2<5;a2++) DF[a1][a2] = DF_copy[a1][a2];
    }        
    cout<<"\n\nDiscriminant function after training :\n\n";
    for(i=0;i<3;i++)
    {
         cout<<"DF "<<i+1<<" : ";
         for(j=0;j<5;j++)
         {
              cout<<DF_copy[i][j];
              if(j==0)
                   cout<<" + ";
              else if(j!=4)
                   cout<<" f"<<j<<" + ";
              else cout<<" f"<<j;
         }          
         cout<<"\n";
    }
    error=0;
    for(actual_class=0,i=0;actual_class<3;actual_class++,i++)//this loop is taking care that sample from each class is fed one by one
    {
         for(j=0;j<15;j++)
         {     
              //sample j of class i has been selected
              p=test_sample[j];
              //Calculating DF_values for above sample
              for(k=0;k<3;k++)
              {
                   DF_value[k]=DF_copy[k][0] + DF_copy[k][1]*f[(i*50)+p][0] + DF_copy[k][2]*f[(i*50)+p][1] + DF_copy[k][3]*f[(i*50)+p][2] + DF_copy[k][4]*f[(i*50)+p][3];
              }
              pr_class = max(DF_value);//Predict class on the basis of DF//  <-------------- Decision making
              
              if(pr_class != actual_class ) 
              {    
                           error+=1;     
              }
         }
    }
    cout<<"\nError in testing data is : "<<(float(error)*100)/45<<" %\n\n";
    
    return 0;                
}

int main()
{
    int x=10;
    //x_cross validation loop
    for(int i=0;i<10;i++)
    {
         cout<<"\n\nCROSS FOLD VALIDATION "<<i+1<<"\n\n";
         x_cross();
         system("PAUSE");
    }
    return 0;
}
