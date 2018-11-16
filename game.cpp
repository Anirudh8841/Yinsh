//0-nothing
//1- player 0 ring 
//-1 - player 1 ring
//2 - player 0 mark
//-2 - player 1 mark
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <utility>
#include "game.h"
using namespace std;

game::game(int n  , int m , int k , int l){
	p_turn = 0 ;
	N = n ; // N side
	M = m ; // number of rings
	K = k ; // K markers in a line
	L = l ; // to win
	mode = 0 ; // initially rings are to be placed
	vector<int> c0;
	vector<int> c1;

	vector<int> r0;
	vector<int> r1;
	rings.push_back(r0);
	rings.push_back(r1);
	for(int i = 0 ; i < 2*m + 1 ;i++){
		rings[0].push_back(0);
		rings[1].push_back(0);
	}


	box = (int**) malloc((2*N+1)*sizeof(int*));
	for(int i = 0 ; i < 2*N + 1;i++){
		box[i] = (int*) malloc((4*N+1)*sizeof(int));
		for(int i1 = 0 ; i1 < 4*N + 1 ;i1++){
			box[i][i1] = 0;
		}

	}
	
	coeff = (int**) malloc(2*sizeof(int*)); 
	coeff[0] = (int*) malloc(7*sizeof(int));
	coeff[1] = (int*) malloc(7*sizeof(int));
	//optimise for other values also
	coeff[0][0]=0;
	coeff[1][0]=0;
	coeff[0][1]=1;
	coeff[1][1]=1;
	coeff[0][2]=10;
	coeff[1][2]=10;
	coeff[0][3]=100;
	coeff[1][3]=100;
	coeff[0][4]=1000;
	coeff[1][4]=1000;
	coeff[0][5]=10000;
	coeff[1][5]=10000;
	coeff[0][6]=100000;
	coeff[1][6]=100000;
}

int game::get_x(int hex1 , int pos1){
	int x = 0 ;
	if( pos1 < hex1 ){
		x = pos1 ;
	}
	else if(pos1 < 2*hex1){
		x = hex1  ;
	}
	else if(pos1 < 3*hex1){
		x = 3*hex1 - pos1;
	}
	else if(pos1 < 4*hex1){
		x = 3*hex1 - pos1;
	}
	else if(pos1 < 5*hex1){
		x = -hex1;
	}
	else if(pos1 < 6*hex1){
		x = pos1 - 6*hex1;
	}
	x += N;
	return x ;
}
int game::get_y(int hex1 , int pos1){
	int y = 0;
	if( pos1 < hex1 ){
		y = 2*hex1 - pos1 ;
	}
	else if(pos1 < 2*hex1){
		y = 3*hex1 - 2*pos1 ;
	}
	else if(pos1 < 3*hex1){
		y = hex1 - pos1;
	}
	else if(pos1 < 4*hex1){
		y =  pos1 -  5*hex1 ;
	}
	else if(pos1 < 5*hex1){
		y = 2*pos1 - 9*hex1;
	}
	else if(pos1 < 6*hex1){
		y = pos1 - 4*hex1;
	}
	y += 2*N;
	return y;
}
int game::get_hex(int x , int y ){
	int hex = 0 ;
	x -= N;
	y -= 2*N;
	if(0 <= x && x <= y ){
		hex = (x + y )/2;
	}
	else if( -x <= y && y <= x  ){
		hex = x  ;
	}
	else if(x>= 0 && x+y <= 0){
		hex = (x-y)/2;
	}
	else if(x <= 0 && y-x <= 0){
		hex = -(x+y)/2     ;
	}
	else if(y-x >= 0 && y+x <= 0){
		hex = -x ;
	}
	else if(y+x >= 0 && x <= 0){
		hex = (-x+y)/2 ;
	}
	return hex;
}
int game::get_pos(int x, int y){
	int pos = 0 ;
	x -= N;
	y -= 2*N;
	if(0 <= x && x <= y ){
		pos = x;
	}
	else if( -x <= y && y <= x  ){
		pos = (3*x - y)/2 ;
	}
	else if(x>= 0 && x+y <= 0){
		pos = ( x - 3*y)/2;
	}
	else if(x <= 0 && y-x <= 0){
		pos = (-5*x - 3*y )/2 ; 				
	}
	else if(y-x >= 0 && y+x <= 0){
		pos = (-9*x + y)/2 ;
	}
	else if(y+x >= 0 && x <= 0){
		pos = (-2*x + 3*y );
	}
	return pos ;
}
int game::mton(string s){
	if(s == "P") return 1;
	else if(s == "X") return -1;
	else if(s == "S") return 2;
	else if(s == "M") return -2;
	else if(s == "f") return 10;
	else if(s == "RS") return 3;
	else if(s == "RE") return -3 ;

}

