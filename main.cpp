#include "mybot.h"

double evaluated_value(){
	
}
void play(int id){

	
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