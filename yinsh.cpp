#include "yinsh.h"


// Yinsh::Yinsh(){}

void initialize()
{
	int rings_n = ring_size;
	int x,y,low,high,j ;
	for(int i = 0 ; i < rows ; i++)
	{
        x = i - rings_n ;
        low = - rings_n ;
        high = rings_n ;

        if( x == 0){
          low = -(rings_n - 1) ;
          high= (rings_n - 1) ;
        }
        else if( x >= 1 && x <= rings_n-1){
          low = -rings_n + x ;
        }
        else if(x == rings_n){
          low = 1 ;
          high = rings_n - 1 ;
        }
        else if(x >= -(rings_n - 1) && x <= -1){
          high = rings_n + x ;
        }
        else if(x ==-(rings_n)){
          low = -(rings_n - 1) ; 
          high = -1;
        }
        for(j = 0 ; j < rows ; j++){
           y = j - (rings_n) ;
          if( !(y >= low && y <= high)){
            myboard[i][j] = -10 ;
          }
        }
    }
    
}

void place_ring(int x,int y,int id)
{

    
}
void select_movering(Place sel,Place mov,int id)
{

}
void remove_row(Place p1,Place p2,int id)
{
  
}
void remove_ring(Place p1,int id)
{

}
void execute_seq(vector<Move>& move,int id)
{
     
}

void neighbours(Place sel,Place dir,vector<Place>& neighbour)
{

}
void totneighbours(PLace sel,vector<Place>& neighbour)
{

}