//decider = 0 -> delete;
//decider = 1 -> update;
void game::update_rings(int decider , int x1 , int y1 ,int x2 , int y2){
	int c ;
	c= rings[p_turn][0]  ;
	for(int i = 1 ; i <= c ;i++){  
		if(rings[p_turn][2*i - 1]== x1 && rings[p_turn][2*i] == y1){
			if(decider == 0){
				rings[p_turn][2*i- 1] = rings[p_turn][2*c - 1];
				rings[p_turn][2*i ] = rings[p_turn][2*c];
				rings[p_turn][0]--;
			}
			else if(decider == 1){
				rings[p_turn][2*i -1] = x2;
				rings[p_turn][2*i] = y2;
			}
			break;
		}
	}
}

//placing the rings
void game::execute_move(int label1 , int x1 , int y1){
	if(label1 == 1){//"P"
		box[x1][y1] = 1 - 2*p_turn;
		rings[p_turn][0]++;
		rings[p_turn][2*rings[p_turn][0] - 1] = x1;
		rings[p_turn][2*rings[p_turn][0]] = y1;
		if(rings[1][0] == M) mode = 1 ; 
	}
	else if(label1 == 2){//"S"
		xex1 = x1 ;
		yos1 = y1 ;
	}
	else if(label1 == -2 ){//"M"
		box[xex1][yos1] = 2 - 4*p_turn ;
		box[x1][y1] = 1 - 2*p_turn ;
		update_rings(1,xex1,yos1,x1,y1);

		int a = 1;
		int m = (x1 - xex1) / (y1 -yos1);
		if(yos1 > y1) a = -1;
		
		for(int i = 2 - m*m ; i < a*(y1 - yos1) ;i+= 2 - m*m){
			box[xex1 + a*m*i][yos1 + a*i ] = - box[xex1 + a*m*i][yos1 + a*i ];
		}
	}
	else if(label1 == 10 ){//"Mf"
		box[xex1][yos1] = 2 - 4*p_turn ;
		box[x1][y1] = 1 - 2*p_turn ;
		update_rings(1,xex1,yos1,x1,y1);	
	}
	else if(label1 == 3 ){//"RS"
		xex1 = x1 ;
		yos1 = y1 ;
	}
	else if(label1 == -3 ){//"RE"
		int a = 1 ;
		int m = (x1 - xex1) / (y1 -yos1);
		if(yos1 > y1) a = -1;
		
		for(int i = 0 ; i <= a*(y1 - yos1) ;i += 2 - m*m){
			box[xex1 + a*m*i][yos1 + a*i ] = 0;
		}
	}
	else if(label1 == -1){//"X"
		box[x1][y1] = 0 ;
		update_rings(0,x1,y1,0,0);
	}
}
void game::dexecute_move(int label1 , int x1 , int y1){//note the turn here;
	if(label1 == -2){//"M"
		xex1 = x1 ;
		yos1 = y1 ;
	}
	else if(label1 == 2){//"S"
		box[xex1][yos1] = 0 ;
		box[x1][y1] = 1 - 2*p_turn ; //note that it is p_turn here 
		update_rings(1,xex1,yos1,x1,y1);

		int a = 1;
		int m = (x1 - xex1) / (y1 -yos1);
		if(yos1 > y1) a = -1;
		for(int i = 2 - m*m ; i < a*(y1 - yos1) ;i+= 2 - m*m){
			box[xex1 + a*m*i][yos1 + a*i] = - box[xex1 + a*m*i][yos1 + a*i];
		}
	}
	else if(label1 == 10){//"Sf"
		box[xex1][yos1] = 0 ;
		box[x1][y1] = 1 - 2*p_turn ; //note that it is p_turn here 
		update_rings(1,xex1,yos1,x1,y1);
	}
	else if(label1 == -3 ){//"RE"
		xex1 = x1 ;
		yos1 = y1 ;
	}
	else if(label1 == 3){//"RS"
		int a = 1 ;
		
		int m = (x1 - xex1) / (y1 -yos1);
		if(yos1 > y1) a = -1;
		for(int i = 0 ; i <= a*(y1 - yos1) ;i += 2 - m*m){
			box[xex1 + a*m*i][yos1 + a*i] = 2 - 4*p_turn;
		}
		
	}
	else if(label1 == -1){//"X"
		box[x1][y1] = 1 - 2*p_turn;
		rings[p_turn][0]++;
		rings[p_turn][2*rings[p_turn][0] - 1] = x1;
		rings[p_turn][2*rings[p_turn][0]] = y1;
	}
}
void game::execute_seq(string S){
	vector<string> t;
	stringstream c1(S);
	string between;
	while(getline(c1,between,' ')){
		t.push_back(between);
	}
	int l = t.size()/3 ;
	for(int i = 0 ; i < l ;i++ ){
		int x_t = stoi(t[3*i +1]);
		int y_t = stoi(t[3*i +2]);
		execute_move(mton(t[3*i]),get_x(x_t,y_t),get_y(x_t,y_t));
	}
	p_turn = 1- p_turn ;
}
void game::dexecute_seq(string S){
	p_turn = 1- p_turn ;
	vector<string> t;
	stringstream c1(S);
	string between;
	while(getline(c1,between,' ')){
		t.push_back(between);
	}
	int l = t.size()/3 ;
	for(int i = l-1 ; i >= 0 ;i-- ){
		int x_t =  stoi(t[3*i +1]);
		int y_t =  stoi(t[3*i +2]);
		dexecute_move(mton(t[3*i]),get_x(x_t,y_t),get_y(x_t,y_t));
	}
}


