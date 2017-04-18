#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<cfloat>

using namespace std;

#define POP_SIZE 6
#define DOF 2

#define X_MAX 100
#define X_MIN -100
#define Y_MAX 100
#define Y_MIN -100

#define ELITE_SIZE 2
#define SIZE_VAR 32
#define epsilon 0.00000000000001
#define M_CONSTANT 1.1
#define pi 3.1416

#define MAXIMA 1


double my_function(unsigned int var1[],int original)
{
    double var[2],return_val;
    double x,y;
    var[0]=X_MIN +(X_MAX-X_MIN)*(var1[0]/4.294967296e9);
    var[1]=Y_MIN +(X_MAX-X_MIN)*(var1[1]/4.294967296e9);
    x=var[0];
    y=var[1];
    //change this function if you want to optimize for any other value
    //for maxima
    //return_val = cos(x);
    //return_val = sin(x);
    return_val = (pow(x,2) + pow(y,2))* exp(-(pow(x,2) + pow(y,2))); //CI class function
    //return_val = -pow(x,4) - pow(y,4) + 4*x*y; //B [-1,-1] and [1,1]

    //for minima
    //return_val = pow((1-x),2) + 100*pow((y-pow(x,2)),2); // Rosenbrock function[1,1]
    //return_val = 20 + pow(x,2) + pow(y,2) - 10*(cos(2*pi*x) + cos(2*pi*y)); //Rastrigin function [0,0]
    //return_val = 2*pow(x,2) - 4*x*y + pow(y,4) +2; //IB [-1,-1] and [1,1];
    //return_val = (pow(x,2) + y -11) + pow(x+pow(y,2)-7,2); //min value is -13.6539
    //return_val = fabs(x-y-5); //pallav function

    if(original ==0)
    {
        return pow(M_CONSTANT,MAXIMA*return_val);
    }
    return return_val;
}

//a pseudo 32 bit random generator made by combining 2 16 bit rand()
unsigned int rand_32()
{
    return rand()<<17 | rand();
}

int elitist_selection(unsigned int pr_generation[POP_SIZE][DOF],double fitness_value[POP_SIZE],unsigned int nxt_generation[POP_SIZE][DOF])
{
    //sorting of present generation
    int i,j;
    double var1;
    unsigned int var2;

    for(i=0;i<POP_SIZE-1;i++)
    {
        for(j=0;j<POP_SIZE-i-1;j++)
        {
            if(fitness_value[j]<fitness_value[j+1])
            {
                var1=fitness_value[j+1];
                fitness_value[j+1]=fitness_value[j];
                fitness_value[j]=var1;

                var2=pr_generation[j+1][0];
                pr_generation[j+1][0]=pr_generation[j][0];
                pr_generation[j][0]=var2;

                var2=pr_generation[j+1][1];
                pr_generation[j+1][1]=pr_generation[j][1];
                pr_generation[j][1]=var2;
            }
        }
    }
    //selection of elite members of pr_generation

    for(i=0;i<ELITE_SIZE;i++)
    {
        for(j=0;j<DOF;j++)
        {
            nxt_generation[i][j]=pr_generation[i][j];
        }
    }
    return 0;
}

int roulette_wheel(double fitness_value[POP_SIZE],int roulette_op[2])
{
    int i;
    double sum=0;
    int selection;

    double angle[POP_SIZE]={0};

    for(i=0;i<POP_SIZE;i++)
    {
        sum = sum + fitness_value[i];
        //sum = sum + fabs(1/log10(fitness_value[i]));
        //sum = sum + pow(1.1,fitness_value[i]);
    }

    angle[0]=(fitness_value[0]/sum)*360;
    //angle[0] = (fabs(1/log10(fitness_value[0]))/sum)*360;
    //angle[0] = (pow(MANISH_CONSTANT,fitness_value[0])/sum)*360;

    for(i=1;i<POP_SIZE;i++)
    {
        angle[i]= angle[i-1] + (fitness_value[i]/sum)*360;
        //angle[i]= angle[i-1] + (pow(MANISH_CONSTANT,fitness_value[0])/sum)*360;
    }

    //selection of first parent
    selection = (rand()%360);
    for(i=0;i<POP_SIZE;i++)
    {
        if(selection<angle[i])
        {
            roulette_op[0]=i;
            break;
        }
    }
    //selection of 2nd parent
    int m; // to avoid deadlock
    do
    {
        m++;
        selection = (rand()%360);
        for(i=0;i<POP_SIZE;i++)
        {
            if(selection<angle[i])
                roulette_op[1]=i;
        }
        if(m>4) // to avoid dead lock
        {
            roulette_op[1]=rand()%POP_SIZE;
        }
    }while(roulette_op[1]==roulette_op[0]);

    return 0;
}

