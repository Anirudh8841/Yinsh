#include "yinsh.h"


Yinsh::Yinsh(){};


//  
Yinsh::Yinsh(int rings,int row,int mark){
            ring_size = rings;
            rows = row;
            marker_rem = mark;
            // matrix.resize(3, vector<int> (5,-1));
            myboard.resize(rows, vector<int> (rows,0));
   			player.resize(2, vector<Place> (ring_size,0));

            initialize();  

		};
void Yinsh::initialize()
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

void Yinsh::place_ring(int x,int y,int id)
{
	 Place p = Place(x,y);

     if(id==0){
     	myboard[x][y] = 2 ;
     }
     else{
     	myboard[x][y] = -2;
     }

// updating ring positions
     player[id][cnt]=p;
     cnt++;

}

// reverse in between and place ring at final position 
// not checked validity

void Yinsh::select_movering(Place sel,Place mov,int id)
{

    myboard[mov.x][mov.y] = myboard[sel.x][sel.y];

    // updating ring positions
    for(int i2=0;i2<ring_size;i2++){
    	if(player[id][i2].x == sel.x ){
    		if(player[id][i2].y == sel.y ){
    			player[id][i2].x = mov.x;
    			player[id][i2].y = mov.y;
    		}
    	}
    }
    
	myboard[sel.x][sel.y] = myboard[sel.x][sel.y]/2;
	//  vertically moment
    if(sel.x == mov.x){
   		if(sel.y < mov.y){
   			for(int i1=sel.y+1 ; i1 < mov.y ; i1++){
   				myboard[sel.x][i1] = -myboard[sel.x][i1];
   			}
   		}
   		else if(sel.y > mov.y){
   			for(int i1=mov.y+1 ; i1 < sel.y ; i1++){
   				myboard[sel.x][i1] = -myboard[sel.x][i1];
   			}
   		}

    }
    // horizontal moment
    else if(sel.y == mov.y){
   		if(sel.x < mov.x){
   			for(int i1=sel.x+1 ; i1 < mov.x ; i1++){
   				myboard[i1][sel.y] = -myboard[i1][sel.y];
   			}
   		}
   		else if(sel.x > mov.x){
   		for(int i1=mov.x+1 ; i1 < sel.x ; i1++){
   			myboard[i1][sel.y] = -myboard[i1][sel.y];
   		}
  	 	}

    }
   // horizontal and vertical 
   else {
 		if(mov.x>sel.x){
 			if(mov.y>sel.y){
 				for(int j1=sel.y+1,i1 = sel.x+1; i1 < mov.x && j1<mov.y;i1++ ,j1++){
 					myboard[i1][j1] = -myboard[i1][j1];
 				}
 			}
 			else{
 				for(int j1=mov.y+1,i1 = sel.x+1; i1 < mov.x && j1<sel.y;i1++ ,j1++){
 					myboard[i1][j1] = -myboard[i1][j1];
 				}
 			}
 		}
 		else{
 			if(mov.y>sel.y){
 				for(int j1=sel.y+1,i1 = mov.x+1; i1 < sel.x && j1<mov.y;i1++ ,j1++){
 					myboard[i1][j1] = -myboard[i1][j1];
 				}
 			}
 			else{
 				for(int j1=mov.y+1,i1 = mov.x+1; i1 < sel.x && j1<sel.y;i1++ ,j1++){
 					myboard[i1][j1] = -myboard[i1][j1];
 				}
 			}

 		}

   		}
	}


