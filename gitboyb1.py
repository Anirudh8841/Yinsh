import sys
import time
import copy

# 1 - for marker
# 2 - for rings
# + for white
# - for black
# -100 for invalid, 0 for empty
row_weights = [1,3,9,27,81]
dirs = [[0,-2],[-1,1],[-1,-1],[0,2],[1,1],[1,-1]]
sel_ring = [-1, -1]
remove_row_start = [-1,-1]
remove_row_end = [-1,-1]
whiteRingsOnBoard = 0
blackRingsOnBoard = 0
whiteRings = 5
blackRings = 5


def setMarker(board,x,y,marker):
    board[x][y] = marker
    return board

def isValidPoint(board,row,col):
    if(row > 19 or row < 0 or col < 0 or col > 10 or board[col][row] == -100):
        return False
    return True

def removeMarker(board,x,y):
    board[x][y] = 0
    return board

def flipMarkers(board,x_init, y_init,x_fin,y_fin):
    ind = 0
    for i,dir in enumerate(dirs):
        if(dir[0] == 0):
            if( x_init == x_fin  and (y_fin - y_init) % dir[1] == 0 ):
                ind = i
                break
        elif( (x_fin - x_init) / dir[0] == (y_fin - y_init) / dir[1]):
            ind = i
            break
    temp_x = x_init + dirs[ind][0]
    temp_y = y_init + dirs[ind][1]
    k = (y_fin - y_init) / dirs[ind][1]
    for l in range(1,k):
        if(board[temp_x][temp_y] == -1):
            board[temp_x][temp_y] = 1
        elif(board[temp_x][temp_y] == 1):
            board[temp_x][temp_y] = -1

        temp_x = temp_x + dirs[ind][0]
        temp_y = temp_y + dirs[ind][1]

    return board

def moveRing(board, x_init, y_init,x_fin, y_fin):
    ring = board[x_init][y_init]
    marker = 1 if ring == 2 else -1
    board[x_init][y_init] = marker
    board = flipMarkers(board, x_init, y_init,x_fin, y_fin)
    board[x_fin][y_fin] = ring

    return board

def placeRingAt(board, x, y, id):
    global whiteRingsOnBoard
    global blackRingsOnBoard
    if(id == 0):
        whiteRingsOnBoard = whiteRingsOnBoard + 1
        return setMarker(board,x,y,2)
    else:
        blackRingsOnBoard = blackRingsOnBoard + 1
        return setMarker(board,x,y,-2)

def removeRing(board, x, y, id):
    global whiteRings
    global blackRings
    if(id == 0):
        whiteRings = whiteRings - 1
    else:
        blackRings = blackRings - 1
    return removeMarker(board, x, y)

def checkWon():
    global whiteRings
    global blackRings
    if( whiteRings <= 2 or blackRings <= 2):
        return True
    else:
        return False

def selectRing(board, x, y):
    global sel_ring
    sel_ring = [x,y]
    return board

def removeRow(board,x_init, y_init, x_fin, y_fin):
    ind = 0
    for i,dir in enumerate(dirs):
        if(dir[0] == 0):
            if( x_init == x_fin  and (y_fin - y_init) % dir[1] == 0 ):
                ind = i
                break
        elif( (x_fin - x_init) / dir[0] == (y_fin - y_init) / dir[1]):
            ind = i
            break
    temp_x = x_init
    temp_y = y_init
    k = (y_fin - y_init) / dirs[ind][1]
    for l in range(1,k+1):
        board[temp_x][temp_y] = 0

        temp_x = temp_x + dirs[ind][0]
        temp_y = temp_y + dirs[ind][1]

    return board

def selectRowStart(board, x, y):
    global remove_row_start
    remove_row_start = [x,y]
    return board

def selectRowEnd(board, x, y):
    global remove_row_end
    global remove_row_start
    remove_row_end = [x,y]
    return removeRow(board,remove_row_start[0],remove_row_start[1], remove_row_end[0], remove_row_end[1])


def execute_sequence(board, moves, id):
    moves_list = []
    for i, move in enumerate(moves):
        if i % 3 == 2:
            moves_list += [move]
            board = execute_move(board,' '.join(moves_list), id)
            moves_list = []
        else:
            moves_list += [move]
    return board

def execute_move(board, cmd, id):
    board = copy.deepcopy(board)
    moves = cmd.split()
    if len(moves) > 3:
        return execute_sequence(board,moves,id)
    move_type = moves[0]
    x = int(moves[1])
    y = int(moves[2])

    success = 1
    string_invalid =  False

    global sel_ring
    if(move_type == 'P'):
        return placeRingAt(board, x, y, id)
    elif (move_type == 'S'): # Select a ring
        return selectRing(board, x ,y)
    elif (move_type == 'M'): # Move a ring
        return moveRing(board,sel_ring[0],sel_ring[1],x,y)
    elif (move_type == 'RS'): # Remove a row start
        return selectRowStart(board, x, y)
    elif (move_type == 'RE'): # Remove a row end
        return selectRowEnd(board, x, y)
    elif (move_type == 'X'): # Remove a ring
        return removeMarker(board, x, y)


