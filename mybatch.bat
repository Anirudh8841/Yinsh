start cmd.exe @cmd /k "python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log" 
start cmd.exe @cmd /k "python  client.py 127.0.0.1 10000 RandomPlayer.py -mode GUI"
start cmd.exe @cmd /k "python  client.py 127.0.0.1 10000 RandomPlayer.py"
