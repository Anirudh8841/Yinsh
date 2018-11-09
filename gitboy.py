from game import Game
import random
import sys
import time
import os
from board1 import evaluationFunction as evaluate 
from board1 import validMovesList as valid_move_list
from board1 import checkRuns as rows_formed
from board1 import execute_move as execute


class Node:
	def __init__(self, board, move, list_children, num_ring, won):
		self.board = board
		self.move = move
		self.list_children = list_children
		self.num_ring = num_ring
		self.won = won
		self.utility = 0
			
	def append_children(self, num, player):
		if num == 0:
			for i in range(11):
				for j in range(19):
					if self.board[i][j] == 0:
						temp_move = "P " + str(i) + " " + str(j)
						b = self.board
						temp_board = execute(b,temp_move,player)
						a = Node(temp_board,temp_move, [], 0, 0)
						#print(a.board)
						(self.list_children).append(a)
		
		if num == 1:
			if player == 0:
				ring = 2
				marker = 1
			if player == 1:
				ring = -2
				marker = -1
			if self.won == 0:
				while (rows_formed(self.board, 0) != []):
					temp = rows_formed(self.board, 0)
					lol = []
					for j in temp:
						temp_move = "RS " + str(j[0][0]) + " " + str(j[0][1]) + " RE " + str(j[1][0]) + " " + str(j[1][1])
						lol.append(Node(execute(self.board, temp_move, player),temp_move, [], self.num_ring, self.won))
					
					lol1 = []
					for i in lol:
						for j in range(11):
							for k in range(19):
								if i.board[j][k] == ring:
									temp_move = i.move + " X " + str(j) + " " + str(k)
									ring_num = i.num_ring + 1
									if ring_num>2:
										lol1.append(Node(execute(i.board, temp_move, player), temp_move, i.list_children, ring_num, 1))
									else:
										lol1.append(Node(execute(i.board, temp_move, player), temp_move, i.list_children, ring_num, 0))
					max_node = 'null'
					max_score = -1000
					
					for i in lol1:
						score = evaluate(i.board, 0)
						if score>max_score:
							max_score = score
							max_node = i
					self.board = i.board
					self.move = i.move
					self.won = i.won
					self.num_ring = i.num_ring
					self.list_children = i.list_children
					
									
				if rows_formed(self.board, 0) == []:
					for i in range(11):
						for j in range(19):
							if self.board[i][j] == ring:
								for (k,l) in valid_move_list(self.board, [i,j]):
									temp_move = "S " + str(i) + " " + str(j) + " M " + str(k) + " " + str(l)
									(self.list_children).append(Node(execute(self.board,temp_move,player), temp_move, [], self.num_ring, self.won))
					'''
					for i in self.list_children:
						print(get_hex_move(i.move))
						print(i.board)
					print("---------------------------------------------------------------")
					'''
					
					#for i in self.list_children:
						#print(get_hex_move(i.move))
						#print(i.board)
					
					for i in self.list_children:	
						#print (get_hex_move(i.move))
						#print (rows_formed(i.board, 0))
						#print (get_hex_move(i.move))	
						if (rows_formed(i.board, 0) or rows_formed(i.board, 1))!= []:
							#print("asdasdasdasd")
							#print (get_hex_move(i.move))
							#print (rows_formed(i.board, 0))
							if i.won == 0:
								self.list_children.remove(i)
								#print("yessss")
								temp = []
								for j in rows_formed(i.board,0):
									temp_move = i.move + " RS " + str(j[0][0]) + " " + str(j[0][1]) + " RE " + str(j[1][0]) + " " + str(j[1][1])
									temp.append(Node(execute(i.board, temp_move, player), temp_move, i.list_children, i.num_ring, i.won)) 
								
								temp1 = []
								for j in temp:
									for k in range(11):
										for l in range(19):
											if j.board[k][l] == ring:
												temp_move = j.move + " X " + str(k) + " " + str(l)
												rings_num = j.num_ring + 1
												if rings_num > 2:
													temp1.append(Node(execute(j.board, temp_move, player), temp_move, j.list_children, rings_num, 1))
												else:
													temp1.append(Node(execute(j.board, temp_move, player), temp_move, j.list_children, rings_num, 0))
								for j in temp1:
									(self.list_children).append(j)
									
									
						
			



