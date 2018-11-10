#ifndef YINSH_H
#define YINSH_H

using namespace std;

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
		string a;
		string b;
	public:
		Move();
		Move(string ty,string i1,string i2){
			type=ty;
			a=i1;
			b=i2;
		};


};

class Yinsh{
	public:
		int ring_size; // no of rings
		int rows;  // 2*rings+1
		int marker_rem;  // no of markers to win
		vector< vector<Place> > player; // player's rings
		vector<vector<int>> myboard;
		int cnt =0;

	public:
		// Yinsh();
		Yinsh(int rings,int row,int mark){
            ring_size = rings;
            rows = row;
            marker_rem = mark; 
		};
		void initialize(); 
		void place_ring(int x,int y,int id);
		void select_movering(Place sel,Place mov,int id);
		void remove_row(Place p1,Place p2,int id);
		void remove_ring(Place p1,int id);
        void execute_seq(vector<Move>& move,int id);

		void neighbours(Place sel,Place dir,vector<Place>& neighbour);
		void totneighbours(PLace sel,vector<Place>& neighbour);

		double evaluate_reward(int id);



};

#endif