def calculate_score( rA, rB, mA, mB, Error_state):
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

def get_score(board, player_id, Error_state=0):
    rings_A = 0
    rings_B = 0
    markers_A = 0
    markers_B = 0
    for cols in range(11):
        for rows in range(19):
            piece = board[cols][rows]
            if piece == '2':
                rings_A+=1
            elif piece == '1':
                markers_A+=1
            elif piece == '-1':
                markers_B+=1
            elif piece == '-2':
                rings_B+=1
    return calculate_score(5-rings_A, 5-rings_B, markers_A, markers_B, Error_state)[player_id]

def markerScore(board, marker, ring):
    marker_score = 0.0
    allot = 0
    row = 0
    global row_weights
    for col in range(11):
        allot = 0
        row = 0
        while board[col][row] == 0:
            row += 1
        while (row < 19 and board[col][row] == 0):
            if(board[col][row] == marker):
                marker_score += row_weights[allot]
                if(allot != 4):
                    allot += 1
            elif (board[col][row] == ring):
                marker_score += 0.5 * row_weights[allot]
                if(allot != 4):
                    allot += 1
            else:
                allot = 0
            row += 2
    row = 0
    col = 4

    for count in range(4):
        allot = 0
        a = col
        b = row
        while board[a][b] != -100:
            if(board[a][b] == marker):
                marker_score += row_weights[allot]
                if allot != 4:
                    allot += 1
            elif(board[a][b] == ring):
                marker_score += 0.5 * row_weights[allot]
                if allot != 4:
                    allot += 1
            else:
                allot = 0
            a -= 1
            b += 1

    row = row + 2
    a = col
    b = row
    allot = 0
    while  a < 11 and b < 19 and board[a][b] != -100 :
        if(board[a][b] == marker):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        elif(board[a][b] == ring):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        else:
            allot = 0
        b += 1
        a += 1

    row += 1
    col -= 1
    for count in range(4):
        allot = 0
        a = col
        b = row
        while board[a][b] != -100:
            if(board[a][b] == marker):
                marker_score += row_weights[allot]
                if allot != 4:
                    allot += 1
            elif(board[a][b] == ring):
                marker_score += 0.5 * row_weights[allot]
                if allot != 4:
                    allot += 1
            else:
                allot = 0
            a -= 1
            b += 1

    allot = 0
    a = col
    b = row
    while board[a][b] != -100:
        if(board[a][b] == marker):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        elif(board[a][b] == ring):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        else:
            allot = 0
        b -= 1
        a += 1

    allot = 0
    row += 1
    col += 1
    a = col
    b = row
    while a < 11 and b > -1 and board[a][b] != -100:
        if(board[a][b] == marker):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        elif(board[a][b] == ring):
            marker_score += row_weights[allot]
            if allot != 4:
                allot += 1
        else:
            allot = 0
        b -= 1
        a += 1

    row += 2
    for count in range(4):
        allot = 0
        a = col
        b = row
        while  a < 11 and b > -1 and board[a][b] != -100:
            if(board[a][b] == marker):
                marker_score += row_weights[allot]
                if allot != 4:
                    allot += 1
            elif(board[a][b] == ring):
                marker_score += 0.5 * row_weights[allot]
                if allot != 4:
                    allot += 1
            else:
                allot = 0
            a += 1
            b -= 1
        row += 1
        col += 1
    return marker_score

def flippedUtil(board,marker,ring,dir,i,j):
    row = i + dir[1]
    col = j + dir[0]
    marker_count = 0
    while row < 19 and row > -1 and col < 11 and col > -1 and board[col][row] == 0:
        row += dir[1]
        col += dir[0]
    while row < 19 and row > -1 and col < 11 and col > -1 and board[col][row] != -100:
        if(board[col][row] == marker):
            marker_count += 1
        elif board[col][row] == 0:
            return marker_count
        elif (board[col][row] == -2 or board[col][row] == 2 ):
            return 0
        row += dir[1]
        col += dir[0]
    return 0

def flippedScore(board,marker,ring):
    flipped_score = 0.0
    for i in range(11):
        for j in range(19):
            if(board[i][j] == ring):
                for k in range(6):
                    flipped_score+= flippedUtil(board,marker,ring,dirs[k],i,j)

    return flipped_score

def countMarkers(board,marker):
    marker_count = 0
    for i in range(11):
        for j in range(19):
            if(board[i][j] == marker):
                marker_count += 1
    return marker_count

