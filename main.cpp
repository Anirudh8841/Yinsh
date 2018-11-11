#include "yinsh.h"

int player_num,rings_num,markers_num;
float timelimit;
Yinsh game;

Place ring_to_xy(int hex,int pos)
{
	Place ans ={0,0};
	if(hex==0 && pos==0){
		ans.x = 0;
		ans.y = 0;
	}
	else if(pos<hex){
		ans.x=hex;
		ans.y=pos;
	}
	else if(pos<2*hex){
		ans.x=2*hex - pos;
		ans.y=hex;
	}
	else if(pos<3*hex){
		ans.x=2*hex -pos;
		ans.y=3*hex-pos;
	}
	else if(pos<4*hex){
		ans.x=-hex;
		ans.y=3*hex-pos;
	}
	else if(pos<5*hex){
		ans.x=pos-5*hex;
		ans.y=-hex;
	}
	else {
		ans.x=pos-5*hex;
		ans.y=pos-6*hex;
	}
	ans.x=ans.x+rings_num;
	ans.y=ans.y+rings_num;

return ans;
}

Place xy_to_ring(int x,int y)
{
 	Place ans ={0,0};
 	x=x- rings_num ;
 	y=y- rings_num ;

 	if(x==0 && y==0){
 		ans.x=0;
 		ans.y=0;
 	}
 	else if(x>=y)
 	{
 		if(x>=0 && y>=0){
 			ans.x=x;
 			ans.y=y;
 		}
 		else if(x<=0 && y<=0)
 		{
 			ans.x = -y;
 			ans.y = x-(5*y);

 		}
 		else if(x>=0 && y<=0)
 		{
 			ans.x=x-y;
 			ans.y = 6*x - 5*y;
 		}
 	}
 	else if (y>x)
 	{
 		if(x>=0 && y>=0)
 		{
 			ans.x=y;
 			ans.y = 2*y-x;

 		}
 		else if(x<=0 && y<=0)
 		{
 			ans.x=-1*x;
 			ans.y = (-3*x)-y;

 		}
 		else if(x<=0 && y>=0)
 		{
 			ans.x = y-x;
 			ans.y = 2*y - 3*x;
 		}
 	}
 	return ans;
}

void input_moves(vector<Move> &in_moves)
{
	string mov_ty;
	int x1,y1;
	string word;
	string dup;
	getline(cin,dup);
	while(dup.length()==0){
		getline(cin,dup);
	}
	istringstream ss(dup);
	while(ss>>word)
	{
		mov_ty = word;
		ss>>word;
		x1 = stoi(word);
		ss>>word;
		y1=stoi(word);
		// Place p = {0,0};
		Place p = ring_to_xy(x1,y1);

		Move mv = {mov_ty,p.x,p.y};

		in_moves.push_back(mv);


	} 

}


