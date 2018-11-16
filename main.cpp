#include "yinsh.h"

int player_num,rings_num,markers_num;
float time_left;
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
	stringstream ss(dup);
    // cerr<<"Move received : "<<dup<<endl;
	while(ss>>word)
	{
		mov_ty = word;

        // cerr <<word<<" "; 
		ss>>word;
		x1 = stoi(word);
        // cerr<<x1<<" ";
		ss>>word;
		y1=stoi(word);
        // cerr << y1<<" ";
		// Place p = {0,0};
		Place p = ring_to_xy(x1,y1);

		Move mv = {mov_ty,p.x,p.y};
        // cerr<<"Move received : "<<mov_ty<<" "<< p.x<<" "<< p.y<<endl;

		in_moves.push_back(mv);
	} 
    // cerr<<endl;

}


// void eval_neigh(Place dup_sel,vector<Place>& neighb,int id,vector<Place>& neighbour_new){
 
//             vector< vector<int> > original_board = game.myboard ;
//             vector< vector<Place> > original_player_rings = game.player;
 
//   map <float, int> m1 ;


//   vector<float > p_nei; 
  

//   for(int i_1=0;i_1<neighb.size();i_1++){
//      game.select_movering(dup_sel,neighb[i_1],id);

//      m1[game.evaluate_reward(id)] = i_1;
//      p_nei.push_back(game.evaluate_reward(id));

//      game.myboard = original_board;
//      game.player = original_player_rings;
     

//   }
//    sort(p_nei.begin(), p_nei.end());
//    // cerr<<"sorted"<< dup_sel.x<<" "<< dup_sel.y <<endl;
   
//    for(int i_1=0;i_1<p_nei.size();i_1++){
//      // game.select_movering(dup_sel,neighb[i_1],id);
//     neighbour_new.push_back (neighb[m1[p_nei[i_1]]]);

     

//   }

    


// }


