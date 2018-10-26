#include <cstdio>
#include <vector>
#include<algorithm>
#include<time.h>
#include<math.h>
using namespace std;

#define accepted_error 0.001

int main()
{

    srand(time(NULL));
    float alpha = 1;
    int i,j,k,l,m,steps=0;
    float V[5][5],W[5][5],Z[4][10],z_total,y_total;
    float Y[4]= {0,0,0,0};
    float Delta[4],delW[4][2],delZ[4][3],delV[4][3];
    int  X[4][2]=
    {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    float T[4]= {1,0,0,1}; // these are our targets

    V[0][1]=1.0/(rand()%100+1);
    V[0][2]=1.0/(rand()%100+1);
    V[1][1]=1.0/(rand()%100+1);
    V[1][2]=1.0/(rand()%100+1);
    V[2][1]=1.0/(rand()%100+1);
    V[2][2]=1.0/(rand()%100+1);
    W[0][1]=1.0/(rand()%100+1);
    W[1][1]=1.0/(rand()%100+1);
    W[2][1]=1.0/(rand()%100+1);


    while(1)
    {
        for(i=0; i<4; i++)
        {

            for(j=1; j<4; j++)
            {
                z_total=V[0][j];
                for(l=1; l<3; l++)
                {
                    z_total=z_total+X[i][l-1]*V[l][j];
                }
                Z[i][j]=1/(1+exp(z_total*(-1)));

            }
            y_total=W[0][1];
            for(j=1; j<3; j++)
            {
                y_total=y_total+Z[i][j]*W[j][1];

            }

            Y[i]=1/(1+exp(y_total*(-1)));

            Delta[i]=(T[i]-Y[i])*(Y[i]*(1-Y[i]));
            //  printf("Del[%d]= %f\n",i,Del[i]);
            delW[i][0]=Delta[i];

            for(j=1; j<3; j++)
            {
                delW[i][j]=Z[i][j]*Delta[i];

                // printf("delW[%d][1]= %f\n",j,delW[i][j]);

            }
            for(j=1; j<3; j++)
            {

                delZ[i][j]=Delta[i]*W[j][1];
                delZ[i][j]=delZ[i][j]*(1-Z[i][j])*Z[i][j];

                delV[0][j]=delZ[i][j];

                for(k=1; k<3; k++)
                {
                    delV[k][j]=delZ[i][j]*X[i][k-1];

                }



            }
            for(j=0; j<3; j++)
            {
                W[j][1]=W[j][1]+delW[i][j];
            }
            for(k=1; k<3; k++)
            {
                for(j=0; j<4; j++)
                {
                    V[j][k]=V[j][k]+delV[j][k];
                }
            }

        }

        //printf("number of steps = %d\n",steps);

        int num_of_acc = 0;
        for(int i=0;i<4;i++){
            if(fabs(T[i]-Y[i])<=accepted_error){
                num_of_acc++;
            }
        }

        if(num_of_acc>=4)
            break;

        else
            steps++;

        /*for(j=0; j<4; j++)
        {
            printf("T[%d] = %f and Y[%d]= %f\n",j,T[j],j,Y[j]);
        }*/

    }

    printf("\nThe modified weights:\n");


    for(i=0; i<4; i++)
    {
        for(j=1; j<3; j++)
        {
            printf("z[%d][%d] = %f\n",i,j,Z[i][j]);
        }
    }

    for(j=0; j<3; j++)
    {
        printf("w[%d][%d] = %f\n",j,1,W[j][1]);
    }

    for(j=0; j<4; j++)
    {
        printf("T[%d] = %f and Y[%d]= %f\n",j,T[j],j,Y[j]);

    }
    for(k=1; k<3; k++)
    {
        for(j=0; j<3; j++)
        {
            V[j][k]=V[j][k]+delV[j][k];
        }
    }

    printf("\nTotal steps required = %d\n",steps);

    return 0;

}
