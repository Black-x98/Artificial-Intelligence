#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
#include <time.h>

int grid[3][3];

int print_grid()
{
    printf("\n");
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(grid[i][j]==1) printf("X ");
            else if(grid[i][j]==2) printf("O ");
            else if(grid[i][j]==0) printf("  ");
        }
        if(i<2) printf("\n-|-|-\n");
    }
    printf("\n\n");
}


class element_X
{

public:
    int x,y,heuristic;
    //int positions[8][2];
    element_X(int _x,int _y, int _heuristic)
    {
        x=_x;
        y=_y;
        heuristic = _heuristic;
    }

    bool operator< ( const element_X& other ) const
    {
        return heuristic < other.heuristic;
    }
};


class element_O
{

public:
    int x,y,heuristic;
    //int positions[8][2];
    element_O(int _x,int _y, int _heuristic)
    {
        x=_x;
        y=_y;
        heuristic = _heuristic;
    }

    bool operator< ( const element_O& other ) const
    {
        return heuristic > other.heuristic;
    }
};


std::priority_queue<element_X> pq_X;
std::priority_queue<element_O> pq_O;

// X 1, O 0


bool winning_condition(int player,int other)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(i==0&&j==0)
            {
                if(grid[i][j]==player&&grid[i][j+1]==player&&grid[i][j+2]==player) return true;
                if(grid[i][j]==player&&grid[i+1][j+1]==player&&grid[i+2][j+2]==player) return true;
                if(grid[i][j]==player&&grid[i+1][j]==player&&grid[i+2][j]==player) return true;
            }
            if(i==0&&j==1)
            {
                if(grid[i][j]==player&&grid[i+1][j]==player&&grid[i+2][j]==player) return true;
            }
            if(i==0&&j==2)
            {
                if(grid[i][j]==player&&grid[i+1][j]==player&&grid[i+2][j]==player) return true;
                if(grid[i][j]==player&&grid[i+1][j-1]==player&&grid[i+2][j-2]==player) return true;
            }
            if(i==1&&j==0)
            {
                if(grid[i][j]==player&&grid[i][j+1]==player&&grid[i][j+2]==player) return true;
            }
            if(i==2&&j==0)
            {
                if(grid[i][j]==player&&grid[i][j+1]==player&&grid[i][j+2]==player) return true;
            }
        }
    }
    return false;

}
int ttt_heuristic(int player, int other,int i,int j)
{

    int heuristic=0;

    if(i==0&&j==0)
    {
        if(grid[i][j]!=other&&grid[i][j+1]!=other&&grid[i][j+2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i+1][j+1]!=other&&grid[i+2][j+2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i+1][j]!=other&&grid[i+2][j]!=other) heuristic++;
    }
    if(i==2&&j==2)
    {
        if(grid[i][j]!=other&&grid[i][j-1]!=other&&grid[i][j-2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j-1]!=other&&grid[i-2][j-2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j]!=other&&grid[i-2][j]!=other) heuristic++;
    }
    if(i==0&&j==2)
    {
        if(grid[i][j]!=other&&grid[i][j-1]!=other&&grid[i][j-2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i+1][j-1]!=other&&grid[i+2][j-2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i+1][j]!=other&&grid[i+2][j]!=other) heuristic++;
    }
    if(i==2&&j==0)
    {
        if(grid[i][j]!=other&&grid[i][j+1]!=other&&grid[i][j+2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j+1]!=other&&grid[i-2][j+2]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j]!=other&&grid[i-2][j]!=other) heuristic++;
    }
    if(i==0&&j==1)
    {
        if(grid[i][j]!=other&&grid[i+1][j]!=other&&grid[i+2][j]!=other) heuristic++;
    }
    if(i==2&&j==1)
    {
        if(grid[i][j]!=other&&grid[i-1][j]!=other&&grid[i-2][j]!=other) heuristic++;
    }
    if(i==1&&j==0)
    {
        if(grid[i][j]!=other&&grid[i][j+1]!=other&&grid[i][j+2]!=other) heuristic++;
    }
    if(i==1&&j==2)
    {
        if(grid[i][j]!=other&&grid[i][j-1]!=other&&grid[i][j-2]!=other) heuristic++;
    }
    if(i==1&&j==1)
    {
        if(grid[i][j]!=other&&grid[i][j-1]!=other&&grid[i][j+1]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j]!=other&&grid[i+1][j]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i+1][j-1]!=other&&grid[i-1][j+1]!=other) heuristic++;
        if(grid[i][j]!=other&&grid[i-1][j+1]!=other&&grid[i+1][j-1]!=other) heuristic++;
    }

    return heuristic;
}





int main()
{

    int prev_turn=2;
    int current_turn=0;
    int t=9;
    while(t--)
    {

        if(prev_turn==2) current_turn=1;
        else current_turn=2;

        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(grid[i][j]==0)
                {
                    grid[i][j]=current_turn;
                    if(current_turn==1)
                    {
                        int h = ttt_heuristic(1,2,i,j)-ttt_heuristic(2,1,i,j);
                        pq_X.push(element_X(i,j,h));
                        //printf(" X Pushing x = %d y = %d h = %d\n",i,j,h);
                    }
                    else
                    {
                        int h = ttt_heuristic(1,2,i,j)-ttt_heuristic(2,1,i,j);
                        pq_O.push(element_O(i,j,h));
                        //printf(" O Pushing x = %d y = %d h = %d\n",i,j,h);
                    }
                    grid[i][j]=0;
                }
            }
        }
        if(current_turn==1)
        {
            element_X e = pq_X.top();
            grid[e.x][e.y]=current_turn;
            printf("X puts his mark on [%d][%d]\n",e.x,e.y);
            while(!pq_X.empty()) pq_X.pop();
            print_grid();
            if(winning_condition(1,2)==true)
            {
                printf("X won the game.\n");
                break;
            }
        }
        else
        {
            element_O e = pq_O.top();
            grid[e.x][e.y]=current_turn;
            printf("O puts his mark on [%d][%d]\n",e.x,e.y);
            while(!pq_O.empty()) pq_O.pop();
            print_grid();
            if(winning_condition(2,1)==true)
            {
                printf("O won the game.\n");
                break;
            }
        }
        prev_turn=current_turn;
    }



}
