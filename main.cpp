#include "yinsh.h"

int player_num,rings_num,markers_num;
	float timelimit;

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

// Place xy_to_ring(int x,int y)
// {
 
// }

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
		Place p = {0,0};
		p = ring_to_xy(x1,y1);

		Move mv = {mov_ty,p.x,p.y};

		in_moves.push_back(mv);


	} 

}

// double evaluated_value()
// {
	
// }


// void play(int id)
// {

//     vector<Move> playermoves,opponentmoves;
//     if(id==1){
       

//     }
// }

int main(){
	
	string ind,rings,time,mark;
	cin>>ind >> rings >> time>> mark ;
	player_num = stoi(ind);
	rings_num = stoi(rings);
	timelimit = stoi(time);
	markers_num = stoi(mark);

	Yinsh game = Yinsh(rings_num,2*rings_num+1,markers_num);
    
    // game.play(player_num);
    
    

	//Mybot* b = new Mybot(player_num,rings_num,timelimit,markers_num);



	
}