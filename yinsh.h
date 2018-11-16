#ifndef YINSH_H
#define YINSH_H
#include <bits/stdc++.h>

using namespace std;

class Place
{
	public:
		int x;
		int y;
	public:
		Place(){};
		Place(int p,int q){
			x=p;
			y=q;
		}
		Place(int null){
			x = -10;
			y = -10;
		}

};

class Move
{
	public:
		string type;
		int x;
		int y;
	public:
		Move(){};
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
		int cnt_0 = 0 ,cnt_1 =0;
		int p0_rings =0;
		int p1_rings =0;

	public:
		Yinsh();
		// ~Yinsh();
		Yinsh(int rings,int row,int mark);
		
		void initialize(); 
		void place_ring(int x,int y,int id);
		void select_movering(Place sel,Place mov,int id);
		void remove_row(Place p1,Place p2,int id);
		void remove_ring(Place p1,int id);
        void execute_seq(vector<Move>& move,int id);

		void neighbours(Place sel,Place dir,vector<Place>& neighbour);
		void totneighbours(Place sel,vector<Place>& neighbour);

		float evaluate_reward(int id);
		
		vector<int> eval_collinear(int id);

		int num_ring_present(int id);
		void check_five(int id,vector< vector<Place> > &five_rows);
		int totcheck_linering(Place sel,int id);
		int check_linering(Place sel,Place dir,int id);

		bool check_surr(Place sel,Place dir,int id);
		bool col3(Place sel,Place dir,int id);
		bool totcheck_surr(Place sel,int id);
		bool totcol3(Place sel,int id);




};

#endif