
#ifndef MYBOT_H
#define MYBOT_H

#include "yinsh.h"

class Mybot{
	public:
		int player_id,rings_num,markers_num;
		float timeremaining;
		Yinsh game;
	public:
		Mybot(int id,int rings,int t,int mark_rem){
			player_id = id-1;
			rings_num = rings;
			timeremaining = t;
			markers_num = mark_rem;
			game = Yinsh(rings,2*rings+1,mark_rem);
		}
		
}