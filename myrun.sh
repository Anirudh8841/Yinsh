xterm -hold -e "python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log"&
sleep 1
xterm -hold -e "python  client.py 0.0.0.0 10000 run.sh -mode GUI"&
sleep 1
xterm -hold -e "python  client.py 0.0.0.0 10000 RandomPlayer.py"