double minimax(int depth,double alpha , double beta , bool isMax_player){

	if(depth==0){
       game.evaluate_reward(player_num);
	}

	else{
			
		if(isMax_player){

			double best_child = INT_MIN;

			// our player num will be maximising so turn = id = player_num
			vector<Place> dup_ringlist ;
			vector<Place> neighb;
			for(int i_1=0;i_1<rings_num;i_1++){
				if(game.player[player_num][i_1].x==-10){
					continue;
				}
				else{
					Place p1_1={game.player[player_num][i_1].x,game.player[player_num][i_1].y};
					dup_ringlist.push_back(p1_1);
				}
			}
           // original board before sel move child

			vector< vector<int> > inter_board = game.myboard ;
			vector< vector<Place> > inter_player_rings = game.player;

			for(int i_1=0;i_1<dup_ringlist.size();i_1++)
			{
				Place dup_sel = dup_ringlist[i_1];
				neighb.resize(0);
				game.totneighbours(dup_sel,neighb);

				
                
                for(int i_2=0;i_2<neighb.size();i_2++)

                {
                	

                	game.select_movering(dup_sel,neighb[i_2],player_num);

                	vector< vector<Place>> five_rows;


                	if(player_num==1){
                		game.check_five(-1,five_rows);
                	}
                	else{
                	 	game.check_five(1,five_rows);

                	}

                	if(five_rows.size()!=0){
                		//vector<Place> rs_re = five_rows[0];
                		Place rs = five_rows[0][0];
                		Place re = five_rows[0][1];

                		game.remove_row(rs,re,player_num);
                		game.remove_ring(dup_ringlist[0],player_num);

                	}
                   // game.check_five 

                	double child = minimax(depth-1,alpha,beta,!isMax_player);
                	best_child = max(best_child,child);
                	alpha = max(alpha,child);
                	if(alpha>=beta){
                		return best_child;
                	}

                	game.myboard = inter_board;
                	game.player = inter_player_rings;
                }




			}
            
			return best_child;

		}
		else if(!isMax_player){

			double best_child = INT_MAX;
            int turn;
			vector<Place> dup_ringlist ;
			vector<Place> neighb;
			if(player_num ==1){
				turn =0;
			}
			else{
				turn =1;
			}
			for(int i_1=0;i_1<rings_num;i_1++){
				if(game.player[turn][i_1].x==-10){
					continue;
				}
				else{
					Place p1_1 = {game.player[turn][i_1].x,game.player[turn][i_1].y};
					dup_ringlist.push_back(p1_1);
				}
			}
           // original board before sel move child

			vector< vector<int> > inter_board = game.myboard ;
			vector< vector<Place> > inter_player_rings = game.player;

			for(int i_1=0;i_1<dup_ringlist.size();i_1++)
			{
				Place dup_sel = dup_ringlist[i_1];
				neighb.resize(0);
				game.totneighbours(dup_sel,neighb);

				
                
                for(int i_2=0;i_2<neighb.size();i_2++)

                {


                	game.select_movering(dup_sel,neighb[i_2],turn);


                	vector< vector<Place>> five_rows;


                	if(turn==1){
                		game.check_five(-1,five_rows);
                	}
                	else{
                	 	game.check_five(1,five_rows);

                	}

                	if(five_rows.size()!=0){
                		//vector<Place> rs_re = five_rows[0];
                		Place rs = five_rows[0][0];
                		Place re = five_rows[0][1];

                		game.remove_row(rs,re,player_num);
                		game.remove_ring(dup_ringlist[0],turn);

                	}
                   // game.check_five 

                	double child = minimax(depth-1,alpha,beta,isMax_player);
                	best_child = min(child,best_child);
                	beta = min(beta,child);
                	if(alpha>=beta){
                		return best_child;
                	}

                	game.myboard = inter_board;
                	game.player = inter_player_rings;
                }
			}


			return best_child;
			
		}
	}

}


// explore neighbours and find path 
void find_moves(vector<Move> &best_moves,int id)
{

	int depth = 5;
	bool isMax_player = true;

// copied from below miniax maximising player

			vector<Place> dup_ringlist ;
			vector<Place> neighb;
			for(int i_1=0;i_1<rings_num;i_1++){
				if(game.player[player_num][i_1].x==-10){
					continue;
				}
				else{
					Place p1_1={game.player[player_num][i_1].x,game.player[player_num][i_1].y};
					dup_ringlist.push_back(p1_1);
				}
			}
           // original board before sel move child

			vector< vector<int> > original_board = game.myboard ;
			vector< vector<Place> > original_player_rings = game.player;

			for(int i_1=0;i_1<dup_ringlist.size();i_1++)
			{
				Place dup_sel = dup_ringlist[i_1];
				neighb.resize(0);
				game.totneighbours(dup_sel,neighb);       
                for(int i_2=0;i_2<neighb.size();i_2++)

                {
                	double alpha = INT_MIN;
					double beta = INT_MAX;
					double best_child = INT_MIN;
                	

                	game.select_movering(dup_sel,neighb[i_2],player_num);

                	vector< vector<Place>> five_rows;


                	if(player_num==1){
                		game.check_five(-1,five_rows);
                	}
                	else{
                	 	game.check_five(1,five_rows);

                	}

// removing dup ring lists first elemt for randomness can be improved also directly taking first five row formed  

                	if(five_rows.size()!=0){
                		//vector<Place> rs_re = five_rows[0];
                		Place rs = five_rows[0][0];
                		Place re = five_rows[0][1];

                		game.remove_row(rs,re,player_num);
                		game.remove_ring(dup_ringlist[0],player_num);

                	}
                   // game.check_five 

                	double child = minimax(depth-1,alpha,beta,!isMax_player);
                	if(best_child<child){

                		best_moves.resize(0);
                		best_moves.push_back({"S",dup_sel.x,dup_sel.y});
                		best_moves.push_back({"M",neighb[i_2].x,neighb[i_2].y});
                		if(five_rows.size()!=0){
                			best_moves.push_back({"RS",five_rows[0][0].x,five_rows[0][0].y});
                		    best_moves.push_back({"RE",five_rows[0][1].x,five_rows[0][1].y});
                		    best_moves.push_back({"X",dup_ringlist[0].x,dup_ringlist[0].y});

                		}


                		best_child = child;
                		
                	}

                	game.myboard = original_board;
                	game.player = original_player_rings;
                	
                }

			}

}