bool game::valid(int hex1 , int pos1){
	int x1 = get_x(hex1,pos1);
	int y1 = get_y(hex1,pos1);
	if(co_poss(x1,y1)){
		if(box[x1][y1] == 0 ) {
			return true ;
		}	
	}
	return false ;
}

bool game::co_poss(int x , int y){
	x -= N;
	y -= 2*N;
	if(x+y + 2*N >= 0 && x + N >= 0 && x- y + 2*N >= 0 && x + y - 2*N <= 0 && x <= N && x- y - 2*N <= 0 ){
		if( (x == N || x == -N) && (y == N || y == -N) ) return false;
		else if(x == 0  && (y == 2*N || y == -2*N) ) return false;
		return true ; 
	}
	else return false ;
}


vector<string> game::determine_5(int x1 , int y1 , int x2 , int y2 ,int count){
	vector<string> ans ;
	vector<string> temp ;
	int m = (x2 - x1)/(y2 - y1);
	int x, y;
	int a = -1;
	if(y1 > y2) a = +1;
	for(int i = 2-m*m ; i <= -(y2 - y1)*a ; i += 2 - m*m){
		y = y2 + a*i;
		x = x2 + a*i*m;
		if(box[x][y] == 2 - 4*p_turn){
			for(int m_temp  = -1;m_temp <=1 ;m_temp++){
				if(m!= m_temp){
					int up_count = number_backrays(x,y,m_temp,1,0,1);
					int down_count = number_backrays(x,y,m_temp,-1,0,1);
					if(up_count+down_count + 1 >= K){
						int x_c = (2-m_temp*m_temp)*m_temp ;
						int y_c = (2-m_temp*m_temp);
						for(; 0 <= up_count + down_count + 1 -K ;up_count--){
						temp.push_back("RS " + to_string(get_hex(x + up_count*x_c,y + up_count*y_c)) + " " + to_string(get_pos(x + up_count*x_c,y + up_count*y_c)) + " RE " +to_string(get_hex(x + (up_count-K +1)*x_c,y + (up_count-K +1)*y_c)) + " " + to_string(get_pos(x + (up_count-K +1)*x_c,y + (up_count-K +1)*y_c))   );
						}
					}
				}
			}
		}
	}
	if(temp.size() == 0 || count == 0 ){
		return temp;
	}
	else{
		for(int i =0 ; i < temp.size() ;i++){
			string s = temp[i];
			execute_seq(s);
			p_turn = 1 - p_turn; 
			
			vector<string> nextdi = determine_5(x1,y1,x2,y2,0);
			if(nextdi.size() == 0){
				for(int i1 = 1 ; i1 <= rings[p_turn][0];i1++){
					int x_temp = rings[p_turn][2*i1 - 1];
					int y_temp = rings[p_turn][2*i1];
					ans.push_back(s + " X " + to_string(get_hex(x_temp,y_temp)) + " " + to_string(get_pos(x_temp,y_temp)));
				}
			}		 
			else{
				for(int i1 = 1 ; i1 <= rings[p_turn][0];i1++){
					int x_temp = rings[p_turn][2*i1 - 1];
					int y_temp = rings[p_turn][2*i1];
					string s1 = s + " X " + to_string(get_hex(x_temp,y_temp)) + " " + to_string(get_pos(x_temp,y_temp));
					for(int i2 = 1 ;i2 <= rings[p_turn][0];i2++){
						if(i1 != i2){
							int x_temp1 = rings[p_turn][2*i2 - 1];
							int y_temp1 = rings[p_turn][2*i2];
							string s2 = " X " + to_string(get_hex(x_temp1,y_temp1)) + " " + to_string(get_pos(x_temp1,y_temp1));;
							for(int i3 = 0 ; i3 < nextdi.size();i3++){
								ans.push_back(s1 + " " + nextdi[i3] + s2 );
							}
						}
					}
				}
			}
			
			p_turn = 1 - p_turn;
			dexecute_seq(s);
		}
	}
	return ans;

}
int game::diagonal_lines(int x, int y,int m , int ours){
	int score = 0 ;
	for(int i = -1 ; i <=1 ;i++){
		if(i!=m){
			int up_count = number_backrays(x,y,i,1,0,ours);
			int down_count = number_backrays(x,y,i,-1,0,ours);
			if(ours == 1) {
				if(up_count + down_count + 1 < K) score += coeff[p_turn][up_count + down_count +1] - coeff[p_turn][up_count] - coeff[p_turn][down_count]; //here greater than k cases are not included
				else{
					score += coeff[p_turn][K] - coeff[p_turn][up_count] - coeff[p_turn][down_count];
					int x_c = (2-i*i)*i ;
					int y_c = (2-i*i);
					for(; 0 <= up_count + down_count + 1 -K ;up_count--){
							current_check->push_back("RS " + to_string(get_hex(x + up_count*x_c,y + up_count*y_c)) + " " + to_string(get_pos(x + up_count*x_c,y + up_count*y_c)) + " RE " +to_string(get_hex(x + (up_count-K +1)*x_c,y + (up_count-K +1)*y_c)) + " " + to_string(get_pos(x + (up_count-K +1)*x_c,y + (up_count-K +1)*y_c)) );
					}
				}
			}
			else{
				score += coeff[1-p_turn][up_count + down_count +1] - coeff[1-p_turn][up_count] - coeff[1-p_turn][down_count];
			}
		}
	}
	return score;
}
int game::number_backrays(int x , int y , int m , int a, int initial,int ours){
	int ans = initial ;
	for(int j = 1 ; j <= (2*N +1);j++ ){
    	x += a*(2-m*m)*m; 
    	y += a*(2-m*m);
    	if(!co_poss(x,y)) break;
    	else if(box[x][y] == ours*(2-4*p_turn)) ans++;
    	else break;
    }
	return ans;		    
}
void game::unnamed_function( vector<pair<int,string>>* pointer, string pre_check_string,int pre_count){
	vector<string> abq ;
	current_check = &abq;
	for(int i = 1 ; i <= rings[p_turn][0];i++){
		int mark_x = rings[p_turn][2*i - 1];
		int mark_y = rings[p_turn][2*i] ;
		for(int m = -1 ; m <= 1 ;m++){
			vector<string> c;
			current_check = &c;
			int score_base_temp= diagonal_lines(mark_x,mark_y,m,1);	
			vector<string> b;
			for(int temp = 0 ; temp < c.size();temp++){
				b.push_back(c[temp]); 
			}
			for(int a = -1 ; a <=1 ;a+=2){
				bool ch = false;//ch if marker is visited
			    bool cur_cov = true; // last marker color
			    bool ab = false ; //first coversion or zero visit;
			    int score_base = score_base_temp;
				if(a == 1 ) current_check = &b;
				int x = mark_x ;
			    int y = mark_y ;
			    int covering = number_backrays(x,y,m,-a,1,1);
			    int hex_t1 = get_hex(x- (K-1)*a*(2-m*m)*m,y -(K-1)*a*(2-m*m) ); 
			    int pos_t1 = get_pos(x- (K-1)*a*(2-m*m)*m,y -(K-1)*a*(2-m*m) );
			    if(covering >= K) current_check -> push_back("RS " + to_string(get_hex(x,y)) + " " + to_string(get_pos(x,y)) + " RE " + to_string(hex_t1) +" " + to_string(pos_t1));
			    
			    int covering_temp = covering ;
			    for(int j = 1 ; j <= (2*N +1);j+=1 ){
			    	x += a*(2-m*m)*m;
			    	y += a*(2-m*m);
			    	if(!co_poss(x,y)) break;
			    	else if(box[x][y] == 0){  
						string M = "S " + to_string(get_hex(mark_x,mark_y)) + " " + to_string(get_pos(mark_x,mark_y)) + " M " + to_string(get_hex(x,y))+ " " + to_string(get_pos(x,y));

						if(!ch){
							if(!ab){ 
								score_base += coeff[p_turn][covering] - coeff[p_turn][covering - 1];
							}
						}	
						else{
							if(cur_cov) {
								if(ab)	score_base += coeff[p_turn][covering] + coeff[1-p_turn][covering] ;
								else score_base +=coeff[p_turn][covering] + coeff[1 - p_turn][covering - covering_temp] - coeff[p_turn][covering_temp - 1]; 
							}
							else {
								score_base -= coeff[1-p_turn][covering] + coeff[p_turn][covering];
							
							}
						}
						covering = 0 ;
						//case of ending game not written here
						if(pre_check_string == "" && current_check->size() == 0) pointer->push_back(make_pair(score_base,M));
						else if (current_check->size()== 0){
						 pointer -> push_back(make_pair(score_base+pre_count*coeff[p_turn][K] , pre_check_string + " " + M ));
						
						}
						else if(pre_check_string == ""){
							for(int p = 0 ; p < current_check ->size();p++ ){
								for(int t = 1 ; t <= rings[p_turn][0];t++){
									int x_temp = rings[p_turn][2*t - 1];
									int y_temp = rings[p_turn][2*t];
									if(t!=i)pointer -> push_back(make_pair(score_base,M +" " +current_check[0][p] + " X " + to_string(get_hex(x_temp,y_temp)) + " " + to_string(get_pos(x_temp,y_temp))) );	
									else pointer ->push_back(make_pair(score_base,M +" " +current_check[0][p] + " X " + to_string(get_hex(x,y)) + " " + to_string(get_pos(x,y))) );
								}
								
							}
						}
						else{
							for(int p = 0 ; p < current_check ->size();p++ ){
								pointer -> push_back(make_pair(score_base+pre_count*coeff[p_turn][K],pre_check_string + " " + M +" " +current_check[0][p]) );
							}
						}	
						ab = true ;
			    		if(ch) break;
			    	}
			    	else if(box[x][y]  == 2 - 4*p_turn ){
			    		score_base -= diagonal_lines(x,y,m,-1);
			    		score_base -= diagonal_lines(x,y,m,1);
			    		if(!cur_cov) covering++;
			    		else{
			    			if(!ab){
			    				score_base += coeff[p_turn][covering] + coeff[1-p_turn][covering - covering_temp] - coeff[1-p_turn][covering_temp - 1];
			    				
			    				ab = true;
			    			}
			    			else score_base += coeff[p_turn][covering] + coeff[1-p_turn][covering] ;
				    		covering = 1;
					   		cur_cov = false;
			    		}
			    		ch = true ;
			    	}
			    	else if(box[x][y] == 4*p_turn - 2){//it changes to our marker 
			    		score_base += diagonal_lines(x,y,m,1);
			    		score_base += diagonal_lines(x,y,m,-1);
			    		if(cur_cov) {
			    			covering++;
			    			hex_t1 = get_hex(x- (K-1)*a*(2-m*m)*m,y -(K-1)*a*(2-m*m)     ); 
			    			pos_t1 = get_pos(x- (K-1)*a*(2-m*m)*m,y -(K-1)*a*(2-m*m)     );
			    			if(covering >= K) current_check -> push_back("RS " + to_string(get_hex(x,y)) + " " + to_string(get_pos(x,y)) + " RE " + to_string(hex_t1) +" " + to_string(pos_t1));

			    		}	
			    		else {
			    			score_base -= coeff[p_turn][covering] + coeff[1-p_turn][covering] ;
			    			covering = 1;
			    			cur_cov = true;
			    		}	
			    		ch = true ;
			    	}	 
			    	else break; 
			    }
			}
		}
	}
	current_check = &abq;
}
vector<pair<int,string>> game::possible_moves(int q , int w , int e , int r){
	vector<string> pre_check ; 
	if(rings[0][0] == M - 2){
		coeff[1][5] = 50000;
		coeff[1][6] = 500000;	
	}
	else if(rings[0][0]==M - 1){
		coeff[1][5] = 20000;
		coeff[1][6] = 200000;	
	}
	if(rings[1][0] == M - 2){
		coeff[0][5] = 50000;
		coeff[0][6] = 500000;	
	}
	else if(rings[1][0] == M - 1){
		coeff[0][5] = 20000;
		coeff[0][6] = 200000; 
	}  
	if(q != 0 || w != 0 || e != 0 || r != 0 ) pre_check = determine_5(get_x(q,w),get_y(q,w),get_x(e,r),get_y(e,r),1);
	vector<pair<int , string>> ans ; 
	if(pre_check.size()== 0) unnamed_function(&ans,"",0);
	else{
		for(int i = 0 ; i < pre_check.size();i++){
			execute_seq(pre_check[i]);
			p_turn = 1- p_turn;
			unnamed_function(&ans,pre_check[i],pre_check[i].length() / 19);
			p_turn = 1 - p_turn;
			dexecute_seq(pre_check[i]);
		}
	}
	return ans;
 }