def get_tree(num, board, num_moves):
	root = Node(board, " ", [], 0, 0)
	if num == 0:
		root.append_children(num, 0)
		#for i in root.list_children:
			#i.append_children(num, 1)
			#for j in i.list_children:
				#j.append_children(num, 0)
		return root
		
	if num == 1:
		if num_moves < 25:
			root.append_children(num, 0)
			#for i in root.list_children:
				#print("-------")
				#print (get_hex_move(i.move))
				#print("-----")
				#i.append_children(num, 1)
				#for j in i.list_children:
					#j.append_children(num, 0)
		else:
			root.append_children(num, 0)
			for i in root.list_children:
				i.append_children(num, 1)
				for j in i.list_children:
					j.append_children(num, 0)
					for k in j.list_children:
						k.append_children(num, 1)
						for l in k.list_children:
							l.append_children(num, 0)
		return root
			

def min_val(node, alpha, beta, player):
	#print "AlphaBeta-->MIN: Visited Node :: " + str(get_hex_move(node.move))
	if node.list_children == []:
		node.utility = evaluate(node.board, player) 
		return node.utility
	
	infinty = float('inf')
	value = infinty
	
	children = node.list_children
	#print(children)
	for child in children:
		value = min(value, max_val(child, alpha, beta, 1-player))
		#print("test")
		if value <= alpha:
			return value
		beta = min(beta, value)
	return value


def max_val(node, alpha, beta, player):
	#print "AlphaBeta-->MAX: Visited Node :: " + str(get_hex_move(node.move))
	if node.list_children == []:
		node.utility = evaluate(node.board, player) 
		#print(node.utility)
		#print(node.move)
		return node.utility
	
	infinty = float('inf')
	value = -infinty
	
	children = node.list_children
	for child in children:
		value = max(value, min_val(child, alpha, beta, 1-player)) 
		if value >= beta:
			return value
		alpha = max(alpha, value)
	return value


def main_minimax(node):
	#print "starting minimax"
	infinty = float('inf')
	best_val = -infinty
	beta = infinty
	
	children = node.list_children
	best_child = None
	for child in children:
		value = max_val(child, best_val, beta, 0)
		if value > best_val:
			best_val = value
			best_child = child
	return best_child



def minimax(num_moves, board):
	if num_moves < 5:
		tree = get_tree(0, board, num_moves)
	else:
		tree = get_tree(1, board, num_moves)
	#print "tree ready"
	#print (tree.list_children)	
	#print(len(tree.list_children))
	#for i in tree.list_children:
		#print(get_hex_move(i.move))	
	child = main_minimax(tree)
	return child.move


null = 'null'

b_to_h = [[null, null, null, null, null, null, (5,24), null, (5,23), null, (5,22), null, (5,21), null, null, null, null, null, null], [null, null, null, (5,26), null, (4,20), null, (4,19), null, (4,18), null, (4,17), null, (4,16), null, (5,19), null, null, null], [null, null, (5,27), null, (4,21), null, (3,15), null, (3,14), null, (3,13), null, (3,12), null, (4,15), null, (5,18), null, null], [null, (5,28), null, (4,22), null, (3,16), null, (2,10), null, (2,9), null, (2,8), null, (3,11), null, (4,14), null, (5,17), null], [(5,29), null, (4,23), null, (3,17), null, (2,11), null, (1,5), null, (1,4), null, (2,7), null, (3,10), null, (4,13), null, (5,16)], [null, (4,0), null, (3,0), null, (2,0), null, (1,0), null, (0,0), null, (1,3), null, (2,6), null, (3,9), null, (4,12), null], [(5,1), null, (4,1), null, (3,1), null, (2,1), null, (1,1), null, (1,2), null, (2,5), null, (3,8), null, (4,11), null, (5,14)], [null, (5,2), null, (4,2), null, (3,2), null, (2,2), null, (2,3), null, (2,4), null, (3,7), null, (4,10), null, (5,13), null], [null, null, (5,3), null, (4,3), null, (3,3), null, (3,4), null, (3,5), null, (3,6), null, (4,9), null, (5,12), null, null], [null, null, null, (5,4), null, (4,4), null, (4,5), null, (4,6), null, (4,7), null, (4,8), null, (5,11), null, null, null], [null, null, null, null, null, null, (5,6), null, (5,7), null, (5,8), null, (5,9), null, null, null, null, null, null]]