void play(int id)
{
    int turn=0;
    vector<Move> playermoves,oppmoves;
    if(id==1){
    	input_moves(oppmoves);
    	game.execute_seq(oppmoves,turn);
    	turn = turn ^ 1;
    }


    clock_t start_t = clock();
    int ring_p=0;
    int pos_p=0;
    Place rec_ring_pos={0,0};
    int num_rings_placed =0;
    while(num_rings_placed < rings_num ){
    	bool b = true;
    	while(b)
    	{
    		rec_ring_pos = ring_to_xy(ring_p,pos_p);
    		if(game.myboard[rec_ring_pos.x][rec_ring_pos.y]!=0)
    		{
    			pos_p++;
    			if(pos_p <= 6*ring_p-1){

    			}
    			else{
    				ring_p++;
    				pos_p=0;
    			}

    		}
    		else{
 				b=false;
    		}
           

    	}

    	game.place_ring(rec_ring_pos.x,rec_ring_pos.y,turn);

       	cout<< "P "<< ring_p<<" "<< pos_p <<endl;
    	turn = turn ^1;

    	oppmoves.resize(0);
    	input_moves(oppmoves);
    	game.execute_seq(oppmoves,turn);
    	turn = turn^1;

    	num_rings_placed++;
// 
    }
    clock_t end_t;
    end_t = clock_t();
    timelimit = timelimit -(end_t - start_t)/(double)CLOCKS_PER_SEC;
    start_t = end_t;

    while(true){
    	playermoves.resize(0);
    	find_moves(playermoves,turn);
    	// sending our move 
    	for(int i1=0;i1<playermoves.size();i1++){
    		string s1 = playermoves[i1].type;
    		int id1 = playermoves[i1].x;
    		int id2 = playermoves[i1].y;
    		Place hex_coord = xy_to_ring(id1,id2);
    		cout<< s1 << " "<< hex_coord.x << " "<< hex_coord.y << " ";
    	}
    	cout<<endl;
    	oppmoves.resize(0);
    	turn=turn^1;
    	input_moves(oppmoves);
    	game.execute_seq(oppmoves,turn);
    	turn = turn^1;

    }    
    
}


int main(){
	
	string ind,rings,time,mark;
	cin>>ind >> rings >> time>> mark ;
	// player num 0 or 1
	player_num = stoi(ind);
	rings_num = stoi(rings);
	timelimit = stoi(time);
	markers_num = stoi(mark);
  
	game = Yinsh(rings_num,2*rings_num+1,markers_num);
    

    // cout <<"a "<< ring_to_xy(0,0).x << " b "<< ring_to_xy(0,0).y << " 2a "<< ring_to_xy(1,0).x<< "2b"<<ring_to_xy(0,0).y <<endl;
    // game.play(player_num);
     
    play(player_num);
	
	





	
}