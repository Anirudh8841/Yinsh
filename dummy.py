import json
import math
import numpy as np
import os
import sys
import time

from jinja2 import Environment, FileSystemLoader
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

board_sizes = { 5 : 11, 6 : 13, 7 : 15 } # Rings : Board Size
display_size = { 5 : 650, 6 : 750, 7 : 850 } # Rings : Pixels



PATH = os.path.dirname(os.path.abspath(__file__))
TEMPLATE_ENVIRONMENT = Environment(
    autoescape=False,
    loader=FileSystemLoader(os.path.join(PATH, 'templates')),
    trim_blocks=False)
 
def render_template(template_filename, context):
    return TEMPLATE_ENVIRONMENT.get_template(template_filename).render(context)
 
def create_index_html(size, rings, rows):
    fname = "Yinsh.html"
    context = {
        'size': size,
        'rings': rings,
        'rows': rows
    }
    with open(fname, 'w') as f:
        html = render_template('index.html', context)
        f.write(html)


# class Point:
#     def __init__(self, row,place):
#         self.row 

class Game:

    def __init__(self, n, mode='CUI', time=120):

        if n in board_sizes:
            self.rings = int(n)
            self.board_size = board_sizes[n]
            self.display_size = display_size[n]
            self.myboard = [[0 for x in range(board_sizes[rings])] for y in range(board_sizes[rings])] 
        else:
            raise AssertionError("Number of rings must be either 5, 6 or 7")
        
        # Setup Driver
        create_index_html(self.display_size, n, self.board_size)
        chrome_options = Options()
        chrome_options.add_argument("--disable-infobars")
        if mode != 'GUI':
            chrome_options.add_argument('headless');
        self.driver = webdriver.Chrome(chrome_options=chrome_options)
        abs_path = os.path.abspath('Yinsh.html')
        self.driver.get("file:" + abs_path)
        self.driver.set_window_size(width=self.display_size, height=(self.display_size+60))

        self.spacing = float(self.display_size)/self.board_size 
        self.centerx = int(self.display_size)/2
        self.centery = int(self.display_size)/2

        self.timer = time # Useful to optimise bot strategy

    def get_corner_coord(self, corner, hexagon) :
        x_mov = self.spacing * hexagon * math.sin(math.radians(corner * 60))
        y_mov = -(self.spacing * hexagon * math.cos(math.radians(corner * 60)))
        return np.array([self.centerx + x_mov, self.centery + y_mov])

    def get_non_corner_coord(self, corner1, corner2, point_num_side, hexagon) :
        corner1_coord = self.get_corner_coord(corner1, hexagon)
        corner2_coord = self.get_corner_coord(corner2, hexagon)
        return ((corner1_coord * (hexagon - point_num_side) / hexagon) + (corner2_coord * point_num_side / hexagon))

    def click_at(self, hexagon, point) :
        el = self.driver.find_elements_by_id("PieceLayer")
        action = webdriver.common.action_chains.ActionChains(self.driver)
        if (hexagon == 0) :
                action.move_to_element_with_offset(el[0], self.centerx, self.centery)
        else :
            if (point % hexagon == 0) :
                pt_coord = self.get_corner_coord(point / hexagon, hexagon)
                action.move_to_element_with_offset(el[0], pt_coord[0], pt_coord[1])
            else :
                pt_coord = self.get_non_corner_coord(point // hexagon, point // hexagon + 1, point % hexagon, hexagon)
                action.move_to_element_with_offset(el[0], pt_coord[0], pt_coord[1])
        action.click()
        action.perform()

    def check_move_validity(self):
        return self.driver.execute_script('return is_valid;')

    def check_player_state(self):
        return self.driver.execute_script('return required_move;')

    def get_current_player(self):
        return self.driver.execute_script('return current_player;')

    ### Score Class
    # 3-0: 10
    # 3-1: 9
    # 3-2: 8
    # 2-0: 7
    # 2-1: 6
    # 1-0: 6
    # x-x: 5
    # 0-1: 4
    # 1-2: 4
    # 0-2: 3
    # 2-3: 2
    # 1-3: 1
    # 0-3: 0

    def calculate_score(self, rA, rB, mA, mB, Error_state):
        if Error_state == '1':
            rA = 0; rB = 3
        elif Error_state == '2':
            rB = 0; rA = 3
        if rA == 3:
            scoreA = 10 - rB; scoreB = rB
        elif rB == 3:
            scoreA = rA; scoreB = 10-rA
        elif rB == rA:
            scoreA = 5; scoreB = 5
        elif rA - rB == 2:
            scoreA = 7; scoreB = 3
        elif rB - rA == 2:
            scoreA = 3; scoreB = 7
        elif rA > rB:
            scoreA = 6; scoreB = 4
        elif rB > rA:
            scoreA = 4; scoreB = 6
        else:
            AssertionError("Cannot Calculate Score")
        scoreA = scoreA + float(mA) / 1000.0
        scoreB = scoreB + float(mB) / 1000.0
        return [scoreA, scoreB]




    def get_board(self):
       
        positions = list(self.driver.execute_script('return positions;'))
        r=0
        c=0
        for row in positions:
            for place in row:
                piece = dict(place)['piece']
                x_v = dict(place)['x']
                if piece == 2:
                    myboard[r][c]=2
                elif piece == 1:
                    myboard[r][c]=1
                elif piece == -1:
                    myboard[r][c]=-1
                elif piece == -2:
                    myboard[r][c]=-2
                elif x_v == -1
                    myboard[r][c] =-10
                c=c+1
            r=r+1
        return myboard
        

    def get_pos(self):
        positions = list(self.driver.execute_script('return positions;'))
        return positions

    def conv_hextoXY(self,hex,pos):
        
        row_n=0;
        place_n=0;


        if pos<hex:
            row_n=hex
            place_n=pos
        
        elif(pos< 2*hex):
            row_n= 2*hex - pos
            place_n=hex
        
        elif(pos< 3*hex):
            row_n = 2*hex - pos
            place_n = 3*hex - pos
        
        elif(pos< 4*hex):
            row_n = -hex 
            place_n = 3*hex - pos
        
        elif(pos< 5*hex):
            row_n = -5*hex + pos
            place_n = -hex 
        
        else:
            row_n = -5*hex + pos
            place_n = -6*hex - pos
        
        row_n = row_n+rings
        place_n = place_n+rings
        return row_n , place_n

    def rpto_hexpos(self,r,p):

        hex=0
        pos=0
        r = r - rings
        p = p - rings

        

        if(r>=p):
            if(r>=0 and p>=0):
                hex=r
                pos=p
            elif(r<=0 and p<=0):
                hex = -p
                pos = r -(5*p)
            elif(r>=0 and p<=0):
                hex = r-p
                pos = 6*r-5*p

        elif(p>r):
            if(r>=0 and p>=0):
                hex = p
                pos = 2*p-x
            elif(r<=0 and p<=0):
                hex = -1*r
                pos = (-3*r)-p
            elif(r<=0 and p>=0):
                hex = p-r
                pos = 2*p - 3*r

        return hex,pos 

    def neighbours(xcord,ycord,dir_x,dir_y,neighbour):

        token_line =0
        a = dir_x
        b = dir_y
        while xcord+a>=0 and xcord+a<=board_sizes[rings] and ycord+b>=0 and ycord+b<=board_sizes[rings] and abs()













    def get_score(self, player_id, Error_state=0):
        rings_A = 0
        rings_B = 0
        markers_A = 0
        markers_B = 0
        positions = list(self.driver.execute_script('return positions;'))
        for row in positions:
            for place in row:
                piece = dict(place)['piece']
                if piece == 2:
                    rings_A+=1
                elif piece == 1:
                    markers_A+=1
                elif piece == -1:
                    markers_B+=1
                elif piece == -2:
                    rings_B+=1
        return self.calculate_score(self.rings-rings_A, self.rings-rings_B, markers_A, markers_B, Error_state)[int(player_id)-1]

    def check_won(self):
        required_move = self.driver.execute_script('return required_move;')
        return required_move == 5

    def execute_sequence(self, moves):
        success = 1
        move_list = []
        player_id = self.get_current_player()
        for i, move in enumerate(moves):
            if i % 3 == 2:
                move_list += [move]
                move_success = self.execute_move(' '.join(move_list))
                if move_success == 0:
                    return 0
                success = success and move_success
                move_list = []
            else:
                move_list += [move]
        player = self.get_current_player()
        if player_id == player:
            return 0
        return success

    '''
    ## New suggested move types
    # P - Place a ring
    # S - Select a ring
    # M - Move a ring
    # R - Remove a row
    # X - Remove a ring

    ## Grid Positions
    # point in center is hexagon 0 and so on outwards
    # topmost point of hexagon is point 0 and pt number increase clockwise with 6*hexring pts on each hexagon
    '''
    def execute_move(self, cmd) :
        moves = cmd.split()
        if len(moves) > 3:
            return self.execute_sequence(moves)
        move_type = moves[0]
        hexagon = int(moves[1])
        position = int(moves[2])

        success = 1
        string_invalid = False

        if (move_type == 'P'): # Place your ring
            self.click_at(hexagon, position)
        elif (move_type == 'S'): # Select a ring
            self.click_at(hexagon, position)
        elif (move_type == 'M'): # Move a ring
            self.click_at(hexagon, position)
        elif (move_type == 'RS'): # Remove a row start
            self.click_at(hexagon, position)
        elif (move_type == 'RE'): # Remove a row end
            self.click_at(hexagon, position)
        elif (move_type == 'X'): # Remove a ring
            self.click_at(hexagon, position)
        else:
            string_invalid = True 
    
        valid = self.check_move_validity()
        won = self.check_won()
        
        if(string_invalid == True or valid == False):
            success = 0
        elif(won == True):
            success = 2

        return success

if __name__ == "__main__":
    game = Game(5, 'GUI')
    game.execute_move("P 0 0")
    game.execute_move("P 4 16")
    # game.execute_move("P 5 26")
    # game.execute_move("P 4 13")
    # positions = game.get_pos()
    # myboard = [[0 for x in range(11)] for y in range(11)] 
    #   # positions = list(self.driver.execute_script('return positions;'))
    # r=0
    
    # for row in positions:
    #     c=0
    #     for place in row:
    #         piece = dict(place)['piece']
    #         if piece == 2:
    #             myboard[r][c]=2
    #         elif piece == 1:
    #             myboard[r][c]=1
    #         elif piece == -1:
    #             myboard[r][c]=-1
    #         elif piece == -2:
    #             myboard[r][c]=-2
    #         c=c+1
    #     r=r+1

    # for i in range(11):
    #     for j in range(11):
    #         print(str(i)+"i "+str(j)+"j"+" "+str(myboard[i][j]))



   
    # game.execute_move("P 5 19")
    # game.execute_move("P 3 1")
    # game.execute_move("P 1 2")
    # game.execute_move("P 4 5")
    # game.execute_move("P 5 21")
    # game.execute_move("P 3 5")
    # game.execute_move("P 1 4")
    # game.execute_move("S 3 5 M 2 5")
    # game.execute_move("S 5 21 M 3 13")
    # game.execute_move("S 2 5 M 2 4")
    # game.execute_move("S 5 19 M 4 15")
    # game.execute_move("S 0 0 M 2 2")
    # game.execute_move("S 4 15 M 4 14")
    # game.execute_move("S 2 4 M 2 3")
    # game.execute_move("S 3 13 M 2 9")
    # game.execute_move("S 2 2 M 4 22")
    # game.execute_move("S 4 14 M 5 17")
    # game.execute_move("S 4 5 M 4 4")
    # game.execute_move("S 5 26 M 1 1")
    # game.execute_move("S 2 3 M 3 2")
    # game.execute_move("S 1 4 M 2 7")
    # game.execute_move("S 3 1 M 3 14")
    # game.execute_move("S 2 9 M 1 5")
    # game.execute_move("S 4 13 M 3 8")
    # game.execute_move("S 1 1 M 4 21")
    # game.execute_move("S 3 14 M 1 3")
    # game.execute_move("S 5 17 M 3 9")
    # game.execute_move("S 3 8 M 5 8")
    # game.execute_move("S 4 21 M 1 0")
    # game.execute_move("S 4 22 M 2 8")
    # game.execute_move("S 1 5 M 4 17")
    # game.execute_move("S 2 8 M 3 12")
    # game.execute_move("S 1 2 M 2 1")
    # game.execute_move("S 3 2 M 3 7 RS 2 8 RE 2 2 X 3 7")
    # game.execute_move("S 2 1 M 3 4")
    # game.execute_move("S 1 3 M 0 0")
    # game.execute_move("S 1 0 M 1 1")
    # game.execute_move("S 3 12 M 1 4")
    # game.execute_move("S 3 4 M 2 2")
    # game.execute_move("S 5 8 M 5 9")
    # game.execute_move("S 1 1 M 4 11")
    # game.execute_move("S 0 0 M 2 6")
    # game.execute_move("S 4 17 M 4 16")
    # game.execute_move("S 2 6 M 2 0")
    # game.execute_move("S 2 7 M 3 11")
    # game.execute_move("S 2 0 M 2 11")
    # game.execute_move("S 3 11 M 2 10")
    # game.execute_move("S 2 11 M 3 16")
    # game.execute_move("S 2 2 M 3 7")
    # game.execute_move("S 4 4 M 5 6")
    # game.execute_move("S 4 11 M 4 12")
    # game.execute_move("S 3 16 M 3 17")

    ### Enter Game Moves Here to Test
    ## Example: game.execute_move("P 2 0")
    


