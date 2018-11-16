#include <cstdlib>
#include <iostream>
#include <ctime>
#include "game.h"
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

int time_left ;
int player;
string opp_move;
class node{
public:
	string move;
	int value;
	int carry;
	node(int v , string s , int c){
		value = v ;
		move = s;
		carry = c ;
	}
};

int max(int a , int b ){
	if(a>b) return a;
	return b ;
}
int min(int a , int b ){
	if(a>b) return b;
	return a ;
}
node* MaxMinVal(game* m ,node* no ,string S,  int count, int alpha , int beta,bool b){
	if(count == 0 ) return no;
	if(m->rings[0][0] <= m->M-3 || m -> rings[1][0] <= m->M-3  ) return no ;
	vector<string> t;
	stringstream c1(S);
	while(getline(c1,S,' ')){
		t.push_back(S);
	}
	int q = 0 ;
	int w = 0 ;
	int e = 0 ;
	int r = 0 ;
	for(int i =0 ; i < t.size();i=i+3){
		if(t[i] == "S"){
			q = stoi(t[i+1]) ;
			w = stoi(t[i+2]) ;
			e = stoi(t[i+4]) ;
			r = stoi(t[i+5]) ;
			break;
		}
	}
	//cout << "serios" <<endl;
	vector<pair<int,string>> possible_moves = m -> possible_moves(q,w,e,r);
	
	if(possible_moves.size() == 0) return no ;
	node* best;
	if(!b){
		best = new node(INT_MAX,"",INT_MAX);
	}
	else{
		best = new node(INT_MIN,"",INT_MIN);
	}
	for(int i = 0 ; i < possible_moves.size() ;i++){
		int a = possible_moves[i].first;
		m->execute_seq(possible_moves[i].second);
		//if(count == 1) cout << possible_moves[i].first<<" "<<possible_moves[i].second <<endl;
		if(!b) a = -a;
		node* next = new node(no->value + a,possible_moves[i].second,no->value + a);
		if(b) next->carry =  MaxMinVal(m,next,possible_moves[i].second, count-1 ,alpha , beta,false) -> carry ;
		else next->carry = MaxMinVal(m,next,possible_moves[i].second, count-1 ,alpha , beta,true) -> carry ;
		m->dexecute_seq(possible_moves[i].second);
		if (b) alpha = max(alpha,next->carry); 
		else beta = min(beta ,next->carry);
		if( (b &&next->carry > best -> carry) || (!b && next->carry < best -> carry) ){
			free(best);
			best = next;
		} 
		if(alpha >= beta) return next;
		else if(best != next )free(next);     //check once
	}
	return best ;	//check once
}

int main ( int argc, char** argv ){
	clock_t startTime ; 
	//ifstream kin ("t.txt");
	if(player == 0){
		 startTime = clock();
	}
	string S;
	getline(cin ,S );
	vector<string> t;
	stringstream c1(S);
	while(getline(c1,S,' ')){
		t.push_back(S);
	}
	player = stoi(t[0]) -1 ;
	game g(stoi(t[1]),stoi(t[1]),stoi(t[3]),3);
	time_left = stoi(t[2]);//what is happening here


	if(player == 1){
		startTime = clock();
		getline(cin,S);
		g.execute_seq(S);
	}
	int a = 0, b = 0 , count ;
	count = 0 ;
	while(true){
		if(g.mode == 0){
			while(true){
				S = "P";
				if(g.valid(a,b)){
					S = S + " " + to_string(a) +" "+  to_string(b);
					cout << S  << endl;
					clock_t endTime = clock();
					clock_t clockTicksTaken = endTime - startTime;
					double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
					time_left = time_left - (int) timeInSeconds;
					g.execute_seq(S);
					if(b < 6*a - 1) b++;
					else a++;
					count ++;
					break;
				}
				if(b < 6*a - 1) b++;
				else a++;
			}	 
		}
		else if(g.mode == 1){
			node n(0,"",0);
			int a = INT_MIN;
			int b = INT_MAX;
			node* temp ;
			int pot = 0;
			if(time_left < 2){
				temp = MaxMinVal(&g,&n,opp_move,1,INT_MIN,INT_MAX,true);
			}
			else if(time_left < 8){
				temp = MaxMinVal(&g,&n,opp_move,2+pot,INT_MIN,INT_MAX,true);
			}
			else if(time_left < 25){
				temp = MaxMinVal(&g,&n,opp_move,3+pot,INT_MIN,INT_MAX,true);
			}			
			else{
				temp = MaxMinVal(&g,&n,opp_move,4+pot,INT_MIN,INT_MAX,true);
			}


			cout << temp ->move <<endl ;
			clock_t endTime = clock();
			clock_t clockTicksTaken = endTime - startTime;
			double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
			time_left = time_left - (int) timeInSeconds;		
			g.execute_seq(temp -> move);
			count++ ;
		}
		getline(cin,opp_move);
		startTime = clock();
		g.execute_seq(opp_move);

	}
	return 0 ;
}