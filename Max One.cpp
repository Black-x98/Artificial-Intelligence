#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
#include <time.h>

using namespace std;

#define MAX 1000
#define INF (1<<20)
#define node pair<int,int>

int arr[6][11];
vector<node> grid_point;
int row_placed_in_column[8];
bool solved=false;
int imm_last_total_col=-1;

int print_array(){
    printf("\n");
    for(int i=0;i<6;i++){
        for(int j=0;j<10;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int total_fitness(){
    int total_fitness=0;
    for(int i=0;i<6;i++){
        int fitness=0;
        for(int j=0;j<10;j++){
            fitness+=arr[i][j];

        }
        arr[i][10]=fitness;
        total_fitness+=fitness;
    }
    return total_fitness;
}

int mutate(){

    int probability = rand()%10;
    for(int i=0;i<probability;i++){
        int ind1 = rand()%6;
        int ind2 = rand()%10;
        arr[ind1][ind2]=1;
    }
}

int crossover(){

    int num_of_cross = rand()%3;

    for(int i=0;i<num_of_cross;i++){

        int pair1 = rand()%6;
        int pair2 = rand()%6;
        int pos1 = rand()%10;
        int pos2 = rand()%10;

        if(pair1!=pair2){
            for(int i=pos1;i<=pos2;i++){
                //swap_arr_element();
                int temp = *arr[pair1];
                *arr[pair1] = *arr[pair2];
                *arr[pair2] = temp;

            }
        }
    }
}


int main(){
    int x,y;

    srand(time(NULL));


    for(int i=0;i<6;i++){
        int fitness=0;
        for(int j=0;j<10;j++){
            arr[i][j]=rand()%2;
            fitness+=arr[i][j];

        }
        arr[i][10]=fitness;
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<11;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }

    printf("\nTotal fitness: %d\n",total_fitness());

    int num_of_times=0;
    while(total_fitness()<60){

        crossover();
        mutate();
        num_of_times++;
        printf("Total fitness : %d\n",total_fitness());
        print_array();

    }

    printf("The number of times required = %d\n",num_of_times);
    //print_grid();


    return 0;
}