int cross_over(unsigned int pr_generation[POP_SIZE][DOF],unsigned int nxt_generation[POP_SIZE][DOF],int roulette_op[2],int iteration)
{

    double var=double(rand());
    var=var/RAND_MAX;
    if(var<0.7) //perform cross over when Pco criteria is met
    {
        //for 1st dimension
        int cross_over_point = rand()%(SIZE_VAR-1);

        //crossover with environmental effects
        nxt_generation[ELITE_SIZE+(iteration*2)][0]= ((pr_generation[roulette_op[0]][0]>>cross_over_point)<<cross_over_point) | (pr_generation[roulette_op[1]][0]<<(SIZE_VAR-cross_over_point)>>(SIZE_VAR-cross_over_point));
        nxt_generation[ELITE_SIZE+(iteration*2)][0] = nxt_generation[ELITE_SIZE+(iteration*2)][0] ^ (1<<(rand()%(SIZE_VAR/2)));

        nxt_generation[ELITE_SIZE+(iteration*2)+1][0]= ((pr_generation[roulette_op[1]][0]>>cross_over_point)<<cross_over_point) | (pr_generation[roulette_op[0]][0]<<(SIZE_VAR-cross_over_point)>>(SIZE_VAR-cross_over_point));
        nxt_generation[ELITE_SIZE+(iteration*2)+1][0] = nxt_generation[ELITE_SIZE+(iteration*2)+1][0] ^ (1<<(rand()%(SIZE_VAR/2)));
        //for 2nd dimension
        cross_over_point = rand()%(SIZE_VAR-1);
        nxt_generation[ELITE_SIZE+(iteration*2)][1]= ((pr_generation[roulette_op[0]][1]>>cross_over_point)<<cross_over_point) | (pr_generation[roulette_op[1]][1]<<(SIZE_VAR-cross_over_point)>>(SIZE_VAR-cross_over_point));
        nxt_generation[ELITE_SIZE+(iteration*2)][1] = nxt_generation[ELITE_SIZE+(iteration*2)][1] ^ (1<<(rand()%(SIZE_VAR/2)));

        nxt_generation[ELITE_SIZE+(iteration*2)+1][1]= ((pr_generation[roulette_op[1]][1]>>cross_over_point)<<cross_over_point) | (pr_generation[roulette_op[0]][1]<<(SIZE_VAR-cross_over_point)>>(SIZE_VAR-cross_over_point));
        nxt_generation[ELITE_SIZE+(iteration*2)+1][1] = nxt_generation[ELITE_SIZE+(iteration*2)+1][1] ^ (1<<(rand()%(SIZE_VAR/2)));
    }

    if(rand()/RAND_MAX<0.05) //perform cross over when Pmu criteria is met
    {
        nxt_generation[ELITE_SIZE+(iteration*2)][0] = nxt_generation[ELITE_SIZE+(iteration*2)][0] ^ (1<<((rand()%(SIZE_VAR/2))+SIZE_VAR/2));
        nxt_generation[ELITE_SIZE+(iteration*2)+1][0] = nxt_generation[ELITE_SIZE+(iteration*2)+1][0] ^ (1<<((rand()%(SIZE_VAR/2))+SIZE_VAR/2));
        nxt_generation[ELITE_SIZE+(iteration*2)][1] = nxt_generation[ELITE_SIZE+(iteration*2)][1] ^ (1<<((rand()%(SIZE_VAR/2))+SIZE_VAR/2));
        nxt_generation[ELITE_SIZE+(iteration*2)+1][1] = nxt_generation[ELITE_SIZE+(iteration*2)+1][1] ^ (1<<((rand()%(SIZE_VAR/2))+SIZE_VAR/2));
    }

    return 0;
}


int main()
{
    int i,j,k;
    unsigned int pr_generation[POP_SIZE][DOF]; //32 bit representation for population
    unsigned int nxt_generation[POP_SIZE][DOF]; //32 bit representation for population
    double fitness_value[POP_SIZE]; //variable for saving value of function for the population
    int roulette_op[2];
    double old_fitness,new_fitness;

    //random population generation
    srand(time(0));
    for(i=0;i<POP_SIZE;i++)
    {
        for(j=0;j<DOF;j++)
        {
            pr_generation[i][j] = rand_32();
            cout<<pr_generation[i][j]<<"\t";
        }
        fitness_value[i]=my_function(pr_generation[i],1);
        cout<<fitness_value[i]<<"\n";
    }
    //end of population generation

    int m_cnt=0,m_on=0;
    cout<<"\n\nLOOPING START :\n\n";
    //loop
    for(i=0;i<5000;i++)
    {
        //new_fitness = 0;

        cout<<"\nLoop : "<<i<<"\n";

        elitist_selection(pr_generation,fitness_value,nxt_generation);
        cout<<"ELITES top 2 values:"<<my_function(nxt_generation[0],1)<<"\t"<<my_function(nxt_generation[1],1)<<"\n";

        for(j=0;j<(POP_SIZE-ELITE_SIZE)/2;j++)
        {
            roulette_wheel(fitness_value,roulette_op);
            //cout<<"ROULETTE OP :"<<roulette_op[0]<<"\t"<<roulette_op[1]<<"\n";
            cross_over(pr_generation,nxt_generation,roulette_op,j);
        }
        old_fitness = new_fitness;
        new_fitness = my_function(nxt_generation[0],1);
        double sign = old_fitness-new_fitness;

        if(fabs(sign) < 0.00001) m_cnt++;
        else    m_cnt = 0;

        if(m_cnt == 1000)
        break;

        //updating generation and fitness value
        for(j=0;j<POP_SIZE;j++)
        {
            for(k=0;k<DOF;k++)
            {
                pr_generation[j][k] = nxt_generation[j][k];
            }
            fitness_value[j]=my_function(pr_generation[j],0); //recalculate fitness
        }
        //cout<<"new_fitness measure= " <<"\t"<<new_fitness;
    }

    cout<<"\n\nFINAL ANSWER :\n\n ";
    cout<<"ELITES value at max or min :"<<my_function(nxt_generation[0],1)<<"\t"<<my_function(nxt_generation[1],1)<<"\n";
    double var[2];
    var[0]=X_MIN +(X_MAX-X_MIN)*(nxt_generation[0][0]/4.294967296e9);
    var[1]=Y_MIN +(X_MAX-X_MIN)*(nxt_generation[0][1]/4.294967296e9);
    cout<<"ELITES position :"<<var[0]<<"\t"<<var[1];//<<"\t"<<my_function(nxt_generation[1])<<"\n";


    return 0;
}