// int main(){
// 	game g(5,5,5,3);
// 	g.box[5][10] = 0;
// 	g.box[5][12] = 0;
// 	g.box[5][14] = 0;
// 	g.box[5][16] = 0;
// 	g.box[5][18] = 0;
// 	g.p_turn = 1 - g.p_turn;
// 	g.dexecute_seq("RS 0 0 RE 4 0");
// 	cout <<g.box[5][10] ;
// 	cout <<g.box[5][12] ;
// 	cout <<g.box[5][14] ;
// 	cout <<g.box[5][16] ;
// 	cout <<g.box[5][18] ;
// 	g.execute_seq("RS 0 0 RE 4 0");
// 	cout <<g.box[5][10] ;
// 	cout <<g.box[5][12] ;
// 	cout <<g.box[5][14] ;
// 	cout <<g.box[5][16] ;
// 	cout <<g.box[5][18] ;

// }

// int time_left ;
// int player;
// string opp_move;
// class node{
// public:
// 	string move;
// 	int value;
// 	int carry;
// 	node(int v , string s , int c){
// 		value = v ;
// 		move = s;
// 		carry = c ;
// 	}
// };

// int max(int a , int b ){
// 	if(a>b) return a;
// 	return b ;
// }
// int min(int a , int b ){
// 	if(a>b) return b;
// 	return a ;
// }
// node* MaxMinVal(game* m ,node* no ,string S,  int count, int alpha , int beta,bool b){
// 	if(count == 0 ) return no;
// 	if(m->rings[0][0] <= m->M-3 || m -> rings[1][0] <= m->M-3  ) return no ;
// 	vector<string> t;
// 	stringstream c1(S);
// 	while(getline(c1,S,' ')){
// 		t.push_back(S);
// 	}
// 	int q = 0 ;
// 	int w = 0 ;
// 	int e = 0 ;
// 	int r = 0 ;
// 	for(int i =0 ; i < t.size();i=i+3){
// 		if(t[i] == "S"){
// 			q = stoi(t[i+1]) ;
// 			w = stoi(t[i+2]) ;
// 			e = stoi(t[i+4]) ;
// 			r = stoi(t[i+5]) ;
// 			break;
// 		}
// 	}
// 	//cout << "serios" <<endl;
// 	vector<pair<int,string>> possible_moves = m -> possible_moves(q,w,e,r);
	
