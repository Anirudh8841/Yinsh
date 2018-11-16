#include <vector>

class game{
public :
	int p_turn  ;
	int N,M,K,L ;
	int** box;
	std::vector<std::vector<int>> rings;
	std::vector<std::string>* current_check;
	int mode ; // determines the move
	int xex1 , yos1 ; // hold the selected node
	int** coeff;

	int mton(std::string s);
	game(int n , int m , int k , int l);
	void execute_move(int s, int a , int b);
	void dexecute_move(int s, int a , int b);
	void execute_seq(std::string S);
	void dexecute_seq(std::string S);
	void update_rings(int decider , int hex1 , int pos1 , int hex2 , int pos2);
	int get_x(int a, int b);
	int get_y(int a, int b);
	int get_hex(int a, int b);
	int get_pos(int a, int b);
	bool valid(int a , int b);
	bool co_poss(int a , int b );

	std::vector<std::string> determine_5(int x1 , int y1 , int x2 , int y2, int count);
	void check_ray(int a , int b , int c , int d, std::vector<std::string>* point);
	int diagonal_lines(int x, int y,int m , int ours);
	int number_backrays(int x , int y , int m , int a, int initial, int ours);
	void unnamed_function( std::vector<std::pair<int,std::string>>* pointer,std::string pre_check,int pre_count);
	std::vector<std::pair<int,std::string>> possible_moves(int a , int b , int c , int d);
};
