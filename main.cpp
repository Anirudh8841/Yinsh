#include "yinsh.h"



Place ring_to_xy(int hex,int pos)
{
	Place ans;
	   
}

Place xy_to_ring(int x,int y)
{
	Place 
}

void input_moves(vector<Move> &in_moves)
{
	string mov_ty;
	int x,y;
	string word;
	string dup;
	getline(cin,dup);
	while(dup.length==0){
		getline(cin,dup);
	}
	istringstream ss(dup);
	while(ss>>word)
	{
		mov_ty = word;
		ss>>word;
		x = stoi(word);
		ss>>word;
		y=stoi(word);
		Place p = ring_to_xy(x,y);
		Move mv = {mov_ty,p.x,p.y};

		in_moves.push_back(mv);


	} 

}

double evaluated_value()
{
	
}


void play(int id)
{

    vector<Move> playermoves,opponentmoves;
    if(id==1){
       

    }
}

int main(){
	int player_num,rings_num,markers_num;
	float timelimit;
	string ind,rings,time,mark;
	cin>>ind >> rings >> time>> mark ;
	player_num = stoi(ind);
	rings_num = stoi(rings_num);
	timelimit = stoi(time);
	markers_num = stoi(mark);

	Yinsh game = Yinsh(rings_num,2*rings_num+1,markers_num);
    
    game.play(player_num);
    
    

	//Mybot* b = new Mybot(player_num,rings_num,timelimit,markers_num);



	
}