float minimax(int depth,float alpha , float beta , bool isMax_player){

	if(depth==0){
       game.evaluate_reward(player_num);
	}

	else{


			
		if(isMax_player){



			float best_child = INT_MIN;

			// our player num will be maximising so turn = id = player_num
			vector<Place> dup_ringlist ;
			vector<Place> neighb;
            vector<Place> neighb_new;
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

                 // if(!game.totcheck_surr(dup_sel,player_num)){
                 //    continue;
                 // }

				neighb.resize(0);
				game.totneighbours(dup_sel,neighb);

				// neighb_new.resize(0);
    //             game.totneighbours(dup_sel,neighb_new); 
                

    //             neighb.resize(0);
    //             eval_neigh(dup_sel,neighb_new,player_num,neighb);

               
                for(int i_2=neighb.size()-1;i_2>=0;i_2--)

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

                        int max_diff=0;
                        int ind_s =0;
                        int diff1 =0;

                        for(int ii =0;ii<rings_num;ii++){

                            diff1 =0;
                         if(game.player[player_num][ii].x !=-10){
            // diff1 = diff1+ totcheck_linering(player[id][i],id);
                              // diff1 = diff1+ game.totcheck_linering(game.player[player_num][ii],0);

                              // diff1 = diff1+ game.totcheck_linering(game.player[player_num][ii],1);
                              diff1 = diff1+ game.totcheck_linering(game.player[player_num][ii],2);
                              diff1 = diff1+ game.totcheck_linering(game.player[player_num][ii],3);

                            if(max_diff<=diff1){
                            max_diff = diff1;
                            ind_s = ii;
                            }

                        }


                       }

                        game.remove_ring(game.player[player_num][ind_s],player_num);

                		// game.remove_ring(dup_ringlist[i_1],player_num);

                	}
                   // game.check_five 

                	float child = minimax(depth-1,alpha,beta,!isMax_player);
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

			float best_child = INT_MAX;
            int turn;
			vector<Place> dup_ringlist ;
			vector<Place> neighb;
            vector<Place> neighb_new;
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

                 // if(!game.totcheck_surr(dup_sel,turn)){
                 //    continue;
                 // }
				neighb.resize(0);
				game.totneighbours(dup_sel,neighb);

				// neighb_new.resize(0);
    //             game.totneighbours(dup_sel,neighb_new); 
                

    //             neighb.resize(0);
    //             eval_neigh(dup_sel,neighb_new,turn,neighb);

                
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

                		game.remove_row(rs,re,turn);

                    int max_diff=0;
                                            int ind_s =0;
                                            int diff1 =0;
                        for(int ii =0;ii<rings_num;ii++){

                            diff1 =0;
                         if(game.player[turn][ii].x !=-10){
            // diff1 = diff1+ totcheck_linering(player[id][i],id);
                              // diff1 = diff1+ game.totcheck_linering(game.player[turn][ii],0);

                              // diff1 = diff1+ game.totcheck_linering(game.player[turn][ii],1);
                               diff1 = diff1+ game.totcheck_linering(game.player[turn][ii],2);
                                diff1 = diff1+ game.totcheck_linering(game.player[turn][ii],3);

                            if(max_diff<=diff1){
                            max_diff = diff1;
                            ind_s = ii;
                            }

                        }


                       }
                     game.remove_ring(game.player[turn][ind_s],turn);

                		// game.remove_ring(dup_ringlist[i_1],turn);

                	}
                   // game.check_five 

                	float child = minimax(depth-1,alpha,beta,isMax_player);
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
    int depth =3;

    if(time_left<40){
        depth = 2;
    }
    else if(time_left<10){
        depth = 1;

    }
   
    // cerr<< "find_move" << game.evaluate_reward(id)<<endl;

    //  if(game.evaluate_reward(id)<.1){
    //     depth=1;
    // }

    // if(game.evaluate_reward(id)<1){
    //     depth=2;
    // }
    // else{
    //     depth=3;
    // }
	

	bool isMax_player = true;

// copied from below miniax maximising player
          
			vector<Place> dup_ringlist ;
			vector<Place> neighb;
            vector<Place> neighb_new;
			for(int i_1=0;i_1<rings_num;i_1++){
				if(game.player[id][i_1].x==-10){
					continue;
				}
				else{
					Place p1_1={game.player[id][i_1].x,game.player[id][i_1].y};
					dup_ringlist.push_back(p1_1);
				}
			}
            // cerr<< "find move id "<< id<< endl;
           // original board before sel move child

			vector< vector<int> > original_board = game.myboard ;
			vector< vector<Place> > original_player_rings = game.player;

            float best_child = INT_MIN;


			for(int i_1=0;i_1<dup_ringlist.size();i_1++)
			{
				Place dup_sel = dup_ringlist[i_1];

                // if(!game.totcheck_surr(dup_sel,id)){
                //     continue;
                //  }

				// neighb.resize(0);
				// game.totneighbours(dup_sel,neighb); 
                

                neighb_new.resize(0);
                // eval_neigh(dup_sel,neighb,id,neighb_new);
                game.totneighbours(dup_sel,neighb_new);
  if(time_left>80){              
  if(neighb_new.size()<5){
   depth = 4;
   }
   else{

    depth =3;
   }}
   else{
    depth=3;
   }
  // cerr<< "neighb "<<neighb_new.size()<<endl;
                for(int i_2=neighb_new.size()-1;i_2>=0;i_2--)

                {
                	float alpha = INT_MIN;
					float beta = INT_MAX;
                	
                    float g1 = game.evaluate_reward(id);

                	game.select_movering(dup_sel,neighb_new[i_2],id);

                    float g2 = game.evaluate_reward(id);
// 
                    float di_f = abs (g1-g2);
                    if(di_f<10){

                       depth=2;
                    }
                    // else if(di_f<10){
                    //     depth=3;
                    // }

                	vector< vector<Place>> five_rows;
                    


                	if(player_num==1){
                		game.check_five(-1,five_rows);
                	}
                	else{
                	 	game.check_five(1,five_rows);

                	}

// removing dup ring lists first elemt for randomness can be improved also directly taking first five row formed  
                    int ch=0;
                	if(five_rows.size()!=0){
                        // cerr<< "entered 5 row:"<< five_rows[0][0].x<< " "<<five_rows[0][0].y<<endl;
                		//vector<Place> rs_re = five_rows[0];
                		Place rs = five_rows[0][0];
                		Place re = five_rows[0][1];

                		game.remove_row(rs,re,id);
                        // bool b_t = true;
                        //  ch=0;
                        // while( ch<rings_num){
                        //     if(game.player[player_num][ch].x!=-10 && game.player[player_num][ch].y!=-10 && (game.player[player_num][ch].x != dup_sel.x || game.player[player_num][ch].y != dup_sel.y  ) ){
                        //         cerr<<"entered "<<game.player[player_num][ch].x<<" "<<game.player[player_num][ch].y<< endl;
                        //         game.remove_ring(game.player[player_num][ch],player_num);
                        //         break;
                        //     }
                        //     else{
                        //         ch++;
                        //     }
                        // }
                        int diff1 =0;
                        int ind_s=0;
                        int v_send =0;
                        // if(id==0){
                        //     v_send=;

                        // }
                        // else{
                        //     v_send = 
                        // }
                        int max_diff=0;
                        for(int ii =0;ii<rings_num;ii++){

                            diff1 =0;
                         if(game.player[id][ii].x !=-10){
            // diff1 = diff1+ totcheck_linering(player[id][i],id);
                              // diff1 = diff1+ game.totcheck_linering(game.player[id][ii],0);

                              // diff1 = diff1+ game.totcheck_linering(game.player[id][ii],1);
                                diff1 = diff1+ game.totcheck_linering(game.player[id][ii],2);
                                diff1 = diff1+ game.totcheck_linering(game.player[id][ii],3);

                            if(max_diff>=diff1){
                            max_diff = diff1;
                            ind_s = ii;
                            }

                        }


                       }
                        game.remove_ring(game.player[id][ind_s],id);

                		

                	}
                   // game.check_five 

                	float child = minimax(depth-1,alpha,beta,!isMax_player);
                    // cerr<<"inside"<< child<< " "<<best_child<<endl;  
                	if(best_child<=child){

                		best_moves.resize(0);
                		best_moves.push_back({"S",dup_sel.x,dup_sel.y});
                		best_moves.push_back({"M",neighb_new[i_2].x,neighb_new[i_2].y});
                		if(five_rows.size()!=0){
                			best_moves.push_back({"RS",five_rows[0][0].x,five_rows[0][0].y});
                		    best_moves.push_back({"RE",five_rows[0][1].x,five_rows[0][1].y});
                		    best_moves.push_back({"X",neighb_new[i_2].x,neighb_new[i_2].y});

                		}


                	best_child = child;
                		
                	}

                	game.myboard = original_board;
                	game.player = original_player_rings;
                    if(best_moves.size()==5){
                        break;
                    }
                	
                }

			}

}