h_to_b = [[(5,9)],[(5,7),(6,8),(6,10),(5,11),(4,10),(4,8)],[(5,5),(6,6),(7,7),(7,9),(7,11),(6,12),(5,13),(4,12),(3,11),(3,9),(3,7),(4,6)],[(5,3),(6,4),(7,5),(8,6),(8,8),(8,10),(8,12),(7,13),(6,14),(5,15),(4,14),(3,13),(2,12),(2,10),(2,8),(2,6),(3,5),(4,4)],[(5,1),(6,2),(7,3),(8,4),(9,5),(9,7),(9,9),(9,11),(9,13),(8,14),(7,15),(6,16),(5,17),(4,16),(3,15),(2,14),(1,13),(1,11),(1,9),(1,7),(1,5),(2,4),(3,3),(4,2)],[null,(6,0),(7,1),(8,2),(9,3),null,(10,6),(10,8),(10,10),(10,12),null,(9,15),(8,16),(7,17),(6,18),null,(4,18),(3,17),(2,16),(1,15),null,(0,12),(0,10),(0,8),(0,6),null,(1,3),(2,2),(3,1),(4,0)]]


flag = 0
data = sys.stdin.readline().strip().split() # Initialize Environment
player = int(data[0]) - 1 # player can have values 0 and 1
n = int(data[1]) # n can have values 5, 6, or 7
time_left = int(data[2])

board = []

for i in range(11):
	board.append([-100 for x in range(19)])
	
	
for i in h_to_b:
	for j in i:
		if j != 'null':
			board[j[0]][j[1]] = 0
			
			
def get_board_move(move):
	temp = (move.strip()).split(" ")
	final = []
	turn = len(temp)
	i = 0
	while (turn>0):
		if (i%3 == 0):
			final.append(temp[i])
			i+=1
			turn = turn - 1
		else:
			move = h_to_b[int(temp[i])][int(temp[i+1])]
			final.append(str(move[0]))
			final.append(str(move[1]))
			i = i + 2
			turn = turn - 2
	return " ".join(final)

def get_hex_move(move):
	temp = (move.strip()).split(" ")
	final = []
	turn = len(temp)
	i = 0
	while (turn>0):
		if (i%3 == 0):
			final.append(temp[i])
			i+=1
			turn = turn - 1
		else:
			move = b_to_h[int(temp[i])][int(temp[i+1])]
			final.append(str(move[0]))
			final.append(str(move[1]))
			i = i + 2
			turn = turn - 2
	return " ".join(final) + "\n"

num_moves = 0		
while(True):		
	
	f = open("test.txt", "a")
	g = open("test1.txt", "a")
	if ((flag == 0)	and (player == 0)):
		my_move = "P 5 9" + "\n"
		board = execute(board, my_move, 0)
		num_moves += 1
		flag = 1
		sys.stdout.write("P 0 0\n")
		sys.stdout.flush()
	else:
		op_move = str(sys.stdin.readline().strip())
		g.write(op_move + "\n")
		op_move = str(get_board_move(op_move))
		f.write(op_move + "\n")
		board = execute(board, op_move, 1)
		my_move = minimax(num_moves, board)
		board = execute(board, my_move, 0)
		f.write(my_move + "\n")
		my_move = str(get_hex_move(my_move))
		g.write(my_move + "\n")
		num_moves += 1
		sys.stdout.write(my_move)
		sys.stdout.flush()
	g.close()
	f.close()

		
