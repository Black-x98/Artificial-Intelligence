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

int grid[8][8];
int sec_grid[8][8];
vector<node> grid_point;
int row_placed_in_column[8];
bool solved=false;
int imm_last_total_col=-1;

class state{

public:
    int num_of_col,x,y,temp_x,temp_y;
    //int positions[8][2];
    state(int _num_of_col,int _x,int _y,int _temp_x,int _temp_y){
        num_of_col = _num_of_col;
        x = _x;
        y = _y;
        temp_x = _temp_x;
        temp_y = _temp_y;
    }

    bool operator< ( const state& other ) const
    { return num_of_col > other.num_of_col; }
};


priority_queue<state> pq;

priority_queue<state> temp_pq;

priority_queue<state> temp2_pq;




int get_heuristic(int x, int y){    // get_heuristic works fine

    int this_h=0;
    int temp_x=x+1, temp_y=y;
    while(temp_x<8){ // 1
        if(grid[temp_x][y]==1){
            //printf("adding in section 1\n");
            this_h+=1;
            break;
        }
        temp_x++;
    }
    temp_x=x-1, temp_y=y;
    while(temp_x>=0){ // 2
        if(grid[temp_x][y]==1){
            //printf("adding in section 2\n");
            this_h+=1;
            break;
        }
        temp_x--;
    }
    temp_x=x, temp_y=y+1;
    while(temp_y<8){ //3
        if(grid[x][temp_y]==1){
            //printf("adding in section 3\n");
            this_h+=1;
            break;
        }
        temp_y++;
    }
    temp_x=x, temp_y=y-1;
    while(temp_y>=0){ //4
        if(grid[x][temp_y]==1){
            //printf("adding in section 4\n");
            this_h+=1;
            break;
        }
        temp_y--;
    }
    temp_x=x+1, temp_y=y+1;

    while(temp_x<8 && temp_y<8){ //5
        if(grid[temp_x][temp_y]==1){
            //printf("adding in section 5\n");
            this_h+=1;
            break;
        }
        temp_x++;
        temp_y++;
    }

    temp_x=x-1, temp_y=y-1;
    while(temp_x>0 && temp_y>=0){ //6
        if(grid[temp_x][temp_y]==1){
            //printf("adding in section 6\n");
            this_h+=1;
            break;
        }
        temp_x--;
        temp_y--;
    }

    temp_x=x+1, temp_y=y-1;
    while(temp_x<8 && temp_y>=0){ //7
        if(grid[temp_x][temp_y]==1){
            //printf("adding in section 7\n");
            this_h+=1;
            break;
        }
        temp_x++;
        temp_y--;
    }

    temp_x=x-1, temp_y=y+1;
    while(temp_x>=0 && temp_y<8){ //8
        if(grid[temp_x][temp_y]==1){
            //printf("adding in section 8\n");
            this_h+=1;
            break;
        }
        temp_x--;
        temp_y++;
    }

    temp_x=x, temp_y=y;

    return this_h;

}

int grid_condition(){

    int total_collision=0;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(grid[i][j]==1){
                int col = get_heuristic(i,j);
                //printf("col = %d\n",col);
                total_collision+=col;
            }
        }
    }

    return total_collision;


}


void all_possible(int x,int y){

    int temp_x,temp_y;

    temp_x=x+1, temp_y=y;
    while(temp_x<8){ // 1
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x++;
    }
    temp_x=x-1, temp_y=y;
    while(temp_x>=0){ // 2
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x--;
    }
    temp_x=x, temp_y=y+1;
    while(temp_y<8){ //3
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_y++;
    }
    temp_x=x, temp_y=y-1;
    while(temp_y>=0){ //4
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_y--;
    }
    temp_x=x+1, temp_y=y+1;

    while(temp_x<8 && temp_y<8){ //5
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x++;
        temp_y++;
    }

    temp_x=x-1, temp_y=y-1;
    while(temp_x>0 && temp_y>=0){ //6
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x--;
        temp_y--;
    }

    temp_x=x+1, temp_y=y-1;
    while(temp_x<8 && temp_y>=0){ //7
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x++;
        temp_y--;
    }

    temp_x=x-1, temp_y=y+1;
    while(temp_x>=0 && temp_y<8){ //8
        if(grid[temp_x][temp_y]==0){
            grid[x][y]=0;
            grid[temp_x][temp_y]=1;
            int tot_col=grid_condition();
            pq.push(state(tot_col,x,y,temp_x,temp_y));
            state kkk = pq.top();
            grid[x][y]=1;
            grid[temp_x][temp_y]=0;
        }
        else{
            break;
        }
        temp_x--;
        temp_y++;
    }

    temp_x=x, temp_y=y;


}

void print_grid(){

    printf("\n");

    for(int i=0;i<8;i++){

        for(int j=0;j<8;j++){

            printf("%d ",grid[i][j]);
        }

        printf("\n");
    }

    printf("\n");

}

int modify_grid(){

    int random2=rand()%8;


    while(random2){
        temp_pq.pop();
        random2--;
    }

    state chosen_obj = temp_pq.top();
    while(!temp_pq.empty()){
        temp_pq.pop();
    }


    grid[chosen_obj.temp_x][chosen_obj.temp_y] = 1;
    grid[chosen_obj.x][chosen_obj.y] = 0;

    printf("\nMoving from [%d][%d] to [%d][%d]\n",chosen_obj.x,chosen_obj.y,chosen_obj.temp_x,chosen_obj.temp_y);



    imm_last_total_col=chosen_obj.num_of_col;

    return imm_last_total_col;

}


int main(){
    int x,y;

    srand(time(NULL));


    /*for(int i=0;i<8;i++){

        for(int j=0;j<8;j++){

            scanf("%d ",&grid[i][j]);
        }

    }*/

    for(int i=0;i<8;i++){

        x = rand()%8;

        if(grid[x][i]==0){
            grid[x][i]=1;
            printf("Entered 1 at [%d][%d]\n",x,i);
            row_placed_in_column[i]=x;
        }

    }

    int latest_col;

    int num_of_moves=0;
    while(!solved){


        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(grid[i][j]==1){
                    all_possible(i,j);
                    //temp_pq.push(pq.top());
                    int taken_col = pq.top().num_of_col;
                    int top_count=0;
                    while(pq.top().num_of_col==taken_col){
                        temp2_pq.push(pq.top());
                        pq.pop();
                        top_count++;
                    }
                    while(!pq.empty()){
                        pq.pop();
                    }
                    int random = rand()%top_count;
                    while(random) {
                        temp2_pq.pop();
                        random--;
                    }
                    temp_pq.push(temp2_pq.top());

                    while(!temp2_pq.empty()) {
                        temp2_pq.pop();
                    }
                }
            }
        }

        num_of_moves++;

        latest_col = modify_grid();

        print_grid();
        if(latest_col<=0){
            solved=true;
            break;
        }

    }

    //print_grid();

    printf("Number of collision: %d\n",latest_col);

    printf("The number of moves required = %d\n",num_of_moves);


    return 0;
}