void print_rings(){

    for(int i=0;i<rings_num;i++){
        Place p1 = xy_to_ring(game.player[0][i].x,game.player[0][i].y);
        Place p2 = xy_to_ring(game.player[1][i].x,game.player[1][i].y);

        // cerr<< " 1st "<< p1.x << " "<<p1.y << "2nd "<<p2.x <<" "<<p2.y <<endl;
    }
}


// int num_ring_presently(int id){

//   int ans;
//   for(int i=0;i<rings_num;i++){
//      if(game.player[id][i].x !=-10 ){
//       ans++;
//      }
//   }

//   return ans;

 

// }



void play(int id) 
{
    int turn=0;
    vector<Move> playermoves,oppmoves;
    if(id==1){
        // cerr<<"Player 2 em"<<endl;
    	input_moves(oppmoves);

    	game.execute_seq(oppmoves,turn);


    	turn = turn ^ 1;
    }
    // cerr<< "starting"<<endl;
    // print_rings();
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

        // cerr<< " my playerring rings"<< num_rings_placed << " board: "<< game.myboard[rec_ring_pos.x][rec_ring_pos.y]<< " ring_p  "<< ring_p <<" pos_p "<<pos_p<<endl;

       	cout<< "P "<< ring_p <<" "<< pos_p <<endl;
    	turn = turn ^1;

    	oppmoves.resize(0);
    	input_moves(oppmoves);
        // cerr<< " other player : "<<oppmoves[0].type<<"  "<< oppmoves[0].x <<" "<<oppmoves[0].y<<endl;
    	game.execute_seq(oppmoves,turn);
    	turn = turn^1;

    	num_rings_placed++;

         // cerr<< "after rings placed"<<endl;
         // print_rings();
// 
    }

    
   

    while(true){



            vector<Place> dup_ringlist ;
            // cerr<< "frst"<< turn<< endl;
            for(int i_1=0;i_1<rings_num;i_1++){
                if(game.player[turn][i_1].x==-10){
                    continue;
                }
                else{
                    Place p1_1={game.player[turn][i_1].x,game.player[turn][i_1].y};
                    dup_ringlist.push_back(p1_1);
                }
            }
    	
   

       bool b_w=true;
        while(b_w){

        playermoves.resize(0);
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
            Place xrem ;

            game.remove_row(rs,re,turn);

                        int ch=0;
                        while( ch<rings_num){
                            if(game.player[turn][ch].x!=-10 && game.player[turn][ch].y!=-10 ){
                                     // cerr<<"entered find"<<game.player[player_num][ch].x<<" "<<game.player[player_num][ch].y<< endl;
                                xrem =  game.player[turn][ch];
                                game.remove_ring(game.player[turn][ch],turn);
                                break;
                            }
                            else{
                                ch++;
                            }
                        }

                                                                    // game.remove_ring(neighb[i_2],player_num);

            // game.remove_ring(dup_ringlist[0],player_num);

            // playermoves.push_back({"RS",five_rows[0][0].x,five_rows[0][0].y});

            Place hex_coord ;
            hex_coord = xy_to_ring(five_rows[0][0].x,five_rows[0][0].y);
            cout<< "RS" << " "<< hex_coord.x << " "<< hex_coord.y<<" ";
            hex_coord = xy_to_ring(five_rows[0][1].x,five_rows[0][1].y);
            cout<< "RE" << " "<< hex_coord.x << " "<< hex_coord.y<< " " ;
            hex_coord = xy_to_ring(xrem.x,xrem.y);
            cout<< "X" << " "<< hex_coord.x << " "<< hex_coord.y<<" ";

            // playermoves.push_back({"RE",five_rows[0][1].x,five_rows[0][1].y});
            // playermoves.push_back({"X",dup_ringlist[0].x,dup_ringlist[0].y});
           


         }
         else{
            b_w = false;
         }

     }

         // vector<Move> tot_moves = playermoves;
        // cerr<< "befor find"<<endl;
        // print_rings();
         playermoves.resize(0);
         clock_t startTime=clock();
    	 find_moves(playermoves,turn);

         clock_t endTime = clock();
         clock_t clockTicksTaken = endTime - startTime;
         float timeInSeconds = clockTicksTaken / (float) CLOCKS_PER_SEC;
         time_left = time_left - (int) timeInSeconds;
           // cerr<< "after find"<< playermoves.size()<<endl;
         // print_rings();
         
        // cerr<< "finded move "<< playermoves.size()<<"ring _s "<< rings_num << " "<< num_ring_presently(turn) <<"  "<<(rings_num - game.num_ring_present(turn) )  <<endl;
    	// sending our move 
  

    	for(int i1=0; i1<playermoves.size() && (rings_num - game.num_ring_present(turn) < 3 ) ;i1++){
    		string s1 = playermoves[i1].type;
    		int id1 = playermoves[i1].x;
    		int id2 = playermoves[i1].y;

            if(s1=="S"){
                vector<Move> m11;
                // cerr<< "sel_mov "<< playermoves[i1].x<<" "<< playermoves[i1].y<<endl;
                m11.push_back(playermoves[i1]);
                m11.push_back(playermoves[i1+1]);
                game.execute_seq(m11,turn);
            }
            if(s1=="RS"){
                vector<Move> m11;
                m11.push_back(playermoves[i1]);
                m11.push_back(playermoves[i1+1]);
                game.execute_seq(m11,turn);   
            }
            if(s1=="X"){
                 vector<Move> m11;
                 m11.push_back(playermoves[i1]);
                  // cerr<< "befr rem"<<endl;
                  // print_rings();
                 game.execute_seq(m11,turn); 
                 // cerr<< "after rem"<<endl;
                  // print_rings();

            }
           
            
    		Place hex_coord = xy_to_ring(id1,id2);
    		cout<< s1 << " "<< hex_coord.x << " "<< hex_coord.y;
            if(i1<playermoves.size()-1){
                cout<<" ";
            }
    	}

        // cerr<< "our turn completed"<<endl;
        // print_rings();
    	cout<<endl;
    	oppmoves.resize(0);
    	turn=turn^1;
    	input_moves(oppmoves);
    	game.execute_seq(oppmoves,turn);
        // cerr<< "opp execute_seq "<< game.myboard[oppmoves[0].x][oppmoves[0].y] << " "<< oppmoves[0].x<<" "<< oppmoves[0].y<<endl;  
    	turn = turn^1;

                // cerr<< "his turn completed"<<endl;
                //  print_rings(); 

    }    
    
}


int main(){
	
	string ind,rings,time,mark;

	cin>>ind >> rings >> time ;
	// player num 0 or 1
	player_num = stoi(ind) -1;
	rings_num = stoi(rings);
	time_left = stoi(time);
    cin>>mark;
	markers_num = stoi(mark);

    // cerr<< " markers "<< markers_num<<endl;
	game = Yinsh(rings_num,2*rings_num+1,markers_num);
    



     
    play(player_num);
	
	





	
}