def mobilityUtil(board,ring,dir,i,j):
    row = i + dir[1]
    col = j + dir[0]
    space_count = 0
    while(row < 19 and row > -1 and col < 11 and col > -1 and board[col][row] == 0):
        space_count += 1
        row += dir[1]
        col += dir[0]
    while(row < 19 and row > -1 and col < 11 and col > -1 and board[col][row] != -100):
        if(board[col][row] == 0):
            return space_count+1
        elif (board[col][row] == -2 or board[col][row] == 2):
            return space_count
        row += dir[1]
        col += dir[0]
    return space_count

def mobilityScore(board,ring):
    mobility_score = 0.0
    for i in range(11):
        for j in range(19):
            if board[i][j] == ring:
                for k in range(6):
                    mobility_score += mobilityUtil(board,ring,dirs[k],i,j)
    return mobility_score

def evaluationFunction(board, current_player):
    #board = copy.deepcopy(board)
    num_w_marker = countMarkers(board,1)
    num_b_marker = countMarkers(board,-1)

    black_row = markerScore(board,-1,-2)
    white_row = markerScore(board,1,2)

    flip_ring = 2 if (current_player == 0) else -2

    flip_white_marker = flippedScore(board,-1,flip_ring)
    flip_black_marker = flippedScore(board,1,flip_ring)

    mobility_black_ring = mobilityScore(board,-2)
    mobility_white_ring = mobilityScore(board,2)

    white_score = get_score(board, 0)
    black_score = get_score(board, 1)

    return (num_w_marker + white_row + flip_white_marker + mobility_white_ring + white_score) * (0.5 * (1 + white_score)) + (num_b_marker + black_row + flip_black_marker + mobility_black_ring + black_score) * (0.5 * (1 + black_score))

def listRings(board, id):
    lis = []
    for i in range(11):
        for j in range(19):
            if board[i][j] == id:
                lis.append([i,j])
    return lis

def validPointsInARow(board,point,dir):
    lis = []
    col = point[0] + dir[0]
    row = point[1] + dir[1]
    no_jump = True
    first_jump = False
    while (row > -1 and row < 19 and col > -1 and col < 11):
        if(board[col][row] == 2 or board[col][row] == -2):
            return lis
        elif (board[col][row] == -1 or board[col][row] == 1):
            first_jump = True
            no_jump = False
        elif(board[col][row] == 0):
            if(no_jump == True):
                lis.append([col,row])
            if(first_jump == True):
                lis.append([col,row])
                return lis
        col = col + dir[0]
        row = row + dir[1]
    return lis

def validMovesList(board,point):
    #board = copy.deepcopy(board)
    lis = []
    for i,dir in enumerate(dirs):
        lis.extend(validPointsInARow(board,point,dir))
    return lis

def checkRuns(board,pid):
    board = copy.deepcopy(board)
    marker = 1 if pid == 0 else -1
    lis = []
    for i in range(11):
        for j in range(11):
            if(board[i][j] != marker):
                continue
            isrow = True
            for k in range(1,5):
                if(board[i][j+k*2] != marker):
                    isrow = False
                    break
            if isrow == False:
                continue
            lis.append([[i,j],[i,j+8]])

    for i in range(7):
        for j in range(4,19):
            if board[i][j] != marker:
                continue
            isrow = True
            for k in range(1,5):
                if (board[i+k][j-k] != marker):
                    isrow = False
                    break
            if isrow == False:
                continue
            lis.append([[i,j],[i+4,j-4]])

    for i in range(7):
        for j in range(15):
            if board[i][j] != marker:
                continue
            isrow = True
            for k in range(1,5):
                if(board[i+k][j+k] != marker):
                    isrow = False
                    break
            if isrow == False:
                continue
            lis.append([[i,j],[i+4,j+4]])
    return lis

if __name__ == "__main__":
    null = 'null'
    h_to_b = [[(5,9)],[(5,7),(6,8),(6,10),(5,11),(4,10),(4,8)],[(5,5),(6,6),(7,7),(7,9),(7,11),(6,12),(5,13),(4,12),(3,11),(3,9),(3,7),(4,6)],[(5,3),(6,4),(7,5),(8,6),(8,8),(8,10),(8,12),(7,13),(6,14),(5,15),(4,14),(3,13),(2,12),(2,10),(2,8),(2,6),(3,5),(4,4)],[(5,1),(6,2),(7,3),(8,4),(9,5),(9,7),(9,9),(9,11),(9,13),(8,14),(7,15),(6,16),(5,17),(4,16),(3,15),(2,14),(1,13),(1,11),(1,9),(1,7),(1,5),(2,4),(3,3),(4,2)],[null,(6,0),(7,1),(8,2),(9,3),null,(10,6),(10,8),(10,10),(10,12),null,(9,15),(8,16),(7,17),(6,18),null,(4,18),(3,17),(2,16),(1,15),null,(0,12),(0,10),(0,8),(0,6),null,(1,3),(2,2),(3,1),(4,0)]]
    board = []
    for i in range(11):
        board.append([-100 for x in range(19)])

    for i in h_to_b:
        for j in i:
            if j != 'null':
                board[j[0]][j[1]] = 0
