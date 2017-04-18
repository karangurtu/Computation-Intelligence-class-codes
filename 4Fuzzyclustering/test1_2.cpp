#include<iostream>
using namespace std;

#include<float.h>
#include<math.h>
#include"support.h"
//c is number of clusters
//no_f is number of features
//n is number of samples

int file_fetch(float f[150][4]);

int fuzzy_clustering(int c,int n,int no_f,float b)
{
    //iris dependent steps
    float f[150][4]; //used for saving extracted data from file in array
    file_fetch(f);
    //iris data saved in array f

    float p[6][4];
    int a,d;
    /*
    for(int i=0;i<6;i++)
    {
        a=i/2;d=i%2;
        for(int j=0;j<4;j++)
        {
            p[i][j] = f[(50*a)+d][j];
        }
    }
    */
    //P(wi|xj) matrix storing membership values of each sample to multiple class
    //its dimension will be
    float P_wi_xj[3][150]; //[c][n]
    float centroid[4][3]; //[no_f][c]
    float distance[3][150]; //[c][n]

    //n=6;

    //initialize centroid
    float max[4]={FLT_MIN,FLT_MIN,FLT_MIN,FLT_MIN};
    float min[4]={FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};
    //min and max computation
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<no_f;j++)
        {
            if(f[i][j]<min[j]) min[j]=f[i][j];
            if(f[i][j]>max[j]) max[j]=f[i][j];
        }
    }
    //cout<<min[0]<<"\t"<<min[1]<<"\t"<<min[2]<<"\t"<<min[3]<<"\n";
    //cout<<max[0]<<"\t"<<max[1]<<"\t"<<max[2]<<"\t"<<max[3]<<"\n\n";

    //not randomized for the timebeing... will randomize this later
    for(int i=0;i<no_f;i++)
    {
        for(int j=0;j<c;j++)
        {
            centroid[i][j] = min[i] + ((max[i]-min[i])/(2*c)) + ((max[i]-min[i])/c)*j;
            //cout<<centroid[i][j]<<"\t";
        }
        //cout<<"\n";
    }

    //convergence loop from here on
    //float P_wi_xj[3][150]; //[c][n]    //float centroid[4][3]; //[no_f][c] vars defined above
    float onebyd;
    int counter = 20;
    while(counter--)//1
    {
        //updation of distance matrix
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<c;j++)
            {
                distance[j][i]=0;
                for(int k=0;k<no_f;k++)
                {
                    float var1=f[i][k];
                    float var2=centroid[k][j];
                    float var = var1-var2;
                    var=pow(f[i][k]-centroid[k][j],2);

                    distance[j][i] += pow(f[i][k]-centroid[k][j],2);
                }
            }
        }
        //update membership values
        for(int i=0;i<n;i++)//no of samples
        {
            float wi_xj_den = 0;
            float total = 0;
            for(int j=0;j<c;j++) //no of clusters
            {
                wi_xj_den += pow((1/distance[j][i]),(1/(b-1)));
            }

            for(int k=0;k<c;k++)
            {
                onebyd = 1/distance[k][i];
                onebyd = pow(onebyd,1/b-1);
                P_wi_xj[k][i] = pow((1/distance[k][i]),(1/(b-1)))/wi_xj_den;
                total += P_wi_xj[k][i];
            }
            //nor required
            for(int l=0;l<c;l++)
            {
                P_wi_xj[l][i] /=total;//normalization
            }
        }
        //membership values update complete

        //update centroids
        for(int i=0;i<c;i++)//number of centroids
        {
            float Ui_num[4] = {0,0,0,0};
            float Ui_den = 0;
            for(int j=0;j<n;j++) //no of samples
            {
                for(int k=0;k<no_f;k++)    //no of features 4 dimensional vector
                {
                    Ui_num[k] += pow(P_wi_xj[i][j],b)*f[j][k];
                }
                Ui_den += pow(P_wi_xj[i][j],b);
            }
            for(int k=0;k<no_f;k++)
            {
                Ui_num[k] /= Ui_den;
                centroid[k][i] = Ui_num[k];
            }
        }
        //centroids update complete
        cout<<"\n";
/*
        for(int i=100;i<105;i++)
        {
            cout<<i+1<<" : ";
            for(int j=0;j<3;j++)
            {
                cout<<P_wi_xj[j][i]<<"\t";
            }
            cout<<"\n";
        }
        */
    }

    for(int i=0;i<150;i++)
        {
            cout<<i+1<<" : ";
            for(int j=0;j<3;j++)
            {
                cout<<P_wi_xj[j][i]<<"\t";
            }
            cout<<"\n";
        }

    return 0;
}

int main()
{
    int n = 150;    //no of samples
    int f = 4;      //no of features used per sample
    int c = 3;      //no of clusters assumed to be know in this case but can be a free parameter
                    //i will try to implement that later
    float b = 1.1;      //blending factor for b>1 criterion allowed each sample to belong to multiple cluster

    fuzzy_clustering(c,n,f,b);  //int c,int n,int no_f
}