// 	if(possible_moves.size() == 0) return no ;
// 	node* best;
// 	if(!b){
// 		best = new node(INT_MAX,"",INT_MAX);
// 	}
// 	else{
// 		best = new node(INT_MIN,"",INT_MIN);
// 	}
// 	for(int i = 0 ; i < possible_moves.size() ;i++){
// 		int a = possible_moves[i].first;
// 		m->execute_seq(possible_moves[i].second);
// 		//if(count == 1) cout << possible_moves[i].first<<" "<<possible_moves[i].second <<endl;
// 		if(!b) a = -a;
// 		node* next = new node(no->value + a,possible_moves[i].second,no->value + a);
// 		if(b) next->carry =  MaxMinVal(m,next,possible_moves[i].second, count-1 ,alpha , beta,false) -> carry ;
// 		else next->carry = MaxMinVal(m,next,possible_moves[i].second, count-1 ,alpha , beta,true) -> carry ;
// 		m->dexecute_seq(possible_moves[i].second);
// 		if (b) alpha = max(alpha,next->carry); 
// 		else beta = min(beta ,next->carry);
// 		if( (b &&next->carry > best -> carry) || (!b && next->carry < best -> carry) ){
// 			free(best);
// 			best = next;
// 		} 
// 		if(alpha >= beta) return next;
// 		else if(best != next )free(next);     //check once
// 	}
// 	return best ;	//check once
// }
// int main(){
// 	game g(5,5,5,3);
// 	g.execute_seq("P 1 2");
// 	g.execute_seq("P 0 0");
// 	g.execute_seq("P 1 4");
// 	g.execute_seq("P 1 0");
// 	g.execute_seq("P 1 5");
// 	g.execute_seq("P 1 1");
// 	g.execute_seq("P 4 7");
// 	g.execute_seq("P 1 3");
// 	g.execute_seq("P 2 8");
// 	g.execute_seq("P 2 5");
// 	g.execute_seq("S 4 7 M 2 3");
// 	g.execute_seq("S 2 5 M 3 7");
// 	g.execute_seq("S 2 8 M 3 13");
// 	g.execute_seq("S 1 0 M 3 16");
// 	g.execute_seq("S 2 3 M 2 4");
// 	g.execute_seq("S 3 16 M 2 10");
// 	g.execute_seq("S 2 4 M 2 2");
// 	g.execute_seq("S 2 10 M 3 11");
// 	g.execute_seq("S 3 13 M 4 17");
// 	g.execute_seq("S 3 11 M 2 9");
// 	g.execute_seq("S 1 5 M 4 23");
// 	g.execute_seq("S 1 3 M 4 15");
// 	g.execute_seq("S 1 2 M 3 6");
// 	g.execute_seq("S 2 9 M 4 14 RS 3 11 RE 3 16 X 4 14");
// 	g.execute_seq("S 2 2 M 3 4");
// 	g.execute_seq("S 4 15 M 2 7");
// 	g.execute_seq("S 4 17 M 3 11");
// 	g.execute_seq("S 0 0 M 2 10");
// 	g.execute_seq("S 3 6 M 5 12");
// 	g.execute_seq("S 1 1 M 3 8");
// 	g.execute_seq("S 4 23 M 5 7");
// 	g.execute_seq("S 3 7 M 5 8 RS 1 5 RE 3 6 X 2 10");
// 	g.execute_seq("S 5 12 M 3 5");
// 	g.execute_seq("S 3 8 M 3 9");
// 	g.execute_seq("S 3 4 M 2 1");
// 	g.execute_seq("S 3 9 M 0 0");
// 	g.execute_seq("S 2 1 M 5 1");
// 	//cout << g.box[g.get_x(2,1) ][g.get_y(2,1) ]<<endl;
// 	//cout << g.box[g.get_x(3,1) ][g.get_y(3,1) ]<<endl;
// 	vector<pair<int,string>> ab = g.possible_moves(3,3,4,3);
// 	for(int i = 0 ; i < ab.size();i++){
// 		cout << "main "<<ab[i].first << " " <<ab[i].second<<endl;
// 	//	g.execute_seq(ab[i].second);
// 	//	vector<pair<int,string>> abc = g.possible_moves(1,2,2,4);
// 	//	for(int i1 = 0 ;i1< abc.size();i1++){
// 	//		cout << abc[i1].first <<" " <<abc[i1].second<<endl;
// 	//	}
// 	//	g.dexecute_seq(ab[i].second);	
// 	}
// 	node n(0,"",0);
// 	node* temp ;
// 	string opp_move = "S 2 1 M 5 1";
// 	temp = MaxMinVal(&g,&n,opp_move,4,INT_MIN,INT_MAX,true);
// 	cout << temp -> move <<endl;


// }