'''
def smart_board(board):
	temp = []
	for i in range(11):
		temp.append([-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100])
	
	col = 0
	for i in board:
		row = 0
		for j in i:
			if j['x']==-1:
				row+=1
			else:
				temp[col][row] = j['piece']
				row+=1
		col+=1
	return temp
		
def smart_place(board):
	return (1,0)
class RandomPlayer:
	def __init__(self):
		data = sys.stdin.readline().strip().split() # Initialize Environment
		self.player = int(data[0]) - 1 # player can have values 0 and 1
		self.n = int(data[1]) # n can have values 5, 6, or 7
		self.time_left = int(data[2])
		self.game = Game(self.n)
		self.RingPos = {}
		self.play()
	def placeRing(self, board):
		movetype = 'P'
		position = smart_place(board)
		hexagon = random.randint(0,self.n)
		position = random.randint(0,max(0,6*hexagon-1))
		if hexagon==self.n and position%self.n==0:
			position+=1
		return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position), len(self.RingPos), hexagon, position
	def selectRing(self, board):
		movetype = 'S'
		ring_num = random.randint(0,self.n-1)
		while ring_num not in self.RingPos:
			ring_num = random.randint(0,self.n-1)
		ring = self.RingPos[ring_num]
		return '{type} {hex} {pos}'.format(type=movetype, hex=ring[0], pos=ring[1]), ring_num
	def moveRing(self, board):
		movetype = 'M'
		hexagon = random.randint(0,self.n)
		position = random.randint(0,max(0,6*hexagon-1))
		if hexagon==self.n and position%self.n==0:
			position+=1
		return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position), hexagon, position
	def removeRowStart(self, board):
		movetype = 'RS'
		hexagon = random.randint(0,self.n)
		position = random.randint(0,max(0,6*hexagon-1))
		if hexagon==self.n and position%self.n==0:
			position+=1
		return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position)
	def removeRowEnd(self, board):
		movetype = 'RE'
		hexagon = random.randint(0,self.n)
		position = random.randint(0,max(0,6*hexagon-1))
		if hexagon==self.n and position%self.n==0:
			position+=1
		return '{type} {hex} {pos}'.format(type=movetype, hex=hexagon, pos=position)
	def removeRing(self, board):
		movetype = 'X'
		ring_num = random.randint(0,self.n-1)
		while ring_num not in self.RingPos:
			ring_num = random.randint(0,self.n-1)
		ring = self.RingPos[ring_num]
		return '{type} {hex} {pos}'.format(type=movetype, hex=ring[0], pos=ring[1]), ring_num
	def play_move_seq(self, move_seq):
		moves = ' '.join(move_seq) + '\n'
		sys.stdout.write(moves)
		sys.stdout.flush()
	def play(self):
		if self.player == 1:
			move = sys.stdin.readline().strip()
			self.game.execute_move(move)
		while True: # Keep playing moves till game is over
			move_seq = []
			while True: # Loop till valid move sequence is found
				state = self.game.check_player_state()
				board = self.game.get_board()
				board = smart_board(board)
				f = open("text.txt", 'w')
				f.write(str(board))
				f.close()
				if state == 0: ## Place Rings
					moveP, i, hex, pos = self.placeRing(board)
					success = self.game.execute_move(moveP)
					if success != 0:
						self.RingPos[i] = (hex, pos)
						move_seq.append(moveP)
						break
				elif state == 1: ## Select a Ring and the Move to Valid Postion
					moveS, i = self.selectRing(board)
					moveM, hex, pos = self.moveRing(board)
					self.game.execute_move(moveS)
					state = self.game.check_player_state()
					success = self.game.execute_move(moveM)
					if success != 0:
						self.RingPos[i] = (hex, pos)
						state = self.game.check_player_state()
						move_seq.append(moveS); move_seq.append(moveM)
						if state != 3:
							break
				elif state == 2:
					raise AssertionError("The player state cannot be 2 after a sequence of valid moves")
				elif state == 3 or state == 6: ## Select Row to Remove (State 6 if other players your row)
					move_start = self.removeRowStart(board)
					success = self.game.execute_move(move_start)
					if success != 0:
						while True:
							move_end = self.removeRowEnd(board)
							success = self.game.execute_move(move_end)
							if success != 0:
								break
						state = self.game.check_player_state()
						move_seq.append(move_start); move_seq.append(move_end);
				elif state == 4 or state == 7: ## Select Ring to Remove (State 7 if other players your row)
					move, i = self.removeRing(board)
					del self.RingPos[i]
					self.game.execute_move(move)
					move_seq.append(move)
					if state == 7:
						continue
					state = self.game.check_player_state()
					if state != 3:
						break
			self.play_move_seq(move_seq)
			
			## Execute Other Player Move Sequence
			move = sys.stdin.readline().strip()
			self.game.execute_move(move)
random_player = RandomPlayer()
'''