void Yinsh::remove_row(Place p1,Place p2,int id)
{
 
    
    myboard[p1.x][p1.y] = 0;
    myboard[p2.x][p2.y] = 0;
   if(p1.x == p2.x){
   		if(p1.y < p2.y){
   			for(int i1=p1.y+1 ; i1 < p2.y ; i1++){
   				myboard[p1.x][i1] = 0;
   			}
   		}
   		else if(p1.y > p2.y){
   			for(int i1=p2.y+1 ; i1 < p1.y ; i1++){
   				myboard[p1.x][i1] = 0;
   			}
   		}

    }
    // horizontal moment
    else if(p1.y == p2.y){
   		if(p1.x < p2.x){
   			for(int i1=p1.x+1 ; i1 < p2.x ; i1++){
   				myboard[i1][p1.y] =0;
   			}
   		}
   		else if(p1.x > p2.x){
   		for(int i1 = p2.x+1 ; i1 < p1.x ; i1++){
   			myboard[i1][p1.y] = 0;
   		}
  	 	}

    }
   // horizontal and vertical 
   else {
 		if(p2.x>p1.x){
 			if(p2.y>p1.y){
 				for(int j1=p1.y+1,i1 = p1.x+1; i1 < p2.x && j1<p2.y;i1++ ,j1++){
 					myboard[i1][j1] = 0;
 				}
 			}
 			else{
 				for(int j1=p2.y+1,i1 = p1.x+1; i1 < p2.x && j1<p1.y;i1++ ,j1++){
 					myboard[i1][j1] = 0;
 				}
 			}
 		}
 		else{
 			if(p2.y>p1.y){
 				for(int j1=p1.y+1,i1 = p2.x+1; i1 < p1.x && j1<p2.y;i1++ ,j1++){
 					myboard[i1][j1] = 0;
 				}
 			}
 			else{
 				for(int j1=p2.y+1, i1 = p2.x+1; i1 < p1.x && j1< p1.y;i1++ ,j1++){
 					myboard[i1][j1] = 0;
 				}
 			}

 		}

   }
}

void Yinsh::remove_ring(Place p1,int id)
{
	myboard[p1.x][p1.y] = 0;


// updating ring positions
	for(int i2=0;i2<ring_size;i2++){
    	if(player[id][i2].x == p1.x ){
    		if(player[id][i2].y == p1.y ){
    			player[id][i2].x = -10;
    			player[id][i2].y = -10;
    		}
    	}
    }



}
void Yinsh::execute_seq(vector<Move>& move,int id)
{
     
}

void Yinsh::neighbours(Place sel,Place dir,vector<Place>& neighbour)
{


}
void Yinsh::totneighbours(Place sel,vector<Place>& neighbour)
{

}
double Yinsh::evaluate_reward(int id)
{

}


 vector<int> Yinsh::eval_collinear(int id){


	// for x y var
   
	vector<int> player1 (ring_size+1,0);
	player1.push_back(0);
	int count_1=0;

	// for x y var
	for(int x_i=0;x_i<rows;x_i++){
        player1[count_1] = player1[count_1]+1;
	    count_1=0;
		for(int y_i =0;y_i<rows;y_i++){
			if(myboard[x_i][y_i]==-10){

			}
			else{
				if(myboard[x_i][y_i] ==id){
					count_1++;
				}
				else if(myboard[x_i][y_i] !=id){
                    player1[count_1] = player1[count_1]+1;
					count_1=0;
					
				}
			}
				
		}
	}

	// y con x var

	count_1 =0;
	for(int y_i=0;y_i<rows;y_i++){	
        player1[count_1] = player1[count_1]+1;
	    count_1=0;
		for(int x_i =0;x_i<rows;x_i++){
			if(myboard[x_i][y_i]==-10){
			}
			else{
				if(myboard[x_i][y_i] ==id){
					count_1++;
										
				}
				else if(myboard[x_i][y_i] !=id){	
                    player1[count_1] = player1[count_1]+1;
					count_1=0;
				}
			}
				
		}
	}

	// x y both increase

	//  horiz
	count_1 =0;
	for(int x_i=0;x_i<=(rows-1)/2;x_i++){	
        player1[count_1] = player1[count_1]+1;
	    count_1=0;
	    int x_dup=x_i;
		for(int y_i =0;y_i<rows && x_dup<rows ;y_i++,x_dup++){
			if(myboard[x_dup][y_i]==-10){
			}
			else{
				if(myboard[x_dup][y_i] ==id){
					count_1++;
										
				}
				else if(myboard[x_dup][y_i] !=id){	
                    player1[count_1] = player1[count_1]+1;
					count_1=0;
				} 
			}
				
		}
	}
	count_1 =0;
	for(int y_i=1;y_i<=(rows-1)/2;y_i++){	
        player1[count_1] = player1[count_1]+1;
	    count_1=0;
	    int y_dup=y_i;
		for(int x_i =0;x_i<rows && y_dup<rows ;x_i++,y_dup++){
			if(myboard[x_i][y_dup]==-10){
			}
			else{
				if(myboard[x_i][y_dup] ==id){
					count_1++;
										
				}
				else if(myboard[x_i][y_dup] !=id){	
                    player1[count_1] = player1[count_1]+1;
					count_1=0;
				} 
			}
				
		}
	}





	return player1;
	// for(int i =0;i<player1.size();i++){

	// 		cout<<" i "<<i <<"  " <<player1[i]<< endl;

	// }

	
}