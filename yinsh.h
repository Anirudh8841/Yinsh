#ifndef YINSH_H
#define YINSH_H
#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h> 

class Place
{
	public:
		int x;
		int y;
	public:
		Place(int p,int q){
			x=p;
			y=q;
		}
		Place(int null){
			x = -5;
			y = -5;
		}

};

class Move
{
	public:
		string type;
		int x;
		int y;
	public:
		Move();
		Move(string ty,int i1,int i2){
			type=ty;
			x=i1;
			y=i2;
		};


};

class Yinsh{
	public:
		int ring_size; // no of rings
		int rows;  // 2*rings+1
		int marker_rem;  // no of markers to win
		vector< vector<Place> > player; // player's rings
		vector< vector<int> > myboard;
		int cnt =0;

	public:
		Yinsh();
		Yinsh(int rings,int row,int mark);
		
		void initialize(); 
		void place_ring(int x,int y,int id);
		void select_movering(Place sel,Place mov,int id);
		void remove_row(Place p1,Place p2,int id);
		void remove_ring(Place p1,int id);
        void execute_seq(vector<Move>& move,int id);

		void neighbours(Place sel,Place dir,vector<Place>& neighbour);
		void totneighbours(Place sel,vector<Place>& neighbour);

		double evaluate_reward(int id);
		int check_five(int id,vector< vector<Place> > &five_rows);
		vector<int> eval_collinear(int id);




};

#endif